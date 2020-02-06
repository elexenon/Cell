// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef NEWPJPROJECTPAGE_H
#define NEWPJPROJECTPAGE_H

#include "../CustomBaseWidgets/customFrame.h"

class customLabel;
class QComboBox;
class customOptionBlock;
class customOptionBlockItem;
class customDialogButton;
class QVBoxLayout;
class customLineEdit;
class ButtonWithIcon;
class CellProjectEntity;

class NewPJProjectCellPage : public customFrame{
    Q_OBJECT
public:
    explicit NewPJProjectCellPage(QWidget *parent = nullptr);
    ~NewPJProjectCellPage() override = default;

private:
    QVBoxLayout           *mainLayout;
    customLabel           *label_title;
    customOptionBlock     *blockConfig;
    customOptionBlockItem *blockConfig_Name;
    customLineEdit        *lineEditName;
    customOptionBlockItem *blockConfig_Loca;
    customDialogButton    *dialogButton;
    ButtonWithIcon        *buttonForward;

    QString path;
    QString name;

private:
    void Init();
    void setEventConnections();

signals:
    void setProjectDone(const QString &name, const QString &path);

private slots:
    void BtnNameClicked();
    void BtnForwardClicked();
};

#endif // NEWPJPROJECTPAGE_H
