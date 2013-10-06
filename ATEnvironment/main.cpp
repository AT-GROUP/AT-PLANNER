#include "ATEnvironment.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ATEnvironment w;
	//w.show();
	w.showMaximized();

	return a.exec();
}
