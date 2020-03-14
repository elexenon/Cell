#ifndef customScrollBlockItem_H
#define customScrollBlockItem_H

#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

class ButtonWithIcon;
class customLabel;
class QVBoxLayout;

class customScrollBlockItem : public QWidget, implements CellWidgetGlobalInterface
{
friend class customScrollBlock;
    Q_OBJECT
    static unsigned _buttonWidth;
    static unsigned _unitSpacing;
    static unsigned _fontSize;
public:
    explicit customScrollBlockItem(QWidget *parent = nullptr);

    void
    initModules(const QString &tag, const QString& fileName, int iconWidth, int iconHeight);

    inline
    ButtonWithIcon* button() const { return btn; }

    static inline unsigned
    buttonWidth() { return customScrollBlockItem::_buttonWidth; }

    static inline unsigned
    unitSpacing() { return customScrollBlockItem::_unitSpacing; }

public Q_SLOTS:
    virtual void
    setColorScheme(Cell::ColorScheme mode) override;

private:
    virtual void
    init() override;

    inline virtual void
    setEventConnections() override {};

    virtual void
    setColor(const QColor &color) override;

    virtual void
    changeToColor(const QColor& startColor, const QColor& targetColor, int duration) override;

    QVBoxLayout    *mainLayout;
    ButtonWithIcon *btn;
    customLabel    *label;
};

#endif // customScrollBlockItem_H
