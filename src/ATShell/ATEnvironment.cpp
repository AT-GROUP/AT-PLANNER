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
#include <ATPlanner/APlannerWidget.h>
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
	connect(ui.actionOpenProject, &QAction::triggered, [=]()
		{
			this->openProject();
	});

	connect(ui.actionOpenFile, &QAction::triggered, [=]()
		{
			this->openFile();
	});

	
	//Create planner widget
	auto planner_wdg = m_pApplication->planner()->createInfoWidget();
	ui.dockPlanner->setWidget((QWidget*)planner_wdg);
	m_pApplication->setPlannerWidget(planner_wdg);
	connect(planner_wdg, &APlannerWidget::startArchDocumentCreated, this, &ATEnvironment::openNodeDocument);

	connect(planner_wdg, &APlannerWidget::projectStructureChanged, [=](){
		displayProject(project());
	});

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

	connect(ui.actionPlugins, &QAction::triggered, [=](){
			auto wdg = new APluginsWidget(m_pApplication);
			wdg->show();
	});

	connect(ui.actionBuildProject, &QAction::triggered, [=](){
		this->buildProject(*ui.wdgConsole);
	});

	connect(ui.actionBuildCleanProject, &QAction::triggered, [=](){
		this->buildClean(*ui.wdgConsole);
	});

	

	/*auto arch_plugin = static_cast<AGUIEditorPlugin*>(m_pApplication->editorForExtension("arch"));
	auto ed = static_cast<AGUIEditorInstance*>(arch_plugin->createEditorInstance());
	ed->showMaximized();*/
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

	m_pApplication->planner()->loadProject(_project);
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

void ATEnvironment::openProject(const std::string & path)
{
	auto res = AProjectManager::openProject(path);
	if(res)
		displayProject(res);
	else
		QMessageBox::warning(this, tr("Error"), tr("Unable to open given project."), QMessageBox::Ok);
}

void ATEnvironment::openProject()
{
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open project"),
                                                 "D:",
                                                 tr("AT Project Files (*.atprj);; All Files (*)"));
	openProject(file_name.toStdString());
}

void ATEnvironment::openFile()
{
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                 "D:",
                                                 tr("All Files (*)"));
	if(file_name != "")
		openFile(file_name.toStdString());
}

void ATEnvironment::openFile(const std::string & file_path)
{
	//Check, maybe document is already opened
	auto oi = mOpenedFiles.find(file_path);
	if(oi != mOpenedFiles.end())
	{
		ui.mdiArea->setActiveSubWindow(oi->second);
	}
	else
	{
		ui.mdiArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		//Find suitable editor for file
		QFileInfo fi(QString::fromStdString(file_path));
		QString ext = fi.suffix();

		auto ed_plug = m_pApplication->editorForExtension(ext.toStdString());
		if(!ed_plug)
		{
			QMessageBox::warning(this, tr("Error"), tr("No suitable editors loaded into environment."), QMessageBox::Ok);
			return;
		}

		auto gui_plug = static_cast<AGUIEditorPlugin*>(ed_plug);
		auto ed_wdg = static_cast<AGUIEditorInstance*>(gui_plug->createEditorInstance());
		ed_wdg->setDelegate(this);
	
		auto mdi_sub_wind = new ATMdiWindow(ed_wdg);
	
		ui.mdiArea->addSubWindow(mdi_sub_wind);
		ui.mdiArea->setActiveSubWindow(mdi_sub_wind);

		ed_wdg->openFile(file_path);
		mdi_sub_wind->setWindowTitle(ed_wdg->windowTitle());

		connect(mdi_sub_wind, &ATMdiWindow::editorClosed, [=]()
			{
				closeMdiWindow(mdi_sub_wind, file_path);
		});

		mOpenedFiles.insert(pair<string, ATMdiWindow*>(file_path, mdi_sub_wind));

		//Connect events
		connect(mdi_sub_wind, &ATMdiWindow::aboutToActivate, [=]()
			{
				linkFileActions(ed_wdg);
		});

		mdi_sub_wind->show();
	}
}

void ATEnvironment::openNodeDocument(ADocumentProjectNode * doc_node)
{
	openFile(project()->documentPath(doc_node));
}

void ATEnvironment::openDocument(const std::string & document_name)
{
	//Find node with document in the project
	auto doc_node = project()->findDocumentNode(document_name);

	if(doc_node)
	{
		//Open it
		openNodeDocument(doc_node);
	}
	else
	{
		AError::criticalErrorOccured(AError(AT_ERROR_FILE_NOT_FOUND, "Document \"" + document_name + "\" was not found in the project."));
	}
}

void ATEnvironment::closeMdiWindow(ATMdiWindow * mdi_wnd, const std::string & fpath)
{
	ui.mdiArea->removeSubWindow(mdi_wnd);

	auto oi = mOpenedFiles.find(fpath);
	mOpenedFiles.erase(oi);
}

void ATEnvironment::documentChanged(const std::shared_ptr<ADocument> & doc)
{
//	if(doc->type() == ADocument::Type::EDFD)
//		m_pApplication->planner()->buildGeneralizedPlan();
}

void ATEnvironment::documentOpenRequested(const std::string & document_name)
{
	openDocument(document_name);
}

void ATEnvironment::linkFileActions(AGUIEditorInstance * editor_widget)
{
	//Link file actions
	
	if(editor_widget)
	{
		ui.actionSaveAsFile->setEnabled(true);
		ui.actionSaveFile->setEnabled(true);

		connect(ui.actionSaveFile, &QAction::triggered, editor_widget, &AGUIEditorInstance::saveFileInitiated);
	}
	else
	{
		ui.actionSaveAsFile->setEnabled(false);
		ui.actionSaveFile->setEnabled(false);
	}

}
