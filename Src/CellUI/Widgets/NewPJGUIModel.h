#ifndef NEWPJGUIMODEL_H
#define NEWPJGUIMODEL_H

#include "../CustomBaseWidgets/customFrame.h"

class QHBoxLayout;
class customFrame;
class customNavigator;
class customSmoothScrollArea;

class NewPJGUIModel : public customFrame
{
public:
    explicit NewPJGUIModel(QWidget *parent = nullptr);
    ~NewPJGUIModel() = default;

private:
    virtual void
    init() override;

    QHBoxLayout            *mainLayout;
    customNavigator        *navigator;
    customSmoothScrollArea *scrollArea;
    customFrame            *scrollWidget;
};

#endif // NEWPJGUIMODEL_H
