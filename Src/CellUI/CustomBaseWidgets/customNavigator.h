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
    static int buttonHeight;
public:
    explicit customNavigator(QWidget *parent = nullptr);
    ~customNavigator() = default;

    //! Custom navigator will create a correspounding
    //! "ButtonWithText" of "checkable" attribute on-
    //! ce a "customOptionBlock" is appended by user.
    void
    jointBlock(const customOptionBlock *block);

    //! Set the top margin of main layout.
    void
    setTopMargin(int value);

    //! Set the height of each "ButtonWithText"
    void
    setButtonHeight(int value);

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
