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

class WSLoadingDialog;
class QsciScintilla;
class customFrame;
class QLabel;
class QPushButton;
class QStyleSheetLoader;
class QPropertyAnimation;
class QGraphicsDropShadowEffect;
class QFrame;
class QVBoxLayout;
class QHBoxLayout;
class QSplitter;
class CellProjectEntity;
class QShortcut;
class customGradientChangeFrame;
class QMenuBar;
class QTreeView;
class QStackedWidget;

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
    void         _constructed();

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
    QPushButton               *btnDirectory;
    QPushButton               *btnWarning;
    QPushButton               *btnToolChain;

    QLabel *cntRow;
    QLabel *cntChar;
    QLabel *labelFormat;

    QString            code_prev;
    QString            code_curr;
    QString            savePath;
    QShortcut         *ctrlS;
    bool               codeModified = false;

    CellProjectEntity  currEntity;

private:
    void initWorkshop();
    virtual void setEventConnections() override;
    void initTreeView();
    inline
    void getProjectEntity(CellProjectEntity &entity) { currEntity = entity; }

private slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
    void updateStatusBar();
    void saveFile();
    void checkCodeModifiedState();
    void btnDirectoryClicked();
    void btnWarrningClicked();
    void btnToolChainClicked();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void constructed();
    void destoryed();
    void fileSaved(CellProjectEntity &entity);
};

#endif // WORKSHOP_H
