#include "Headers/guidedialog.h"
#include "ui_guidedialog.h"

GuideDialog::GuideDialog(QWidget *parent) :
    DropShadowDialog(parent),
    ui(new Ui::GuideDialog),
    frame_titleBar(new customFrame(WINDOW_TYPE::_MAIN, this)),
    m_mode(COLOR_SCHEME::_BRIGHT)
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
    frame_titleBar->setGeometry(0, 0, 781, 51);
    frame_titleBar->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(164, 163, 164);}"));

    ui->label_getStart->setFont(QFont(QStringLiteral("微软雅黑"), 18));
    ui->label_getStart->setStyleSheet(QStringLiteral("QLabel{color:#DCDCDC;background-color: transparent;}"));

    ui->label_learn->setFont(QFont(QStringLiteral("微软雅黑"), 9));
    ui->label_learn->setStyleSheet(QStringLiteral("QLabel{color:#DCDCDC;background-color: transparent;}"));

    ui->checkBox_showUp->setFont(QFont(QStringLiteral("微软雅黑 Light")));
    ui->checkBox_showUp->setStyleSheet(QStringLiteral("QCheckBox{color:#798186;background-color: transparent;}"));

    styleSheetLoader->setStyleSheetName(QStringLiteral("GuideDialogCloseBtn_Bright.qss"));
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

void GuideDialog::setColorScheme(COLOR_SCHEME mode)
{
    if(mode == COLOR_SCHEME::_DARK){
        if(mode == m_mode) return;
        m_mode = COLOR_SCHEME::_DARK;

        styleSheetLoader->setStyleSheetName(QStringLiteral("GuideDialogCloseBtn_Dark.qss"));
        ui->Btn_close->setStyleSheet(styleSheetLoader->styleSheet());

        UTILITY::setPropertyAnimation(animi_main, "color", color(), MAINWINDOW_DARK, 500,
                             QEasingCurve::Linear, this, true, nullptr);
        UTILITY::setPropertyAnimation(animi_title, "color", frame_titleBar->color(), QColor(44, 44, 45), 500,
                             QEasingCurve::Linear, frame_titleBar, true, nullptr);
    }
    else{
        if(mode == m_mode) return;
        m_mode = COLOR_SCHEME::_BRIGHT;

        styleSheetLoader->setStyleSheetName(QStringLiteral("GuideDialogCloseBtn_Bright.qss"));
        ui->Btn_close->setStyleSheet(styleSheetLoader->styleSheet());

        UTILITY::setPropertyAnimation(animi_main, "color", color(), MAINWINDOW_BRIGHT, 500,
                             QEasingCurve::Linear, this, true, nullptr);
        UTILITY::setPropertyAnimation(animi_title, "color", frame_titleBar->color(), QColor(164, 163, 164), 500,
                             QEasingCurve::Linear, frame_titleBar, true, nullptr);
    }
}

void GuideDialog::on_Btn_close_clicked()
{
    close();
}
