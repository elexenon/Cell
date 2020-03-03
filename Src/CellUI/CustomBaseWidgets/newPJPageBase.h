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

    void setPageTitle(const QString &text);

private:
    QVBoxLayout           *mainLayout;
    customLabel           *labelTitle;
    customOptionBlock     *blockConfig;
    customOptionBlockItem *blockConfigName;
    customLineEdit        *lineEditName;
    customOptionBlockItem *blockConfigLoca;
    customDialogButton    *dialogButton;

    customOptionBlock     *blockToolChain;
    customOptionBlockItem *blockToolChainVersion;
    QComboBox             *cBoxVersions;

    QString path;
    QString name;

protected:
    virtual void init();
    virtual void setEventConnections() override;
    void         addOptionBlock(customOptionBlock *block);
    void         enableToolChainsBlock();

Q_SIGNALS:
    void pathSettled(const QString &path);
    void nameSettled(const QString &name);

private Q_SLOTS:
    void btnPathClicked();
};

#endif // NEWPJPAGEBASE_H
