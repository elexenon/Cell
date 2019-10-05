#include "Headers/mainwindow.h"

#ifdef Q_OS_WIN32
#include "Headers/WindWMAPI.h"
#endif

#include "ui_mainwindow.h"
#define DEBUG

mainWindow::mainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWindow)
    , mainWindowTabBtns(new QList<QPushButton*>)
    , styleSheetLoader(new QStyleSheetLoader(STYLESHEET_DIR))
{
    ui->setupUi(this);
    InitMainWindow();
}
mainWindow::~mainWindow()
{
    delete ui;
}

#ifdef Q_OS_WIN32
// Achieve the window drop shadow effect( Windows ).
bool mainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
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
void mainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= 60){
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void mainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move && event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos );
    }
}

void mainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_move = false;
    }
}
#ifdef ROUNDED_WINDOW
void mainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor::fromRgb(247, 247, 247)));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 5, 5);
    QWidget::paintEvent(e);
}
//
#endif

void mainWindow::InitMainWindow()
{
    // Functional.
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);  // Remove Windows' Default Window Frame.
#ifdef ROUNDED_WINDOW
    this->setAttribute(Qt::WA_TranslucentBackground);
#endif

#ifdef Q_OS_WIN32
    // Achieve the window drop shadow effect.
    HWND hwnd =  (HWND)this->winId();
    DWORD style = static_cast<DWORD>(::GetWindowLong(hwnd, GWL_STYLE));
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    const MARGINS shadow = { 1, 1, 1, 1 };
    WinDwmapi::instance()->DwmExtendFrameIntoClientArea(HWND(winId()), &shadow);
#endif



    mainWindowTabBtns->append(ui->Btn_HomePage);
    mainWindowTabBtns->append(ui->Btn_Settings);

    // Load Custom Fonts.
    int fontID_Info = QFontDatabase::addApplicationFont(FONT_DIR + QStringLiteral("InfoDisplayWeb W01 Medium.ttf"));
    QString Info = QFontDatabase::applicationFontFamilies(fontID_Info).at(0);
#ifdef DEBUG
    qDebug() << QStringLiteral("Main Window Title Font: ") << Info;
#endif

    // Load Styles.
    QFont font_Info(Info, 14);
    font_Info.setLetterSpacing(QFont::PercentageSpacing, 100);
    ui->label_mainWindowTitle->setFont(font_Info);
    ui->label_mainWindowTitle->setStyleSheet("color:"+COLOR_SPACE_GRAY+";");

    ui->label_welcome->setFont(QFont("微软雅黑 Light", 18));

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowLeftTab_HomePage.qss"));
    ui->Btn_HomePage->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowLeftTab_Settings.qss"));
    ui->Btn_Settings->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowLeftTab_Guide.qss"));
    ui->Btn_Guide->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowLeftTab_NewPJ.qss"));
    ui->Btn_NewProject->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowLeftTab_OpenPJ.qss"));
    ui->Btn_OpenProject->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowCloseBtn.qss"));
    ui->Btn_close->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowMinimizeBtn.qss"));
    ui->Btn_mini->setStyleSheet(styleSheetLoader->styleSheet());

    // Functiona;
    guideDialog = new GuideDialog(this);
    guideDialog->show();
}

void mainWindow::setAllTabsUnchecked()
{
    for(auto & e : *mainWindowTabBtns)
        e->setChecked(false);
}

void mainWindow::on_Btn_mini_clicked()
{
    if(this->windowState() != Qt::WindowMinimized)
            this->setWindowState(Qt::WindowMinimized);    // 在macOS下有bug
}

void mainWindow::on_Btn_close_clicked()
{
    close();
}

void mainWindow::on_Btn_HomePage_clicked()
{
    setAllTabsUnchecked();
    ui->Btn_HomePage->setChecked(true);
}

void mainWindow::on_Btn_Settings_clicked()
{
    setAllTabsUnchecked();
    ui->Btn_Settings->setChecked(true);
}

void mainWindow::on_Btn_Guide_clicked()
{
    guideDialog->show();
}
