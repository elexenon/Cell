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

    QString path;
    QString name;

private:
    void init();
    virtual void setEventConnections() override;

signals:
    void pathSettled(const QString &path);
    void nameSettled(const QString &name);

private Q_SLOTS:
    void btnPathClicked();
    inline
    void lineEditChanged(const QString &text) { nameSettled(text); }
};

#endif // NEWPJPROJECTPAGE_H
