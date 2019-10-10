#include "Headers/workshop.h"
#include "ui_workshop.h"

Workshop::Workshop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Workshop),
    welcomeDialog(new WorkshopDialog_1(this))
{
    ui->setupUi(this);
    InitWorkshop();
}

Workshop::~Workshop()
{
    delete ui;
}

void Workshop::InitWorkshop()
{
    // Functional.
    welcomeDialog->show();

}

void Workshop::setColorScheme(COLOR_SCHEME mode)
{
    if(mode == COLOR_SCHEME::_DARK)
        UTILITY::setPropertyAnimation(animi, "color", color(), MAINWINDOW_DARK, 500,
                         QEasingCurve::Linear, this, true, nullptr);
    else
        UTILITY::setPropertyAnimation(animi, "color", color(), MAINWINDOW_BRIGHT, 500,
                         QEasingCurve::Linear, this, true, nullptr);
}

const QColor Workshop::color() const
{
    return m_color;
}

void Workshop::setColor(const QColor color)
{
    m_color = color;
    QString qss=QString("background-color:rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue());
    setStyleSheet(qss);
}
