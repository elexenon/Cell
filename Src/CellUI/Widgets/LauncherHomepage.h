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

class HomeStackGrid;
class HomeStackList;
class customLabel;
class QVBoxLayout;
class QLabel;
class ButtonWithIcon;
class QStackedWidget;
class CellProjectEntity;

class LauncherHomepage : public QWidget
{
friend class Launcher;
    Q_OBJECT

public:
    explicit LauncherHomepage(QWidget *parent = nullptr);
    ~LauncherHomepage() = default;

private:
    QVBoxLayout    *mainLayout;
    HomeStackGrid  *stackGrid;
    HomeStackList  *stackList;
    QStackedWidget *stackedWidget;
    ButtonWithIcon *btnGrid;
    ButtonWithIcon *btnList;
    QLabel         *iconRecentPJ;
    customLabel    *labelRecentPJ;

    Cell::ColorScheme mMode = Cell::ColorScheme::Bright;

    void
    init();

    void
    setEventConnections();

    void
    updateDatas();

public Q_SLOTS:
    void
    setColorScheme(Cell::ColorScheme mode);

    void
    insertProject(const CellProjectEntity &entity);

Q_SIGNALS:
    void openFileByPath(bool isDS, const QString &path);
};

#endif // LauncherHomepage_H
