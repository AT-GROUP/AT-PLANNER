#include <MainWindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow b;
    b.visualizePlan();
    b.show();
    return a.exec();
}
