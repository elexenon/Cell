// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef OPTIONBLOCKBASE_H
#define OPTIONBLOCKBASE_H

class customLabel;
class QVBoxLayout;

#include "customFrame.h"

class optionBlockBase : public customFrame{
friend class customNavigator;
    Q_OBJECT
public:
    explicit optionBlockBase(const QString& name, QWidget *parent = nullptr);
    virtual ~optionBlockBase() = default;

protected:
    virtual void
    init() override = 0;

    virtual void
    enterEvent(QEvent*) override;

    void
    addThemeTag(const QString&);

    QVBoxLayout *mainLayout;
    QString     _theme;
    customLabel *theme;

Q_SIGNALS:
    void
    entered(const QString&);
};

#endif // OPTIONBLOCKBASE_H
