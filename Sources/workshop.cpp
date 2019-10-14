#include <QPropertyAnimation>
#include <QLabel>
#include <QDebug>
#include <QCursor>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSplitter>
#include <QGraphicsDropShadowEffect>
#include <QSci/qsciscintilla.h>
#include "../Headers/Kits/_utility.h"
#include "../Headers/wswelcomedialog.h"
#include "../Headers/Kits/customFrame.h"
#include "Headers/workshop.h"
#include "ui_workshop.h"

Workshop::Workshop(COLOR_SCHEME mainWindow_mode, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Workshop),
    dropShadowLine1(new QFrame),
    dropShadowLine2(new QFrame),
    dropShadowLine3(new QFrame),
    welcomeDialog(new WSWelcomeDialog),
    menuBar(new customFrame(WINDOW_TYPE::_MAIN, this)),
    leftBlock(new customFrame(WINDOW_TYPE::_MAIN, this)),
    rightBlock(new customFrame(WINDOW_TYPE::_MAIN, this)),
    statusBar(new customFrame(WINDOW_TYPE::_MAIN, this)),
    mainEditor(new QsciScintilla(this)),
    m_color(COLOR_SCHEME::_BRIGHT)
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
    setFixedSize(this->size());

    menuBar->setParent(this);
    menuBar->setGeometry(0, 0, 1400, 39);

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

    setConnections();

    leftBlock->setGeometry(0, 39, 370, 732);
    rightBlock->setGeometry(1030, 39, 370, 732);

    dropShadowLine1->setParent(leftBlock);
    dropShadowLine1->setGeometry(QRect(0, 0, leftBlock->width(), 1));
    dropShadowLine1->setFrameShape(QFrame::HLine);
    dropShadowLine1->setFrameShadow(QFrame::Plain);

    dropShadowLine2->setParent(mainEditor);
    dropShadowLine2->setGeometry(QRect(0, 0, mainEditor->width(), 1));
    dropShadowLine2->setFrameShape(QFrame::HLine);
    dropShadowLine2->setFrameShadow(QFrame::Plain);

    dropShadowLine3->setParent(rightBlock);
    dropShadowLine3->setGeometry(QRect(0, 0, rightBlock->width(), 1));
    dropShadowLine3->setFrameShape(QFrame::HLine);
    dropShadowLine3->setFrameShadow(QFrame::Plain);

    statusBar->setGeometry(0, 771, 1400, 29);

    cntRow = new QLabel(statusBar);
    cntChar = new QLabel(statusBar);
    labelFormat = new QLabel(statusBar);

    // Load Style.
    // Menu Bar.
    statusBar->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(210,210,210);}"));

    menuBar->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(65,152,197);}"));

    ui->BtnFile->setFont(QFont("微软雅黑", 10));
    ui->BtnEdit->setFont(QFont("微软雅黑", 10));
    ui->BtnBuild->setFont(QFont("微软雅黑", 10));
    ui->BtnDebug->setFont(QFont("微软雅黑", 10));
    ui->BtnKits->setFont(QFont("微软雅黑", 10));
    ui->BtnView->setFont(QFont("微软雅黑", 10));
    ui->BtnHelp->setFont(QFont("微软雅黑", 10));

    ui->BtnFile->setStyleSheet(QStringLiteral("QPushButton{color:rgb(255,255,255);background-color:rgb(65,152,197);}"));
    ui->BtnEdit->setStyleSheet(QStringLiteral("QPushButton{color:rgb(255,255,255);background-color:rgb(65,152,197);}"));
    ui->BtnBuild->setStyleSheet(QStringLiteral("QPushButton{color:rgb(255,255,255);background-color:rgb(65,152,197);}"));
    ui->BtnDebug->setStyleSheet(QStringLiteral("QPushButton{color:rgb(255,255,255);background-color:rgb(65,152,197);}"));
    ui->BtnKits->setStyleSheet(QStringLiteral("QPushButton{color:rgb(255,255,255);background-color:rgb(65,152,197);}"));
    ui->BtnView->setStyleSheet(QStringLiteral("QPushButton{color:rgb(255,255,255);background-color:rgb(65,152,197);}"));
    ui->BtnHelp->setStyleSheet(QStringLiteral("QPushButton{color:rgb(255,255,255);background-color:rgb(65,152,197);}"));

    // DropShadow Lines.
    dropShadowLine1->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:rgb(65,152,197);max-height:1px;}"));
    dropShadowLine2->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:rgb(65,152,197);max-height:1px;}"));
    dropShadowLine3->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:rgb(65,152,197);max-height:1px;}"));

    // DropShadowEffects.
    eff1 = new QGraphicsDropShadowEffect(dropShadowLine1);
    eff1->setOffset(QPoint(0, 1));
    eff1->setColor(Qt::black);
    eff1->setBlurRadius(10);

    eff2 = new QGraphicsDropShadowEffect(dropShadowLine2);
    eff2->setOffset(QPoint(0, 1));
    eff2->setColor(Qt::black);
    eff2->setBlurRadius(10);

    eff3 = new QGraphicsDropShadowEffect(dropShadowLine3);
    eff3->setOffset(QPoint(0, 1));
    eff3->setColor(Qt::black);
    eff3->setBlurRadius(10);

    dropShadowLine1->setGraphicsEffect(eff1);
    dropShadowLine2->setGraphicsEffect(eff2);
    dropShadowLine3->setGraphicsEffect(eff3);

    // Main Editor.
    mainEditor->setFrameShape(QFrame::NoFrame);
    styleSheetLoader->setStyleSheetName(QStringLiteral("WorkshopEditor.css"));
    mainEditor->setStyleSheet(styleSheetLoader->styleSheet());
    mainEditor->setFont(QFont("Courier New", 11));
    mainEditor->setPaper(QColor(249,250,250));

    mainEditor->setMarginsBackgroundColor(QColor(240,240,240));
    mainEditor->setCaretLineBackgroundColor(QColor(240,240,240));

    // Two Blocks.
    leftBlock->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(235,235,235);}"));
    rightBlock->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(235,235,235);}"));

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

void Workshop::setConnections()
{
    connect(mainEditor, SIGNAL(textChanged()), this, SLOT(updateStatusBar()));
}

void Workshop::setColorScheme(COLOR_SCHEME mode)
{
    if(mode == COLOR_SCHEME::_DARK){
        if(mode == m_mode) return;
        m_mode = COLOR_SCHEME::_DARK;

        dropShadowLine1->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:rgb(44,44,45);max-height:1px;}"));

        dropShadowLine2->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:rgb(44,44,45);max-height:1px;}"));

        dropShadowLine3->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:rgb(44,44,45);max-height:1px;}"));

        cntRow->setStyleSheet(QStringLiteral("QLabel{color:rgb(255,255,255);}"));
        cntChar->setStyleSheet(QStringLiteral("QLabel{color:rgb(255,255,255);}"));

        UTILITY::setPropertyAnimation(animi_MenuBar, "color", QColor(65,152,197), COLOR_OPTION_BLOCK_DARK, 500,
                             QEasingCurve::InOutCubic, menuBar, true, nullptr);
        UTILITY::setPropertyAnimation(animi_StatusBar, "color", QColor(210,210,210), COLOR_OPTION_BLOCK_DARK, 500,
                             QEasingCurve::InOutCubic, statusBar, true, nullptr);
        UTILITY::setPropertyAnimation(animi_LeftBlock, "color", QColor(235,235,235), QColor(70, 70, 70), 500,
                             QEasingCurve::InOutCubic, leftBlock, true, nullptr);
        UTILITY::setPropertyAnimation(animi_RightBlock, "color", QColor(235,235,235), QColor(70, 70, 70), 500,
                             QEasingCurve::InOutCubic, rightBlock, true, nullptr);
    }
    else{
        if(mode == m_mode) return;
        m_mode = COLOR_SCHEME::_BRIGHT;

        dropShadowLine1->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:rgb(65,152,197);max-height:1px;}"));

        dropShadowLine2->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:rgb(65,152,197);max-height:1px;}"));

        dropShadowLine3->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:rgb(65,152,197);max-height:1px;}"));

        cntRow->setStyleSheet(QStringLiteral("QLabel{color:rgb(0, 0, 0);}"));
        cntChar->setStyleSheet(QStringLiteral("QLabel{color:rgb(0, 0, 0);}"));

        UTILITY::setPropertyAnimation(animi_MenuBar, "color", COLOR_OPTION_BLOCK_DARK, QColor(65,152,197), 500,
                             QEasingCurve::InOutCubic, menuBar, true, nullptr);
        UTILITY::setPropertyAnimation(animi_StatusBar, "color", COLOR_OPTION_BLOCK_DARK, QColor(210,210,210), 500,
                             QEasingCurve::InOutCubic, statusBar, true, nullptr);
        UTILITY::setPropertyAnimation(animi_LeftBlock, "color", QColor(70, 70, 70), QColor(235,235,235), 500,
                             QEasingCurve::InOutCubic, leftBlock, true, nullptr);
        UTILITY::setPropertyAnimation(animi_RightBlock, "color", QColor(70, 70, 70), QColor(235,235,235), 500,
                             QEasingCurve::InOutCubic, rightBlock, true, nullptr);
    }
}

void Workshop::updateStatusBar()
{
    QCursor cursor = mainEditor->cursor();
    qDebug() << cursor.pos();

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
    QString qss=QString("background-color:rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue());
    setStyleSheet(qss);
}

void Workshop::closeEvent(QCloseEvent *event)
{
    welcomeDialog->close();
}
