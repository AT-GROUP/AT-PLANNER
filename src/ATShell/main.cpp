#include "ATApplication.h"
#include "ATEnvironment.h"
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

int main(int argc, char *argv[])
{
	ATApplication a(argc, argv);
	ATEnvironment w(&a);
	//w.show();
	w.showMaximized();

	if(argc > 1)
	{
		QString project_path(argv[1]);
		qDebug() << "Opening project " << project_path;

		w.openProject(project_path.toStdString());
	}

	return a.exec();
}

//D:\Projects\AT-PLANNER\test_projects\SimpleIES\SimpleIES.atprj