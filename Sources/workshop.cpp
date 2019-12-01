// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QPropertyAnimation>
#include <QFrame>
#include <QLabel>
#include <QDebug>
#include <QCursor>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerpython.h>
#include "Headers/Kits/cell_util.h"
#include "Headers/Kits/qstylesheetloader.hpp"
#include "Headers/wswelcomedialog.h"
#include "Headers/Kits/customFrame.h"
#include "Headers/workshop.h"
#include "ui_workshop.h"
#define CELL_DEBUG

Workshop::Workshop(CellGlobal::COLOR_SCHEME mainWindow_mode, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Workshop),
    welcomeDialog(new WSWelcomeDialog),
    menuBar(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    leftBlock(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    rightBlock(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    statusBar(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    mainEditor(new QsciScintilla(this)),
    m_color(CellGlobal::COLOR_SCHEME::_BRIGHT),
    verticalLayout(new QVBoxLayout(this)),
    splitter(new QSplitter(this))
{
    ui->setupUi(this);
    InitWorkshop();
    if(m_mode != mainWindow_mode)
        setColorScheme(mainWindow_mode);
}

Workshop::~Workshop()
{
    delete ui;
}

void Workshop::InitWorkshop()
{
    // Functional.
    setAttribute(Qt::WA_DeleteOnClose);

    verticalLayout->setSpacing(0);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    verticalLayout->setContentsMargins(0,0,0,0);

    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setOrientation(Qt::Horizontal);
    splitter->setOpaqueResize(true);
    splitter->setHandleWidth(1);
    splitter->setChildrenCollapsible(false);
    splitter->setStyleSheet(QStringLiteral("QSplitter::handle{background-color:grey;}"));

    menuBar->setParent(this);
    menuBar->setGeometry(0, 0, 1400, 39);
    menuBar->setMaximumSize(65535,39);

    verticalLayout->addWidget(menuBar);

    ui->BtnFile->setParent(menuBar);
    ui->BtnEdit->setParent(menuBar);
    ui->BtnBuild->setParent(menuBar);
    ui->BtnDebug->setParent(menuBar);
    ui->BtnKits->setParent(menuBar);
    ui->BtnView->setParent(menuBar);
    ui->BtnHelp->setParent(menuBar);

    mainEditor->setGeometry(370, 39, 660 ,732);
    mainEditor->setMarginWidth(0, 62);
    mainEditor->setUtf8(true);

    mainEditor->setWrapIndentMode(QsciScintilla::WrapIndentFixed);
    mainEditor->setWrapMode(QsciScintilla::WrapNone);
    mainEditor->setWrapVisualFlags(QsciScintilla::WrapFlagByText, QsciScintilla::WrapFlagNone, 0);
    mainEditor->setTabWidth(4);
    mainEditor->setCaretLineVisible(true);

    QsciLexer *lexPY = new QsciLexerPython();
    lexPY->setFont(QFont(QStringLiteral("Courier New"), 11));
    mainEditor->setLexer(lexPY);

    setEventConnections();

    leftBlock->setGeometry(0, 39, 370, 732);
    leftBlock->setMinimumSize(200,50);

    rightBlock->setGeometry(1030, 39, 370, 732);
    rightBlock->setMinimumSize(200,50);

    splitter->addWidget(leftBlock);
    splitter->addWidget(mainEditor);
    splitter->addWidget(rightBlock);
    splitter->setCollapsible(0,true);
    splitter->setCollapsible(1,false);
    splitter->setCollapsible(2,true);

#ifdef CELL_DEBUG
    qDebug() << splitter->indexOf(mainEditor);
#endif

    verticalLayout->addWidget(splitter);

    statusBar->setGeometry(0, 771, 1400, 29);
    statusBar->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(210,210,210);}"));
    statusBar->setMaximumSize(65535,29);

    verticalLayout->addWidget(statusBar);

    cntRow = new QLabel(statusBar);
    cntChar = new QLabel(statusBar);
    labelFormat = new QLabel(statusBar);

    menuBar->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(65,152,197);}"));

    ui->BtnFile->setFont(QFont("微软雅黑", 10));
    ui->BtnEdit->setFont(QFont("微软雅黑", 10));
    ui->BtnBuild->setFont(QFont("微软雅黑", 10));
    ui->BtnDebug->setFont(QFont("微软雅黑", 10));
    ui->BtnKits->setFont(QFont("微软雅黑", 10));
    ui->BtnView->setFont(QFont("微软雅黑", 10));
    ui->BtnHelp->setFont(QFont("微软雅黑", 10));

    CellGlobal::multiModulesOneStyleSheet({ui->BtnFile,ui->BtnEdit,ui->BtnBuild,
                                      ui->BtnDebug,ui->BtnKits,ui->BtnView,ui->BtnHelp},
                                          QStringLiteral("QPushButton{color:rgb(255,255,255);background-color:rgb(65,152,197);}"));
    // Main Editor.
    mainEditor->setFrameShape(QFrame::NoFrame);
    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("WorkshopEditor.css"));
    mainEditor->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    mainEditor->setFont(QFont("Courier New", 11));
    mainEditor->setPaper(QColor(249,250,250));

    mainEditor->setMarginsBackgroundColor(QColor(240,240,240));
    mainEditor->setCaretLineBackgroundColor(QColor(240,240,240));

    // Two Blocks.
    CellGlobal::multiModulesOneStyleSheet({leftBlock, rightBlock},
                                       QStringLiteral("QFrame{background-color:rgb(235,235,235);}"));

    // Labels.
    cntRow->setGeometry(370, 0, cntRow->width(), cntRow->height());
    cntRow->setFont(QFont(QStringLiteral("微软雅黑 Light")));
    cntRow->setText(QStringLiteral("Row: 0"));

    cntChar->setGeometry(450, 0, cntChar->width(), cntChar->height());
    cntChar->setFont(QFont(QStringLiteral("微软雅黑 Light")));
    cntChar->setText(QStringLiteral("Char: 0"));

    labelFormat->setGeometry(1030 - labelFormat->width(), 0, labelFormat->width(), labelFormat->height());
    labelFormat->setFont(QFont(QStringLiteral("微软雅黑 Light")));
    labelFormat->setText(QStringLiteral("Format: UTF-8"));

    // Functional.
    welcomeDialog->show();
    welcomeDialog->progress();

    mainEditor->setText("#!/usr/bin/python\n"
                        "#conding=utf-8\n"
                        "import sys\n");
}

void Workshop::setEventConnections()
{
    connect(mainEditor, SIGNAL(textChanged()), this, SLOT(updateStatusBar()));
}

void Workshop::_constructed()
{
    emit constructed();
}

void Workshop::setColorScheme(CellGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    if(mode == CellGlobal::COLOR_SCHEME::_DARK){
        m_mode = CellGlobal::COLOR_SCHEME::_DARK;

        CellGlobal::multiModulesOneStyleSheet({cntRow,cntChar,labelFormat},
                                               QStringLiteral("QLabel{color:rgb(255,255,255);}"));

        CellGlobal::setPropertyAnimation({animi_MenuBar},
                                     "color",
                                     menuBar->color(),
                                     Cell_Const::GRAYLEVEL45,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {menuBar}, nullptr);
        CellGlobal::setPropertyAnimation({animi_StatusBar},
                                     "color",
                                     statusBar->color(),
                                     Cell_Const::GRAYLEVEL45,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {statusBar}, nullptr);

        CellGlobal::setPropertyAnimation({animi_LeftBlock,animi_RightBlock},
                                     "color",
                                     leftBlock->color(),
                                     Cell_Const::GRAYLEVEL70,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {leftBlock,rightBlock}, nullptr);
    }
    else{
        m_mode = CellGlobal::COLOR_SCHEME::_BRIGHT;

        CellGlobal::multiModulesOneStyleSheet({cntRow,cntChar,labelFormat},
                                          QStringLiteral("QLabel{color:rgb(0, 0, 0);}"));

        CellGlobal::setPropertyAnimation({animi_MenuBar},
                                         "color",
                                         menuBar->color(),
                                         QColor(65,152,197),
                                         CellGlobal::CELL_GLOBALANIMIDURATION,
                                         QEasingCurve::InOutCubic,
                                         {menuBar}, nullptr);
        CellGlobal::setPropertyAnimation({animi_StatusBar},
                                         "color",
                                         statusBar->color(),
                                         QColor(210,210,210),
                                         CellGlobal::CELL_GLOBALANIMIDURATION,
                                         QEasingCurve::InOutCubic,
                                         {statusBar}, nullptr);

        CellGlobal::setPropertyAnimation({animi_LeftBlock,animi_RightBlock},
                                         "color",
                                         leftBlock->color(),
                                         QColor(235,235,235),
                                         CellGlobal::CELL_GLOBALANIMIDURATION,
                                         QEasingCurve::InOutCubic,
                                         {leftBlock,rightBlock}, nullptr);
    }
}

void Workshop::updateStatusBar()
{
    QCursor cursor = mainEditor->cursor();
#ifdef CELL_DEBUG
    qDebug() << cursor.pos();
#endif
    cntRow->setText("Row: " + QString::number(mainEditor->lines()));

    QString tmp = mainEditor->text();
    cntChar->setText("Char: " + QString::number(tmp.length()));
}

const QColor Workshop::color() const
{
    return m_color;
}

void Workshop::setColor(const QColor color)
{
    m_color = color;
    setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
}

void Workshop::closeEvent(QCloseEvent*)
{
    emit destoryed();
    welcomeDialog->close();
}
