#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>

#include <ATItems/AT_Plan.h>
#include <QtItems/MainWindow.h>
#include <QtItems/G_PlanItem.h>



namespace Ui
{
    class Visualizator;
}

class Visualizator: public QWidget
    {
        Q_OBJECT
        public:
            explicit Visualizator(QWidget *parent = 0);
            ~Visualizator();
            void visualizePlan();
        private:
            QGraphicsScene *m_scene;
            QGraphicsView *graphicsView;
            AT_Plan m_AT_Plan;
            void visualizeItem(AT_PlanItem* a, int x_pos, int y_pos);
            Ui::Visualizator *ui;
    };

#endif // MAINWINDOW_H
