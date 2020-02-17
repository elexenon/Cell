#ifndef CUSTOMMASKDIALOG_H
#define CUSTOMMASKDIALOG_H

#include <QWidget>

class QVBoxLayout;
class QLabel;
class QPropertyAnimation;

class customMaskDialog: public QWidget{
    Q_OBJECT
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity)
public:
    explicit customMaskDialog(QWidget *parent = nullptr);

    void setOptionText(const QString &text);
    void setHintText(const QString &text);
    void setOptionWidget(QWidget *widget);
    inline
    void setTargetWidget(QWidget *widget) { targetWidget = widget; }
    inline
    int  opacity() { return mOpacity; }
    void setOpacity(int value);

protected:
    virtual void showEvent(QShowEvent *e) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    void init();
    void switchOpacity(int sValue, int eValue);
    void fade();

    QPropertyAnimation *animi;
    QWidget            *targetWidget;
    QVBoxLayout        *mainLayout;
    QFrame             *dialog;
    QLabel             *labelOption;
    QLabel             *labelHint;

    int mOpacity;
};

#endif // CUSTOMMASKDIALOG_H
