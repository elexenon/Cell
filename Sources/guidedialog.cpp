#include "Headers/guidedialog.h"
#include "ui_guidedialog.h"

GuideDialog::GuideDialog(QWidget *parent) :
    DropShadowDialog(parent),
    ui(new Ui::GuideDialog)
{
    ui->setupUi(this);
    Init();
}

GuideDialog::~GuideDialog()
{
    delete ui;
}

void GuideDialog::Init()
{
    // Functional.
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
#ifdef Q_OS_WIN32
    DropShadowDialog::LoadWinStyle(this);
#endif
    // Load styles
    ui->frame->setStyleSheet(QStringLiteral("#frame{border:1.4px solid #DCDCDC}"));

    ui->label_getStart->setFont(QFont(QStringLiteral("微软雅黑"), 18));
    ui->label_getStart->setStyleSheet(QStringLiteral("QLabel{color:#DCDCDC;background-color: transparent;}"));

    ui->label_learn->setFont(QFont(QStringLiteral("微软雅黑"), 9));
    ui->label_learn->setStyleSheet(QStringLiteral("QLabel{color:#DCDCDC;background-color: transparent;}"));

    ui->checkBox_showUp->setFont(QFont(QStringLiteral("微软雅黑 Light")));
    ui->checkBox_showUp->setStyleSheet(QStringLiteral("QCheckBox{color:#798186;background-color: transparent;}"));

    styleSheetLoader->setStyleSheetName(QStringLiteral("GuideDialogCloseBtn.qss"));
    ui->Btn_close->setStyleSheet(styleSheetLoader->styleSheet());
    ui->Btn_close->setFont(QFont(QStringLiteral("微软雅黑")));
}

#ifdef Q_OS_WIN32
// Achieve the window drop shadow effect( Windows ).
bool GuideDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return DropShadowDialog::nativeEvent(eventType, message, result);
}
#endif

// Mouse drag process.
void GuideDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= 40){
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void GuideDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move && event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos );
    }
}

void GuideDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_move = false;
    }
}

void GuideDialog::on_Btn_close_clicked()
{
    close();
}
