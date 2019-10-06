/*

  CREATED BY HENGYI YU 2019/10/06

*/
#ifndef DROPSHADOWWIDGET_H
#define DROPSHADOWWIDGET_H

#include <QWidget>

class DropShadowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DropShadowWidget(QWidget *parent = nullptr);
    ~DropShadowWidget() = default;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void LoadWinStyle(QWidget *obj);
#endif
};

#endif // DROPSHADOWWIDGET_H
