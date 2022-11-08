#include "CVisualizationPainter.h"

#include <QGraphicsItem>

namespace Window
{
namespace Visualization
{

    CVisualizationPainter::CVisualizationPainter(QGraphicsView* view) :
        m_view(view)
    {
        m_view->setScene(std::make_unique<QGraphicsScene>().release());
    }

    void CVisualizationPainter::drawBasicScene(const TextsPair& userTexts)
    {
        int start = 0;
        const auto scene = m_view->scene();
        for(const auto letter : userTexts.first)
        {
            QGraphicsRectItem* item1 = new QGraphicsRectItem(start, 200, 80, 80);
            scene->addItem(item1);
            item1->setBrush(QBrush(Qt::white));
            QGraphicsTextItem* tItem1 = new QGraphicsTextItem(QString::fromStdString(std::string(1, letter)));
            scene->addItem(tItem1);

            tItem1->setFont(QFont("Source Code Pro", 25));
            tItem1->setPos(start + 25, 220);
            start += 80;
        }
        start = 0;
        for(const auto letter : userTexts.second)
        {
            QGraphicsRectItem* item1 = new QGraphicsRectItem(start, 300, 80, 80);
            scene->addItem(item1);
            item1->setBrush(QBrush(Qt::white));
            QGraphicsTextItem* tItem1 = new QGraphicsTextItem(QString::fromStdString(std::string(1, letter)));
            scene->addItem(tItem1);

            tItem1->setFont(QFont("Source Code Pro", 25));
            tItem1->setPos(start + 25, 320);
            start += 80;
        }
    }

    void CVisualizationPainter::cleanWholeScene()
    {
        m_view->scene()->clear();
    }

} // Visualization
} // Window
