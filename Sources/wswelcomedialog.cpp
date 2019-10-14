#include "Headers/wswelcomedialog.h"
#include "ui_wswelcomedialog.h"
#include "Headers/Kits/_utility.h"

WSWelcomeDialog::WSWelcomeDialog(QWidget *parent) :
    DropShadowDialog(parent),
    ui(new Ui::WSWelcomeDialog),
    timer(new QTimer)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
#ifdef Q_OS_WIN32
    DropShadowDialog::LoadWinStyle(this);
#endif
    setAutoFillBackground(true);
    setModal(true);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
}

WSWelcomeDialog::~WSWelcomeDialog()
{
    delete ui;
}

void WSWelcomeDialog::progress()
{
    timer->start(10);
}

void WSWelcomeDialog::updateProgressBar()
{
    QProgressBar *bar = ui->progressBar;
    if(bar->value() < 100)
        bar->setValue(bar->value()+1);
    else{
        timer->stop();
        delete timer;
        close();
    }
}

#ifdef Q_OS_WIN32
// Achieve the window drop shadow effect( Windows ).
bool WSWelcomeDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return DropShadowDialog::nativeEvent(eventType, message, result);
}
#endif

// Mouse drag process.
void WSWelcomeDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= 40){
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void WSWelcomeDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move && event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos );
    }
}

void WSWelcomeDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_move = false;
    }
}
