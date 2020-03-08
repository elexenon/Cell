#ifndef CUSTOMNAVIGATOR_H
#define CUSTOMNAVIGATOR_H

#include "../../CellCore/CellNamespace.h"

class customOptionBlock;
class ButtonWithText;
class QVBoxLayout;
class QButtonGroup;

class customNavigator : public QWidget
{
    Q_OBJECT
public:
    explicit customNavigator(QWidget *parent = nullptr);
    ~customNavigator() = default;

    void jointBlock(const customOptionBlock *block);

private:
    void init();

    QVBoxLayout            *mainLayout;
    QButtonGroup           *btnGroup;
    QMap<QString, unsigned> blockBtnMap;
    QList<ButtonWithText*>  btns;

protected:
    //virtual void paintEvent(QPaintEvent *event) override;

public Q_SLOTS:
    void setColorScheme(Cell::ColorScheme mode);

private Q_SLOTS:
    void setCurr(const QString &name);
};

#endif // CUSTOMNAVIGATOR_H
