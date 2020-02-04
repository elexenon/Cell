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

class QVBoxLayout;
class QLabel;
class QPushButton;
class QScrollArea;
class QComboBox;

class LauncherHomepage : public QWidget
{
    Q_OBJECT

public:
    explicit LauncherHomepage(QWidget *parent = nullptr);
    ~LauncherHomepage() = default;

private:
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QPushButton *BtnGrid;
    QPushButton *BtnList;
    QLabel      *labelRecentPJ;
    QLabel      *labelSort;
    QFrame      *splitterLine;
    QComboBox   *cBoxSort;

    CellUiGlobal::COLOR_SCHEME m_mode = CellUiGlobal::COLOR_SCHEME::_BRIGHT;

    void Init();
    void setAllGraphBtnsUnchecked();

private slots:
    void setColorScheme(CellUiGlobal::COLOR_SCHEME mode);
    void on_Btn_grid_clicked();
    void on_Btn_list_clicked();
};

#endif // LauncherHomepage_H
