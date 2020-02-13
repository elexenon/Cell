#include "customStackedWidget.h"
#include "../../CellCore/Kits/CellUtility.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

#include <QPropertyAnimation>
#include <QPainter>

customStackedWidget::customStackedWidget(QWidget *parent):
    QStackedWidget(parent),
    animi(new QPropertyAnimation(this, "midIndex"))
{
    setEventConnections();
}

void customStackedWidget::paintEvent(QPaintEvent *e)
{
    if(!animiRunning) return;
    QPainter paint(this);
    switch(m_type)
    {
    case _RIGHT:
        paintPrevious(paint, currentIndex());
        paintNext(paint, switchIndex);
        break;
    case _LEFT:
        paintPrevious(paint, switchIndex);
        paintNext(paint, currentIndex());
        break;
    }
    QStackedWidget::paintEvent(e);
}

void customStackedWidget::paintNext(QPainter &painter, int index)
{
    QWidget *nextWidget = widget(index);
    QRect r = geometry();
    nextWidget->resize(r.width(), r.height());
    QPixmap nextPixmap(nextWidget->size());
    nextWidget->render(&nextPixmap);
    double value = midIndex;
    QRectF r1(value, 0.0, r.width() - value, r.height());
    QRectF r2(0.0, 0.0, r.width() - value, r.height());
    painter.drawPixmap(r1, nextPixmap, r2);
}

void customStackedWidget::paintPrevious(QPainter &painter, int index)
{
    QWidget *w = widget(index);
    QPixmap pixmap(w->size());
    w->render(&pixmap);
    QRect r = w->geometry();
    double value = midIndex;
    QRectF r1(0.0, 0.0, value, r.height());
    QRectF r2(r.width() - value, 0, value, r.height());
    painter.drawPixmap(r1, pixmap, r2);
}

void customStackedWidget::setEventConnections()
{
    connect(animi, &QPropertyAnimation::finished, this, &customStackedWidget::animiFinished);
}

void customStackedWidget::switchNext()
{
    if(animiRunning) return;
    animiRunning = true;
    m_type = _RIGHT;
    switchIndex = (currentIndex()+1) % count();
    widget(currentIndex())->hide();
    int sValue = this->width();
    int eValue = 0;
    animi->setEasingCurve(QEasingCurve::InOutQuad);
    animi->setStartValue(sValue);
    animi->setEndValue(eValue);
    animi->setDuration(animiDuration);
    animi->start();
}

void customStackedWidget::switchPrevious()
{
    if(animiRunning) return;
    animiRunning = true;
    m_type = _LEFT;
    switchIndex = (currentIndex()+count()-1) % count();
    widget(currentIndex())->hide();
    int sValue = 0;
    int eValue = this->width();
    animi->setEasingCurve(QEasingCurve::InOutQuad);
    animi->setStartValue(sValue);
    animi->setEndValue(eValue);
    animi->setDuration(animiDuration);
    animi->start();
}

void customStackedWidget::animiFinished()
{
    animiRunning = false;
    widget(currentIndex())->show();
    setCurrentIndex(switchIndex);
}
