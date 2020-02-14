// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <QWidget>
#include "../../CellCore/Kits/CellGlobalMacros.h"
#include "../CustomBaseWidgets/CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellUtility.h" // COLOR_SCHEME
#include "../../CellCore/CellProjectEntity.h"
#define WORKSHOP_DEBUG (QTextStream(stdout) << "***WorkShop::")

class WSLoadingDialog;
class QsciScintilla;
class customFrame;
class QLabel;
class QPushButton;
class QStyleSheetLoader;
class QVBoxLayout;
class QSplitter;
class QShortcut;
class customGradientChangeFrame;
class QMenuBar;
class QTreeView;
class QStackedWidget;
class QJsonObject;
class QFileSystemModel;

class Workshop : public QWidget, implements CellWidgetGlobalInterface
{
friend class Launcher;
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit Workshop(CellUiGlobal::COLOR_SCHEME mainWindow_mode, QWidget *parent = nullptr);
    ~Workshop();

public:
    virtual void setColor(const QColor& color) override;
    virtual void setBaseQss(const QString &qss) override;
    virtual void changeToColor(const QColor &startColor, const QColor &targetColor, int duration) override;

private:
    QVBoxLayout *mainLayout;

    WSLoadingDialog           *loadingDialog;
    QMenuBar                  *menuBar;
    customFrame               *leftBlock;
    customFrame               *rightBlock;
    customGradientChangeFrame *statusBar;
    QsciScintilla             *mainEditor;
    QStackedWidget            *leftStackedWidget;
    QTreeView                 *treeView;
    QFileSystemModel          *fileModel;
    QPushButton               *btnDirectory;
    QPushButton               *btnWarning;
    QPushButton               *btnToolChain;

    QLabel *labelCntRow;
    QLabel *labelCntChar;
    QLabel *labelFormat;

    QString            codePrev;
    QString            codeCurr;
    QString            savePath;
    QShortcut         *ctrlS;
    bool               codeModified = false;

    CellProjectEntity  currEntity;

private:
    void         init();
    void         initTreeView();
    void         getProjectEntity(CellProjectEntity &entity);
    void         read(const QJsonObject &json);
    void         write(QJsonObject &json);
    virtual void setEventConnections() override;

private slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
    void         updateStatusBar();
    void         loadFile(const QString &path);
    void         saveFile();
    void         checkCodeModifiedState();
    void         btnDirectoryClicked();
    void         btnWarrningClicked();
    void         btnToolChainClicked();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void constructed();
    void destoryed();
    void projectUpdate(CellProjectEntity &entity);
};

#endif // WORKSHOP_H
