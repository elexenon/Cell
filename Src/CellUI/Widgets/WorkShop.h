// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef WORKSHOP_H
#define WORKSHOP_H

#include "../CustomBaseWidgets/customWinstyleWidget.h"
#include "../../CellCore/Kits/CellUtility.h" // COLOR_SCHEME

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

class Workshop : public customWinstyleWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit Workshop(CellUiGlobal::COLOR_SCHEME mainWindow_mode, QWidget *parent = nullptr);
    ~Workshop();

public:
    virtual void setColor(const QColor& color) override;
    void         _constructed();

private:
    QVBoxLayout *mainLayout;

    WSLoadingDialog           *loadingDialog;
    QMenuBar                  *menuBar;
    customFrame               *leftBlock;
    customFrame               *rightBlock;
    customGradientChangeFrame *statusBar;
    QsciScintilla             *mainEditor;

    QLabel *cntRow;
    QLabel *cntChar;
    QLabel *labelFormat;

    QString            code_prev;
    QString            code_curr;
    CellProjectEntity *PJEntity;
    QString            savePath;
    QShortcut         *ctrlS;
    bool               codeModified = false;

private:
    void InitWorkshop();
    void setEventConnections();

private slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
    void updateStatusBar();
    void saveFile();
    void checkCodeModifiedState();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void constructed();
    void destoryed();
};

#endif // WORKSHOP_H
