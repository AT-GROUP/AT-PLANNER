#include <QtItems/MainWindow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Visualizator b;
    b.visualizePlan();
    b.show();
    return a.exec();
}
