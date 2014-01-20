#include "ATApplication.h"
#include "ATEnvironment.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	ATApplication a(argc, argv);
	ATEnvironment w(&a);
	//w.show();
	w.showMaximized();

	return a.exec();
}
