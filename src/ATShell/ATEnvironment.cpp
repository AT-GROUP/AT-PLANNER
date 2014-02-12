#include "ATEnvironment.h"
#include <ATCore/project/AProject.h>
#include "AQNewProjectDialog.h"
#include "AQNewFileDialog.h"
#include "APluginsWidget.h"
#include "ATEnvironment.h"
#include "ATApplication.h"
#include <ATCore/project/AProjectNode.h>
#include <ATCore/AFile.h>
#include <ATPlanner/ATPlanner.h>
#include <ArchEditor/AArchEditor.h>
//#include <EDFDEditor/EDFDEditor.h>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QMessageBox>

using namespace std;

ATEnvironment::ATEnvironment(ATApplication * app, QWidget *parent)
	: QMainWindow(parent), m_pProject(0), m_pApplication(app)
{
	ui.setupUi(this);

	/*
	"File" menu.
	*/
	connect(ui.actionExit, &QAction::triggered, this, &ATEnvironment::close);
	connect(ui.actionNewProject, &QAction::triggered, this, &ATEnvironment::createNewProject);

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

	connect(ui.actionNewFile, &QAction::triggered, [=](){openFile("test");});

	//mEditorsFactory.insert(pair<AFile::Type, AAbstractEditorInitializer*>(AFile::Type::ExtendedDFD, new AEditorInitializer<EDFDEditor>()));

	ui.wdgConsole->setDelegate(m_pApplication);

	connect(ui.actionPlugins, &QAction::triggered, [=]()
		{
			auto wdg = new APluginsWidget(m_pApplication);
			wdg->show();
	});


	//=============
	auto arch_plugin = static_cast<AGUIEditorPlugin*>(m_pApplication->editorForExtension("arch"));
	auto ed = arch_plugin->createMainWindow();
	ed->showMaximized();
}

ATEnvironment::~ATEnvironment()
{

}

void ATEnvironment::displayProject(AProject * _project)
{
	if(_project)
		ui.wdgProjectExplorer->loadProjectTree(_project->rootNode());


	delete m_pProject;
	m_pProject = _project;

	updateWindowTitle();
}

int ATEnvironment::closeProject()
{
	if(m_pProject)
	{
		//Ask to save changes

		displayProject(0);
		return 0;
	}
	else
		return 0;
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

			AProject * project = new AProject(prj_dlg.projectName().toStdString().c_str(), project_dir.toStdString().c_str());
			project->save();
			displayProject(project);
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

void ATEnvironment::openFile(const std::string & file_path)
{
	//Get file type
	auto f_type = AFile::Type::ExtendedDFD;

	//Check if there is registered editor
/*	auto i_it = mEditorsFactory.find(f_type);
	if(i_it == mEditorsFactory.end())
	{
		 QMessageBox::warning(this, tr("Error"), tr("There is no registered association for given file type."), QMessageBox::Ok);
		 return;
	}

	AEditor * ed_instance = i_it->second->init(0, 0);*/

	QMdiSubWindow * mdi_sub_wind = new QMdiSubWindow();


//	mdi_sub_wind->layout()->addWidget(ed_instance);
	mdi_sub_wind->show();

	ui.mdiArea->addSubWindow(mdi_sub_wind);
	ui.mdiArea->setActiveSubWindow(mdi_sub_wind);
}

void ATEnvironment::updateWindowTitle()
{
	QString file_name = m_pProject ? QFileInfo(m_pProject->name()).fileName() : "No File";
	setWindowTitle(QString("%1 - ATEnvironment").arg(file_name));
}

void ATEnvironment::openFile(AFile * file)
{
	ui.mdiArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QMdiSubWindow * mdi_sub_wind = new QMdiSubWindow();
	

/*	EDFDEditor * editor = new EDFDEditor();
	mdi_sub_wind->layout()->addWidget(editor);
	//editor->show();
	mdi_sub_wind->show();

	ui.mdiArea->addSubWindow(mdi_sub_wind);
	ui.mdiArea->setActiveSubWindow(mdi_sub_wind);

	editor->openFile(file);*/
}

