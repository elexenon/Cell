// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMLINE_H
#define CUSTOMLINE_H

#include "customFrame.h"
#include "../../CellCore/Kits/CellUtility.h" // LINE_TYPE

class customLine : public customFrame{
    Q_OBJECT
    const QString BASEQSS;
public:
    explicit customLine(const QString &qss, QWidget *parent = nullptr,
                        const CellUiGlobal::LINE_TYPE &shape = CellUiGlobal::LINE_TYPE::HLine);
    ~customLine() = default;

private:
    void Init();

    CellUiGlobal::LINE_TYPE shape;
};


#endif // CUSTOMLINE_H
