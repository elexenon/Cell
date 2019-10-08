/*

  CREATED BY HENGYI YU 2019/10/06
  This class achieve both window drop shadow effet & "color" property.

*/
#ifndef DROPSHADOWWIDGET_H
#define DROPSHADOWWIDGET_H

#include <QWidget>

class DropShadowWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit DropShadowWidget(QWidget *parent = nullptr);
    ~DropShadowWidget() = default;

public:
    const QColor color() const;
    void setColor(const QColor color);
    const QColor b_color() const;
    const QColor d_color() const;

protected:
    QColor m_color;
    QColor bright;
    QColor dark;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void LoadWinStyle(QWidget *obj);
#endif
};

#endif // DROPSHADOWWIDGET_H
