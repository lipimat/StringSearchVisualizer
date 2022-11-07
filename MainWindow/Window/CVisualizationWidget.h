#pragma once

#include <QWidget>
#include "../AlgorithmsModule/IVisualizationWidget.h"

namespace Window
{

    class CVisualizationWidget : public QWidget, public IVisualizationWidget
    {
    public:

        explicit CVisualizationWidget(QWidget*);

        void paintEvent(QPaintEvent*) override;

        QPaintEngine* paintEngine() const override { return QWidget::paintEngine(); };

        void updateWithGivenFunction(std::function<void()>) override;

        ~CVisualizationWidget() = default;

    private:

        std::function<void()> m_paintingFunction;

    };

} //Window
