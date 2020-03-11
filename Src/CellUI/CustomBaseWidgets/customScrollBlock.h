#ifndef CUSTOMSCROLLBLOCK_H
#define CUSTOMSCROLLBLOCK_H

#include "optionBlockBase.h"

class customScrollBlock : public optionBlockBase
{
    Q_OBJECT
public:
    explicit customScrollBlock(const QString &name, QWidget *parent = nullptr);
    ~customScrollBlock() = default;

private:
    virtual void
    init() override;
};

#endif // CUSTOMSCROLLBLOCK_H
