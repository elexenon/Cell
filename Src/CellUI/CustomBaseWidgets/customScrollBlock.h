#ifndef CUSTOMSCROLLBLOCK_H
#define CUSTOMSCROLLBLOCK_H

#include "optionBlockBase.h"

class customFlowLayout;
class QButtonGroup;
class customLabel;
class customScrollBlockItem;
class QAbstractButton;

class customScrollBlock : public optionBlockBase
{
    Q_OBJECT
    static unsigned itemSpacing;
public:
    explicit customScrollBlock(const QString &name, QWidget *parent = nullptr);
    ~customScrollBlock() override;

    void
    addItem(const QString &tag, const QString& fileName, int iconWidth, int iconHeight);

    void
    setExclusive(bool value);

    inline const QAbstractButton*
    testButton() const { return button(1); }

    const QAbstractButton*
    button(int ID) const;

    bool
    isEmpty();

    void
    setButtonsChecked(bool checked);

    void
    addExclusiveBlock(customScrollBlock *block);

private:
    //! Inheried from
    //! CellWidgetGlobalInterface.
    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    QVector<customScrollBlock*> *blocks = nullptr;
    customFlowLayout            *flowLayout;
    QButtonGroup                *btnGroup;
    unsigned buttonCount = 1;

Q_SIGNALS:
    void
    clicked(const QString &theme, int buttonID);

private Q_SLOTS:
    void
    processBlocks(const QString &theme, int buttonID);
};

#endif // CUSTOMSCROLLBLOCK_H
