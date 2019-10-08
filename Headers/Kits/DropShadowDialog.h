/*

  CREATED BY HENGYI YU 2019/10/06
  This class achieve both window drop shadow effet & "color" property.

*/
#ifndef DROPSHADOWDIALOG_H
#define DROPSHADOWDIALOG_H

#include <QDialog>

class DropShadowDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit DropShadowDialog(QWidget *parent = nullptr);
    ~DropShadowDialog() = default;

public:
    const QColor color() const;
    void setColor(const QColor color);

protected:
    QColor m_color;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void LoadWinStyle(QDialog *obj);
#endif
};


#endif // DROPSHADOWDIALOG_H
