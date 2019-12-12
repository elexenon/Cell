#include "launcherNewPJDialog.h"
#include "ui_launchernewpjdialog.h"

#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/customStaticButton.h"

LauncherNewPJDialog::LauncherNewPJDialog(QWidget *parent) :
    customDialog(parent),
    ui(new Ui::LauncherNewPJDialog),
    frame_titleBar(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    label_choose(new customLabel(Cell_Const::QSS_CUSTOMLABEL, this)),
    label_project(new customLabel(Cell_Const::QSS_CUSTOMLABEL, this)),
    label_file(new customLabel(Cell_Const::QSS_CUSTOMLABEL, this)),
    frame_project(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    frame_file(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    Tab_WorkShop(new customStaticButton(this)),
    Tab_Others(new customStaticButton(this))
{
    ui->setupUi(this);
    Init();
}

LauncherNewPJDialog::~LauncherNewPJDialog()
{
    delete ui;
}

void LauncherNewPJDialog::Init()
{
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    customDialog::LoadWinStyle(this);
    setAttribute(Qt::WA_DeleteOnClose);

    frame_titleBar->setObjectName(QStringLiteral("frame_titleBar"));
    frame_titleBar->setGeometry(0, 0, 600, 45);
    frame_titleBar->setColor(QColor(164,164,164));

    frame_project->setObjectName(QStringLiteral("frame_project"));
    frame_project->setGeometry(20, 120, 150, 31);
    frame_project->setColor(QColor(50,200,230));

    label_project->setObjectName(QStringLiteral("label_project"));
    label_project->setGeometry(10, 0, 70, 31);
    label_project->setText(QStringLiteral("PROJECT"));
    label_project->setFont(QFont("Microsoft YaHei UI",9,QFont::Bold));
    label_project->setColor(Cell_Const::GRAYLEVEL255);
    label_project->setParent(frame_project);

    label_choose->setObjectName(QStringLiteral("label_choose"));
    label_choose->setGeometry(20, 50, 150, 50);
    label_choose->setText(tr("选择一个模板"));
    label_choose->setFont(QFont("微软雅黑 Light",15));
    label_choose->setColor(Cell_Const::GRAYLEVEL70);

    Tab_WorkShop->setObjectName(QStringLiteral("Tab_WorkShop"));
    Tab_WorkShop->setBrightModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL218,Cell_Const::GRAYLEVEL247);
    Tab_WorkShop->setDarkModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL70,Cell_Const::GRAYLEVEL30);
    Tab_WorkShop->Init();
    Tab_WorkShop->setGeometry(20, 160, 150, 30);
    Tab_WorkShop->setCheckable(true);
    Tab_WorkShop->setChecked(true);

    Tab_Others->setObjectName(QStringLiteral("Tab_Others"));
    Tab_Others->setBrightModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL218,Cell_Const::GRAYLEVEL247);
    Tab_Others->setDarkModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL70,Cell_Const::GRAYLEVEL30);
    Tab_Others->Init();
    Tab_Others->setGeometry(20, 193, 150, 30);
    Tab_Others->setCheckable(true);

    frame_file->setObjectName(QStringLiteral("frame_file"));
    frame_file->setGeometry(20, 233, 150, 31);
    frame_file->setColor(QColor(50,200,230));

    label_file->setObjectName(QStringLiteral("label_file"));
    label_file->setGeometry(10, 0, 70, 31);
    label_file->setText(QStringLiteral("FILE"));
    label_file->setFont(QFont("Microsoft YaHei UI",9,QFont::Bold));
    label_file->setColor(Cell_Const::GRAYLEVEL255);
    label_file->setParent(frame_file);

    CellGlobal::setDropShadowEffect({eff_dse},
                               {frame_project},
                                QPoint(0,0),QColor(50,200,230),12);

    CellGlobal::setDropShadowEffect({eff_dse},
                               {frame_file},
                                QPoint(0,0),QColor(50,200,230),12);
}

void LauncherNewPJDialog::setColorScheme(CellGlobal::COLOR_SCHEME mode){
    if(mode == m_mode) return;
    m_mode = mode;
    const QColor labelColor = (mode == CellGlobal::COLOR_SCHEME::_BRIGHT ? Cell_Const::GRAYLEVEL70 : Cell_Const::GRAYLEVEL255);
    const QColor titleColor = (mode == CellGlobal::COLOR_SCHEME::_BRIGHT ? QColor(164,164,164) : Cell_Const::GRAYLEVEL45);
    CellGlobal::setPropertyAnimation({animi},
                                 "color",
                                 frame_titleBar->color(),
                                 titleColor,
                                 CellGlobal::CELL_GLOBALANIMIDURATION,
                                 QEasingCurve::InOutCubic,
                                 {frame_titleBar}, nullptr);
    CellGlobal::setPropertyAnimation({label_animi},
                                     "color",
                                     label_choose->color(),
                                     labelColor,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {label_choose}, nullptr);
}

bool LauncherNewPJDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return customDialog::nativeEvent(eventType, message, result);
}

void LauncherNewPJDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= 40){
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void LauncherNewPJDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move && event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos );
    }
}

void LauncherNewPJDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_move = false;
    }
}
