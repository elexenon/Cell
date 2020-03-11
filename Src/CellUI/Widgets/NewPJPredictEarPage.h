// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef NEWPJPREDICTEARPAGE_H
#define NEWPJPREDICTEARPAGE_H

#include "../CustomBaseWidgets/newPJPageBase.h"

class NewPJPredictEarPage : public newPJPageBase{
    Q_OBJECT
public:
    explicit NewPJPredictEarPage(QWidget *parent = nullptr);
    ~NewPJPredictEarPage() = default;

private:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;
};

#endif // NEWPJPREDICTEARPAGE_H
