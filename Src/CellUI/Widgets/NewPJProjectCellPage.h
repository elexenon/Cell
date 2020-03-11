// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef NEWPJPROJECTPAGE_H
#define NEWPJPROJECTPAGE_H

#include "../CustomBaseWidgets/newPJPageBase.h"

class QComboBox;


class NewPJProjectCellPage : public newPJPageBase{
    Q_OBJECT
public:
    explicit NewPJProjectCellPage(QWidget *parent = nullptr);
    ~NewPJProjectCellPage() = default;

private:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;
};

#endif // NEWPJPROJECTPAGE_H
