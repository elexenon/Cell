// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include "customFrame.h"

class QHBoxLayout;
class customLabel;
class ButtonWithIcon;

class customDialogButton : public customFrame{
    Q_OBJECT
public:
    explicit customDialogButton(const QString& state, QWidget *parent = nullptr);
    inline
    const ButtonWithIcon* getTrigger() { return trigger;}
    void  setText(const QString &text);

private:
    virtual void setEventConnections() override;

protected:
    customLabel    *currState;
    ButtonWithIcon *trigger;
    QHBoxLayout    *mainLayout;

signals:
    void clicked();

private Q_SLOTS:
    inline
    void triggerClicked() { emit clicked(); }
};

#endif // CUSTOMCOMBOBOX_H
