#include "Headers/guidedialog.h"
#include "ui_guidedialog.h"

#ifdef Q_OS_WIN32
#include "Headers/WindWMAPI.h"
#pragma comment(lib, "user32.lib")
#endif

GuideDialog::GuideDialog(QWidget *parent) :
    QDialog(parent),
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
    styleSheetLoader = new QFile;

#ifdef Q_OS_WIN32
    // Achieve the window drop shadow effect.
    HWND hwnd =  (HWND)this->winId();
    DWORD style = static_cast<DWORD>(::GetWindowLong(hwnd, GWL_STYLE));
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    const MARGINS shadow = { 1, 1, 1, 1 };
    WinDwmapi::instance()->DwmExtendFrameIntoClientArea(HWND(winId()), &shadow);
#endif

    // Load styles
    ui->frame->setStyleSheet(QStringLiteral("#frame{border:1.4px solid #DCDCDC}"));

    ui->label_getStart->setFont(QFont(QStringLiteral("微软雅黑"), 18));
    ui->label_getStart->setStyleSheet(QStringLiteral("QLabel{color:#DCDCDC;background-color: transparent;}"));

    ui->label_learn->setFont(QFont(QStringLiteral("微软雅黑"), 9));
    ui->label_learn->setStyleSheet(QStringLiteral("QLabel{color:#DCDCDC;background-color: transparent;}"));

    ui->checkBox_showUp->setFont(QFont(QStringLiteral("微软雅黑 Light")));
    ui->checkBox_showUp->setStyleSheet(QStringLiteral("QCheckBox{color:#798186;background-color: transparent;}"));

    setMyStyleSheet("GuideDialogCloseBtn.qss");
    ui->Btn_close->setStyleSheet(myStyleSheet);
    ui->Btn_close->setFont(QFont(QStringLiteral("微软雅黑")));
}

void GuideDialog::setMyStyleSheet(QString name)
{
    styleSheetLoader->setFileName(STYLESHEET_DIR + name);
    styleSheetLoader->open(QFile::ReadOnly);
    myStyleSheet = tr(styleSheetLoader->readAll());
    styleSheetLoader->close();
}

#ifdef Q_OS_WIN32
// Achieve the window drop shadow effect( Windows ).
bool GuideDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    switch (msg->message){
        case WM_NCCALCSIZE:{
            *result = 0;
            return true;
        }
        default:
            return QWidget::nativeEvent(eventType, message, result);
    }
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
