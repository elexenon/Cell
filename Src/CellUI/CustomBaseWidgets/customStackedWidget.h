#ifndef CUSTOMSTACKEDWIDGET_H
#define CUSTOMSTACKEDWIDGET_H

#include <QStackedWidget>

class QPropertyAnimation;

class customStackedWidget : public QStackedWidget{
    Q_OBJECT
    Q_PROPERTY(double midIndex READ getMidIndex WRITE setMidIndex)
public:
    enum SWITCH_TYPE{
        _LEFT,
        _RIGHT
    };
    explicit customStackedWidget(QWidget *parent = nullptr);

    inline double
    getMidIndex() { return midIndex; }

    inline void
    setMidIndex(const double index) { midIndex = index; update(); }

    inline void
    setAnimiDuration(int value) { animiDuration = value; }

protected:
    virtual void
    paintEvent(QPaintEvent *e);

private:
    void
    paintNext(QPainter &painter, int index);

    void
    paintPrevious(QPainter &painter, int index);

    void
    setEventConnections();

    QPropertyAnimation *animi;
    SWITCH_TYPE         m_type;
    int                 animiDuration;
    int                 switchIndex;
    double              midIndex;
    bool                animiRunning = false;

public Q_SLOTS:
    void
    switchNext();

    void
    switchPrevious();

    void
    animiFinished();
};

#endif // CUSTOMSTACKEDWIDGET_H
