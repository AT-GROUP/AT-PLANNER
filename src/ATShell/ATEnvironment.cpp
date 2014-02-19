#include "ATEnvironment.h"

#include "AQNewProjectDialog.h"
#include "AQNewFileDialog.h"
#include "ATApplication.h"
#include "APluginsWidget.h"
#include <ATCore/project/AProject.h>
#include <ATCore/project/AProjectNode.h>
#include <ATCore/ADocument.h>
#include <ATCore/ADocument.h>
#include <ATGUI/AEditor.h>
//#include "editors/schemes_editor/AQSchemesEditor.h"
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QDialog>

using namespace std;

ATEnvironment::ATEnvironment(ATApplication * app, QWidget *parent)
	: QMainWindow(parent), AProjectManager(), m_pApplication(app)
{
	ui.setupUi(this);

	/*
	"File" menu.
	*/
	connect(ui.actionExit, &QAction::triggered, this, &ATEnvironment::close);
	connect(ui.actionNewProject, &QAction::triggered, this, &ATEnvironment::createNewProject);
	connect(ui.actionSave_Project, &QAction::triggered, [=]()
			{
				saveProject();
			}
		);
	connect(ui.actionOpen_Project, &QAction::triggered, this, &ATEnvironment::openProject);

	//Create planner widget
	auto planner_wdg = m_pApplication->planner()->createInfoWidget();
	ui.dockPlanner->setWidget((QWidget*)planner_wdg);
	/*
	Create switching menus in View menu.
	*/
	QList<QDockWidget *> dockwidgets = findChildren<QDockWidget *>();
    for(auto i : dockwidgets)
	{
        if (i->parentWidget() == this)
			ui.menuView->addAction(i->toggleViewAction());
    }

	//Setup project explorer links
	connect(ui.wdgProjectExplorer, &AProjectExplorer::createNewFileRequested, this, &ATEnvironment::createNewFile);
	connect(ui.wdgProjectExplorer, &AProjectExplorer::openNodeFileRequested, this, &ATEnvironment::openNodeDocument);

	//connect(ui.actionNewFile, &QAction::triggered, [=](){openFile("test");});

	//mEditorsFactory.insert(pair<AFile::Type, AAbstractEditorInitializer*>(AFile::Type::ExtendedDFD, new AEditorInitializer<EDFDEditor>()));

	ui.wdgConsole->setDelegate(m_pApplication);

	connect(ui.actionPlugins, &QAction::triggered, [=]()
		{
			auto wdg = new APluginsWidget(m_pApplication);
			wdg->show();
	});
}

ATEnvironment::~ATEnvironment()
{

}

void ATEnvironment::displayProject(AProject * _project)
{
	if(_project)
		ui.wdgProjectExplorer->loadProjectTree(_project->rootNode());

	QString file_name = project() ? QFileInfo(QString::fromStdString(project()->name())).fileName() : "No File";
	setWindowTitle(QString("%1 - ATEnvironment").arg(file_name));
}

int ATEnvironment::closeProject()
{
	int res = 0;

	if(project())
	{
		if(project()->hasUnsavedChanges())
		{
			int ret = QMessageBox::warning(this, tr("Save chanhes"),
									tr("The project has been modified.\n"
									   "Do you want to save your changes?"),
									QMessageBox::Save | QMessageBox::Discard
									| QMessageBox::Cancel,
									QMessageBox::Save);

		
			if(ret == QMessageBox::Cancel)
				return 1;
			else if(ret == QMessageBox::Save)
			{
				saveProject();
			}
		}
		res = AProjectManager::closeProject();
	}
	

	return res;
}

void ATEnvironment::createNewProject()
{
	AQNewProjectDialog prj_dlg(this);
	if(prj_dlg.exec() == QDialog::Accepted)
	{
		if(closeProject() == 0)
		{
			//Create dir for new project
			QDir base_dir(prj_dlg.projectDir());
			base_dir.mkdir(prj_dlg.projectName());

			QString project_dir = prj_dlg.projectDir() + "/" + prj_dlg.projectName();

			auto res = createProject(project_dir.toStdString());
			displayProject(res);
		}
	}
}

void ATEnvironment::createNewFile(AQProjectNode * project_parent_node)
{
	AQNewFileDialog dlg(m_pApplication);
	if(dlg.exec() != QDialog::Accepted)
	{
		return;
	}
	
	auto editor_plugin = dlg.selectedTypeEditor();
	ADocument * doc = editor_plugin->createFile(project()->projectDir(), dlg.fileName().toStdString());

	if(!doc)
		return;

	ADocumentProjectNode * new_node = new ADocumentProjectNode(doc);
	project_parent_node->projectNode()->addChild(new_node);

	AQProjectNode * new_tree_node = new AQProjectNode(new_node, project_parent_node);
	if(!project_parent_node->isExpanded())
		project_parent_node->setExpanded(true);

	openNodeDocument(new_node);
}

void ATEnvironment::openProject()
{
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open project"),
                                                 "D:",
                                                 tr("AT Project Files (*.atprj);; All Files (*)"));

	auto res = AProjectManager::openProject(file_name.toStdString());
	if(res)
		displayProject(res);
	else
		QMessageBox::warning(this, tr("Error"), tr("Unable to open given project."), QMessageBox::Ok);
}

void ATEnvironment::openNodeDocument(ADocumentProjectNode * doc_node)
{
	//Check, maybe document is already opened
	auto oi = mOpenedDocs.find(doc_node);
	if(oi != mOpenedDocs.end())
	{
		ui.mdiArea->setActiveSubWindow(oi->second);
	}
	else
	{
		ui.mdiArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		//Find suitable editor for file
		QFileInfo fi(QString::fromStdString(doc_node->name()));
		QString ext = fi.completeSuffix();

		auto ed_plug = m_pApplication->editorForExtension(ext.toStdString());
		if(!ed_plug)
		{
			QMessageBox::warning(this, tr("Error"), tr("No suitable editors loaded into environment."), QMessageBox::Ok);
			return;
		}

		auto gui_plug = static_cast<AGUIEditorPlugin*>(ed_plug);
		auto ed_wdg = static_cast<AGUIEditorInstance*>(gui_plug->createEditorInstance());
	
		auto mdi_sub_wind = new ATMdiWindow(ed_wdg);
	
		ui.mdiArea->addSubWindow(mdi_sub_wind);
		ui.mdiArea->setActiveSubWindow(mdi_sub_wind);

		mdi_sub_wind->show();
	
		/*connect(ed_wdg, &AGUIEditorInstance::windowTitleChanged, [=](const QString & new_title)
			{
				mdi_sub_wind->setWindowTitle(new_title);
		});*/


		ed_wdg->openFile(project()->projectDir() + "/" + doc_node->name());
		mdi_sub_wind->setWindowTitle(ed_wdg->windowTitle());

		connect(mdi_sub_wind, &ATMdiWindow::editorClosed, [=]()
			{
				closeMdiWindow(mdi_sub_wind, doc_node);
		});

		mOpenedDocs.insert(pair<ADocumentProjectNode*, ATMdiWindow*>(doc_node, mdi_sub_wind));
	}
}

void ATEnvironment::closeMdiWindow(ATMdiWindow * mdi_wnd, ADocumentProjectNode * doc_node)
{
	ui.mdiArea->removeSubWindow(mdi_wnd);

	auto oi = mOpenedDocs.find(doc_node);
	mOpenedDocs.erase(oi);
}
