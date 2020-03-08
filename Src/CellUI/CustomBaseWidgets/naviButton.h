#ifndef NAVIBUTTON_H
#define NAVIBUTTON_H

#include <QPushButton>

class customLabel;
class QVBoxLayout;
class CellVariant;

class naviButton : public QPushButton{
    Q_OBJECT
public:
    explicit naviButton(QWidget *parent = nullptr) noexcept;

    void init(const QString& text = "naviButton", int fontSize = 18);
    void setTextColor(const CellVariant &b, const CellVariant &d);

protected:
    virtual void paintEvent(QPaintEvent*) override;

    QVBoxLayout *mainLayout;
    customLabel *tag;
};

#endif // NAVIBUTTON_H
