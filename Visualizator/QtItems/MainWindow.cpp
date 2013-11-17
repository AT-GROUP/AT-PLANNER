#include <QGridLayout>

#include <QtItems/MainWindow.h>
#include <QtItems/G_PlanItem.h>
#include <ui_Visualizator.h>

Visualizator::Visualizator(QWidget *parent) :
    QWidget(parent)
    {
        ui->setupUi(this);
        setLayout(new QGridLayout());
        graphicsView = new QGraphicsView();
            layout()->addWidget(graphicsView);
            graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_scene = new QGraphicsScene(0,0,1600,900);
        graphicsView->fitInView(0,0,3200,1800);
        m_AT_Plan.generatePlan((char*)"123");
        graphicsView->setScene(m_scene);
    }
Visualizator::~Visualizator()
    {
        delete ui;
    }
void Visualizator::visualizePlan()
    {
        int x_pos;
        int y_pos=0;
        for(AT_PlanItem* item: m_AT_Plan.getItems())
        {
            x_pos = item->getStartTime();
            visualizeItem(item, x_pos, y_pos);
            y_pos = y_pos + 30;
        }
    }
void Visualizator::visualizeItem(AT_PlanItem* a, int x_pos, int y_pos)
    {
        G_PlanItem* m_gItem = new G_PlanItem(a);
        m_gItem->setPos(x_pos, y_pos);
        m_scene->addItem(m_gItem);
    }
