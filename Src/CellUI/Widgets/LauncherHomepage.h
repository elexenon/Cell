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
class QTableView;
class QStackedWidget;
class CellProjectEntity;
class QStandardItemModel;

class LauncherHomepage : public QWidget
{
friend class Launcher;
    Q_OBJECT

public:
    explicit LauncherHomepage(QWidget *parent = nullptr);
    ~LauncherHomepage() = default;

private:
    QVBoxLayout        *mainLayout;
    QStackedWidget     *stackedWidget;
    QTableView         *tableView;
    QStandardItemModel *itemModel;
    QScrollArea        *scrollArea;
    QPushButton        *btnGrid;
    QPushButton        *btnList;
    QLabel             *iconRecentPJ;
    QLabel             *labelRecentPJ;

    CellUiGlobal::COLOR_SCHEME m_mode = CellUiGlobal::COLOR_SCHEME::_BRIGHT;

    void init();
    void setEventConnections();
    void initTableView();
    void updateDatas();
    bool tableExists(const char *tableName);

private Q_SLOTS:
    void setColorScheme(CellUiGlobal::COLOR_SCHEME mode);
    void updateDatasByWS(CellProjectEntity &entity);
    void Btn_grid_clicked();
    void Btn_list_clicked();
};

#endif // LauncherHomepage_H
