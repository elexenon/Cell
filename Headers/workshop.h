#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <QWidget>
#include "Kits/_utility.h"

namespace Ui {
class Workshop;
}

class WSWelcomeDialog;
class QsciScintilla;
class customFrame;
class QLabel;
class QPushButton;

class Workshop : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit Workshop(COLOR_SCHEME mainWindow_mode, QWidget *parent = nullptr);
    ~Workshop();

public:
    const QColor color() const;
    void  setColor(const QColor color);

private:
    Ui::Workshop *ui;
    QPropertyAnimation *animi_MenuBar;
    QPropertyAnimation *animi_StatusBar;
    QPropertyAnimation *animi_LeftBlock;
    QPropertyAnimation *animi_RightBlock;

    QGraphicsDropShadowEffect *eff1;
    QGraphicsDropShadowEffect *eff2;
    QGraphicsDropShadowEffect *eff3;

    QFrame *dropShadowLine1;
    QFrame *dropShadowLine2;
    QFrame *dropShadowLine3;

    WSWelcomeDialog  *welcomeDialog;
    customFrame      *menuBar;
    customFrame      *leftBlock;
    customFrame      *rightBlock;
    customFrame      *statusBar;
    QLabel           *cntRow;
    QLabel           *cntChar;
    QLabel           *labelFormat;
    QsciScintilla    *mainEditor;

    QColor m_color;
    COLOR_SCHEME m_mode;

private:
    void InitWorkshop();
    void setConnections();

private slots:
    void setColorScheme(COLOR_SCHEME mode);
    void updateStatusBar();

protected:
    virtual void closeEvent(QCloseEvent *event) override;
};

#endif // WORKSHOP_H
