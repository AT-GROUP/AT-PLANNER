#include "ATEnvironment.h"

#include "AQNewProjectDialog.h"
#include "AQNewFileDialog.h"
#include "ATApplication.h"
#include "APluginsWidget.h"
#include <ATCore/project/AProject.h>
#include <ATCore/project/AProjectNode.h>
#include <ATCore/AFile.h>
#include <ATGUI/AEditor.h>
//#include "editors/schemes_editor/AQSchemesEditor.h"
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QDialog>

/*void parseDoc(xmlNodePtr ptr, AProjectNode *  _node)
{
	ptr = ptr->xmlChildrenNode;
	int _i = 0;
	while (ptr != NULL)
	{	

		if (_i&1)
		{
			AFile * new_file = new AFile((const char*) ptr->name);
			AFileProjectNode * new_node = new AFileProjectNode(new_file);
			_node->addChild(new_node);
			parseDoc(ptr, new_node);
		}
		ptr = ptr->next;
		++_i;
	}
}*/


void ATEnvironment::parseDocument(xmlNodePtr _ptr, AProjectNode *  _node)
{
	_ptr = _ptr->xmlChildrenNode;
	int _i = 0;
	while (_ptr != NULL)
	{	

		if (_i&1)
		{
			AFile * new_file = new AFile((const char*) _ptr->name);
			AFileProjectNode * new_node = new AFileProjectNode(new_file);
			_node->addChild(new_node);
			parseDocument(_ptr, new_node);
		}
		_ptr = _ptr->next;
		++_i;
	}
}

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
	connect(ui.wdgProjectExplorer, &AProjectExplorer::openFileRequested, [=](AFile * file){openFile(file);});

	//connect(ui.actionNewFile, &QAction::triggered, [=](){openFile("test");});

	//mEditorsFactory.insert(pair<AFile::Type, AAbstractEditorInitializer*>(AFile::Type::ExtendedDFD, new AEditorInitializer<EDFDEditor>()));

	ui.wdgConsole->setDelegate(m_pApplication);

	connect(ui.actionPlugins, &QAction::triggered, [=]()
		{
			auto wdg = new APluginsWidget(m_pApplication);
			wdg->show();
	});


	//=============
	/*auto arch_plugin = static_cast<AGUIEditorPlugin*>(m_pApplication->editorForExtension("arch"));
	auto ed = arch_plugin->createMainWindow();
	ed->showMaximized();*/

	auto edfd_plugin = static_cast<AGUIEditorPlugin*>(m_pApplication->editorForExtension("edfd"));
	auto ed = edfd_plugin->createMainWindow();
	ed->showMaximized();

}

ATEnvironment::~ATEnvironment()
{

}

void ATEnvironment::displayProject(AProject * _project)
{
	if(_project)
		ui.wdgProjectExplorer->loadProjectTree(_project->rootNode());

	QString file_name = project() ? QFileInfo(project()->name()).fileName() : "No File";
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
	AQNewFileDialog dlg;
	if(dlg.exec() == QDialog::Accepted)
	{
		QString file_name = dlg.fileName() + ".rdpd";

		AFile * new_file = new AFile(file_name.toStdString().c_str());

		AFileProjectNode * new_node = new AFileProjectNode(new_file);
		project_parent_node->projectNode()->addChild(new_node);

		AQProjectNode * new_tree_node = new AQProjectNode(new_node, project_parent_node);
		if(!project_parent_node->isExpanded())
			project_parent_node->setExpanded(true);
	}
}


void ATEnvironment::openFile(AFile * file)
{
	ui.mdiArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QMdiSubWindow * mdi_sub_wind = new QMdiSubWindow();
	

/*	AQSchemesEditor * editor = new AQSchemesEditor();
	mdi_sub_wind->layout()->addWidget(editor);
	//editor->show();
	mdi_sub_wind->show();

	ui.mdiArea->addSubWindow(mdi_sub_wind);
	ui.mdiArea->setActiveSubWindow(mdi_sub_wind);

	editor->openFile(file);*/
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