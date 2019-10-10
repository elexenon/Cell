#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <QWidget>
#include <QPropertyAnimation>
#include "Kits/_utility.h"
#include "workshopdialog_1.h"

namespace Ui {
class Workshop;
}

class Workshop : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit Workshop(QWidget *parent = nullptr);
    ~Workshop();

public:
    const QColor color() const;
    void  setColor(const QColor color);

private:
    Ui::Workshop *ui;
    QPropertyAnimation *animi;

    WorkshopDialog_1 *welcomeDialog;

    QColor m_color;

private:
    void InitWorkshop();

private slots:
    void setColorScheme(COLOR_SCHEME mode);
};

#endif // WORKSHOP_H
