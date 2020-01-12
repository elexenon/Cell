// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
//
// This is part of main launcher's stackwidget.
#ifndef LauncherHomepage_H
#define LauncherHomepage_H

#include <QWidget>
#include "../../CellCore/Kits/CellUtility.h" // COLOR_SCHEME

namespace Ui {
class LauncherHomepage;
}

class LauncherHomepage : public QWidget
{
    Q_OBJECT

public:
    explicit LauncherHomepage(QWidget *parent = nullptr);
    ~LauncherHomepage();

private:
    Ui::LauncherHomepage *ui;

private:
    CellUiGlobal::COLOR_SCHEME m_mode;

private:
    void Init();
    void setAllGraphBtnsUnchecked();

private slots:
    void setColorScheme(CellUiGlobal::COLOR_SCHEME mode);
    void on_Btn_grid_clicked();
    void on_Btn_list_clicked();
};

#endif // LauncherHomepage_H
