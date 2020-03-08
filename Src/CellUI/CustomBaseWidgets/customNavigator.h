#ifndef CUSTOMNAVIGATOR_H
#define CUSTOMNAVIGATOR_H

#include "customFrame.h"

class customOptionBlock;
class ButtonWithText;
class QVBoxLayout;
class QButtonGroup;

class customNavigator : public customFrame
{
    Q_OBJECT
public:
    explicit customNavigator(QWidget *parent = nullptr);
    ~customNavigator() = default;

    void
    jointBlock(const customOptionBlock *block);

private:
    QVBoxLayout            *mainLayout;
    QButtonGroup           *btnGroup;
    QMap<QString, unsigned> blockBtnMap;

protected:
    //! Inhrited from
    //! CellWidgetGlobalInterface.
    virtual void
    init() override;

private Q_SLOTS:
    void
    setCurr(const QString &name);
};

#endif // CUSTOMNAVIGATOR_H
