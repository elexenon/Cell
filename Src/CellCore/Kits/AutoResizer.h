// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef AUTORESIZER_H
#define AUTORESIZER_H

class AutoResizer{
public:
    explicit AutoResizer() = default;
    explicit AutoResizer(QWidget *target,double origiWidth, double origiHeight);

private:
    QWidget *targetObj;
    double horRatio;
    double verRatio;
    double fontRatio;
    double originalWidth;
    double originalHeight;
};

#endif // AUTORESIZER_H
