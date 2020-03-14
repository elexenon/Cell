// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef NEWPJPAGEBASE_H
#define NEWPJPAGEBASE_H

class customLabel;
class customLineEdit;
class customDialogButton;
class customOptionBlock;
class customOptionBlockItem;
class CellProjectEntity;
class QVBoxLayout;
class QComboBox;

#include "../CustomBaseWidgets/customFrame.h"

class newPJPageBase : public customFrame{
    Q_OBJECT
public:
    explicit newPJPageBase(QWidget *parent = nullptr);
    virtual ~newPJPageBase() = default;

    void
    setPageTitle(const QString &text);

    void
    enableToolChainsBlock();

private:
    QVBoxLayout           *mainLayout;
    customLabel           *labelTitle;
    customOptionBlock     *blockConfig;
    customLineEdit        *lineEditName;
    customDialogButton    *dialogButton;

    customOptionBlock     *blockToolChain;
    QComboBox             *cBoxVersions;

    QString path;
    QString name;

protected:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    void
    addOptionBlock(customOptionBlock *block);

Q_SIGNALS:
    void pathSettled(const QString &path);
    void nameSettled(const QString &name);

private Q_SLOTS:
    void btnPathClicked();
};

#endif // NEWPJPAGEBASE_H
