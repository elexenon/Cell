#include "launcherNewPJDialog.h"
#include "ui_launchernewpjdialog.h"

#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customLabel.h"

LauncherNewPJDialog::LauncherNewPJDialog(QWidget *parent) :
    customDialog(parent),
    ui(new Ui::LauncherNewPJDialog),
    frame_titleBar(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    label_choose(new customLabel(Cell_Const::QSS_CUSTOMLABEL, this))
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
    customDialog::LoadWinStyle(this);
    setAttribute(Qt::WA_DeleteOnClose);

    frame_titleBar->setObjectName(QStringLiteral("frame_titleBar"));
    frame_titleBar->setGeometry(0, 0, this->width(), 45);
    frame_titleBar->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(164, 163, 164);}"));

    label_choose->setObjectName(QStringLiteral("label_choose"));
    label_choose->setGeometry(10, 50, 100, 50);
    label_choose->setText(tr("选择一个模板"));
    label_choose->setFont(QFont("微软雅黑 Light",15));
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
