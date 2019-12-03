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
#include "../../CellCore/Kits/CellUtility.h" // COLOR_SCHEME

namespace Ui {
class Workshop;
}

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

class Workshop : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit Workshop(CellGlobal::COLOR_SCHEME mainWindow_mode, QWidget *parent = nullptr);
    ~Workshop() override;

public:
    const QColor color() const;
    void  setColor(const QColor color);

    void _constructed();

private:
    Ui::Workshop *ui;
    QPropertyAnimation *animi_MenuBar;
    QPropertyAnimation *animi_StatusBar;
    QPropertyAnimation *animi_LeftBlock;
    QPropertyAnimation *animi_RightBlock;

    WSLoadingDialog  *loadingDialog;
    customFrame      *menuBar;
    customFrame      *leftBlock;
    customFrame      *rightBlock;
    customFrame      *statusBar;
    QLabel           *cntRow;
    QLabel           *cntChar;
    QLabel           *labelFormat;
    QsciScintilla    *mainEditor;

    QColor                   m_color;
    CellGlobal::COLOR_SCHEME m_mode;

    QVBoxLayout      *verticalLayout;
    QSplitter        *splitter;

private:
    void InitWorkshop();
    void setEventConnections();

private slots:
    void setColorScheme(CellGlobal::COLOR_SCHEME mode);
    void updateStatusBar();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void constructed();
    void destoryed();
};

#endif // WORKSHOP_H
