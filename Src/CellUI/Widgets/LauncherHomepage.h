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
#include "../../CellCore/Kits/CellUtility.h" // ColorScheme

class QVBoxLayout;
class QLabel;
class ButtonWithIcon;
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
    ButtonWithIcon     *btnGrid;
    ButtonWithIcon     *btnList;
    QLabel             *iconRecentPJ;
    QLabel             *labelRecentPJ;

    Cell::ColorScheme mMode = Cell::ColorScheme::Bright;

    void
    init();

    void
    setEventConnections();

    void
    initTableView();

    void
    updateDatas();

    bool
    tableExists(const char *tableName);

public Q_SLOTS:
    void
    setColorScheme(Cell::ColorScheme mode);

private Q_SLOTS:
    void
    updateDatasByWS(CellProjectEntity &entity);

    void
    btnGridClicked();

    void
    btnListClicked();

    void
    tableDoubleClicked(const QModelIndex &index);

Q_SIGNALS:
    void getProjectPath(const QString &path);
};

#endif // LauncherHomepage_H
