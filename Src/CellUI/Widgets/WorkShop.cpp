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
#include <QShortcut>
#include <QMenuBar>
#include <QTreeView>
#include <QMenu>
#include <QScrollBar>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexercpp.h>

#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customGradientChangeFrame.h"
#include "../../CellCore/CellProjectEntity.h"
#include "../../CellCore/Kits/CellUtility.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"
#include "WSLoadingDialog.h"
#include "WorkShop.h"
#include "ui_WorkShop.h"
#define CELL_DEBUG

Workshop::Workshop(CellUiGlobal::COLOR_SCHEME mainWindow_mode, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Workshop),
    loadingDialog(new WSLoadingDialog),
    menuBar(new QMenuBar),
    leftBlock(new customFrame(CellUiConst::QSS_CUSTOMFRAME, this)),
    rightBlock(new customFrame(CellUiConst::QSS_CUSTOMFRAME, this)),
    statusBar(new customGradientChangeFrame(CellUiConst::QSS_CUSTOMFRAME, QColor(74,207,90) ,this)),
    mainEditor(new QsciScintilla(this)),
    m_mode(CellUiGlobal::COLOR_SCHEME::_BRIGHT),
    verticalLayout(new QVBoxLayout(this)),
    splitter(new QSplitter(this)),
    savePath(""),
    ctrlS(new QShortcut(this)),
    codeModified(false)
{
    ui->setupUi(this);
    InitWorkshop();
    if(m_mode != mainWindow_mode)
        setColorScheme(mainWindow_mode);
}

Workshop::~Workshop()
{
    delete ui;
    delete PJEntity;
}

void Workshop::InitWorkshop()
{
    // Functional.
    setAttribute(Qt::WA_DeleteOnClose);

    verticalLayout->setSpacing(0);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    verticalLayout->setContentsMargins(0,0,0,0);
    verticalLayout->addWidget(menuBar);

    using CellEntityTools::styleSheetLoader;
    styleSheetLoader->setStyleSheetName(QStringLiteral("WorkshopMenuBar.css"));
    menuBar->setStyleSheet(styleSheetLoader->styleSheet());
    menuBar->setFont(QFont("Microsoft YaHei UI"));
    menuBar->setFixedHeight(27);


    QMenu *fileMenu = new QMenu(menuBar);
    fileMenu->setTitle("文件(F)");
    fileMenu->addAction("OpenFile");

    QMenu *editMenu = new QMenu(menuBar);
    editMenu->setTitle("编辑(E)");

    QMenu *buildMenu = new QMenu(menuBar);
    buildMenu->setTitle("构建(B)");

    QMenu *helpMenu = new QMenu(menuBar);
    helpMenu->setTitle("构建(D)");

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(buildMenu);
    menuBar->addMenu(helpMenu);

    splitter->setObjectName(QStringLiteral("splitter"));
    splitter->setOrientation(Qt::Horizontal);
    splitter->setOpaqueResize(true);
    splitter->setHandleWidth(1);
    splitter->setChildrenCollapsible(false);
    splitter->setStyleSheet(QStringLiteral("QSplitter::handle{background-color:grey;}"));

    mainEditor->setMarginWidth(0, 62);
    mainEditor->setUtf8(true);
    mainEditor->setMinimumWidth(500);
    mainEditor->setWrapIndentMode(QsciScintilla::WrapIndentFixed);
    mainEditor->setWrapMode(QsciScintilla::WrapNone);
    mainEditor->setWrapVisualFlags(QsciScintilla::WrapFlagByText, QsciScintilla::WrapFlagNone, 0);
    mainEditor->setTabWidth(4);
    mainEditor->setCaretLineVisible(true);

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("WorkshopEditorVerticalScrollBar.css"));
    QScrollBar *verticalBar = mainEditor->verticalScrollBar();
    verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("WorkshopEditorHorizontalScrollBar.css"));
    QScrollBar *horizontalBar = mainEditor->horizontalScrollBar();
    horizontalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    QsciLexer *lexCPP = new QsciLexerCPP();
    lexCPP->setFont(QFont(QStringLiteral("Courier New"), 11));
    mainEditor->setLexer(lexCPP);

    setEventConnections();

    leftBlock->setMinimumWidth(300);
    QVBoxLayout *leftBlockLayout = new QVBoxLayout;
    leftBlockLayout->setMargin(0);
    leftBlockLayout->addStretch(1);
    leftBlockLayout->addWidget(CellUiGlobal::getLine(CellUiGlobal::LINE_TYPE::HLine));
    leftBlockLayout->addStretch(25);
    leftBlock->setLayout(leftBlockLayout);

    rightBlock->setMinimumWidth(300);
    QVBoxLayout *rightBlockLayout = new QVBoxLayout;
    rightBlockLayout->setMargin(0);
    rightBlockLayout->addStretch(1);
    rightBlockLayout->addWidget(CellUiGlobal::getLine(CellUiGlobal::LINE_TYPE::HLine));
    rightBlockLayout->addStretch(25);
    rightBlock->setLayout(rightBlockLayout);

    splitter->addWidget(leftBlock);
    splitter->addWidget(mainEditor);
    splitter->addWidget(rightBlock);
    splitter->setCollapsible(0,true);
    splitter->setCollapsible(1,false);
    splitter->setCollapsible(2,true);

    verticalLayout->addWidget(splitter);

    statusBar->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(210,210,210);}"));
    statusBar->setMaximumSize(65535,29);
    statusBar->setColor(CellUiConst::GRAYLEVEL218);

    verticalLayout->addWidget(statusBar);

    cntRow = new QLabel(statusBar);
    cntChar = new QLabel(statusBar);
    labelFormat = new QLabel(statusBar);

    // Main Editor.
    mainEditor->setFrameShape(QFrame::NoFrame);
    mainEditor->setFont(QFont("Courier New", 11));
    mainEditor->setPaper(QColor(249,250,250));

    mainEditor->setMarginsBackgroundColor(QColor(240,240,240));
    mainEditor->setCaretLineBackgroundColor(QColor(240,240,240));

    // Two Blocks.
    CellUiGlobal::multiModulesOneStyleSheet({leftBlock, rightBlock},
                                       QStringLiteral("QFrame{background-color:rgb(235,235,235);}"));

    // Labels.
    cntRow->setGeometry(370, 0, cntRow->width(), cntRow->height());
    cntRow->setFont(QFont(QStringLiteral("Microsoft YaHei UI Light")));
    cntRow->setText(QStringLiteral("Row: 0"));

    cntChar->setGeometry(450, 0, cntChar->width(), cntChar->height());
    cntChar->setFont(QFont(QStringLiteral("Microsoft YaHei UI Light")));
    cntChar->setText(QStringLiteral("Char: 0"));

    labelFormat->setGeometry(1030 - labelFormat->width(), 0, labelFormat->width(), labelFormat->height());
    labelFormat->setFont(QFont(QStringLiteral("Microsoft YaHei UI Light")));
    labelFormat->setText(QStringLiteral("Format: UTF-8"));

    // Functional.
    loadingDialog->show();
    loadingDialog->progress();

    code_prev = "#!/usr/bin/python\n"
           "#conding=utf-8\n"
           "import sys\n";
    mainEditor->setText(code_prev);

    ctrlS->setKey(tr("ctrl+s"));
    ctrlS->setAutoRepeat(false);
}

void Workshop::setEventConnections()
{
    connect(mainEditor, SIGNAL(textChanged()), this, SLOT(updateStatusBar()));
    connect(ctrlS, SIGNAL(activated()), this, SLOT(saveFile()));
    connect(mainEditor, SIGNAL(textChanged()), this, SLOT(checkCodeModifiedState()));
}

void Workshop::_constructed()
{
    emit constructed();
    PJEntity = new CellProjectEntity("newpj",CellProjectEntity::CellProjectEntityType::_WORKSHOP);
}

void Workshop::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    statusBar->setColorScheme(mode);
    const QColor blockTargetPos = (m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ?
                              QColor(235,235,235) : CellUiConst::GRAYLEVEL70);

    CellUiGlobal::setPropertyAnimation({animi_LeftBlock,animi_RightBlock},
                                 "color",
                                 leftBlock->color(),
                                 blockTargetPos,
                                 CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                 QEasingCurve::InOutCubic,
                                 {leftBlock,rightBlock}, nullptr);
    if(mode == CellUiGlobal::COLOR_SCHEME::_DARK){
        CellUiGlobal::multiModulesOneStyleSheet({cntRow,cntChar,labelFormat},
                                               QStringLiteral("QLabel{color:rgb(255,255,255);}"));      
    }
    else{
        m_mode = CellUiGlobal::COLOR_SCHEME::_BRIGHT;
        CellUiGlobal::multiModulesOneStyleSheet({cntRow,cntChar,labelFormat},
                                          QStringLiteral("QLabel{color:rgb(0, 0, 0);}"));
    }
}

void Workshop::updateStatusBar()
{
    cntRow->setText("Row: " + QString::number(mainEditor->lines()));

    QString tmp = mainEditor->text();
    cntChar->setText("Char: " + QString::number(tmp.length()));
}

void Workshop::saveFile()
{
    //if(savePath!=""){
        if(!codeModified) return;
        code_prev = code_curr;
        statusBar->transCurrState(customGradientChangeFrame::_NORMAL);
    //}
}

void Workshop::checkCodeModifiedState()
{
    code_prev == (code_curr = mainEditor->text()) ?
    codeModified = false : codeModified = true;
    codeModified ?
        statusBar->transCurrState(customGradientChangeFrame::_SPECIAL):
        statusBar->transCurrState(customGradientChangeFrame::_NORMAL);
#ifdef CELL_DEBUG
    qDebug() << "--------------------------";
    qDebug() << "CODE EDITOR";
    qDebug() << "CodeModified: " << codeModified;
    qDebug() << "--------------------------\n";
#endif
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
    loadingDialog->close();
}
