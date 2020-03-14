#ifndef NEWPJGUICONFIG_H
#define NEWPJGUICONFIG_H

#include "../CustomBaseWidgets/customFrame.h"

class QVBoxLayout;

class NewPJGUIConfig : public customFrame
{
public:
    explicit NewPJGUIConfig(QWidget *parent = nullptr);

private:
    QVBoxLayout *mainLayout;
};

#endif // NEWPJGUICONFIG_H
