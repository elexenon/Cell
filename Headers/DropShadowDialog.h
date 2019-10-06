/*

  CREATED BY HENGYI YU 2019/10/06

*/
#ifndef DROPSHADOWDIALOG_H
#define DROPSHADOWDIALOG_H

#include <QDialog>

class DropShadowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DropShadowDialog(QWidget *parent = nullptr);
    ~DropShadowDialog() = default;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void LoadWinStyle(QDialog *obj);
#endif
};


#endif // DROPSHADOWDIALOG_H
