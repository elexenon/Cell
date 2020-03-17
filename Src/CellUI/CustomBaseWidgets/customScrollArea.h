#ifndef CUSTOMSMOOTHSCROLLAREA_H
#define CUSTOMSMOOTHSCROLLAREA_H

#include <QScrollArea>

class customScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit customScrollArea(QWidget *parent = nullptr);
    ~customScrollArea() = default;
};

#endif // CUSTOMSMOOTHSCROLLAREA_H
