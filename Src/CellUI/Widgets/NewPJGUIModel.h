#ifndef NEWPJGUIMODEL_H
#define NEWPJGUIMODEL_H

#include "../CustomBaseWidgets/customFrame.h"
#include "../../CellCore/CellProjectEntity.h"

class QHBoxLayout;
class customFrame;
class customNavigator;
class customScrollArea;
class customScrollBlock;

class NewPJGUIModel : public customFrame
{
    Q_OBJECT
public:
    explicit NewPJGUIModel(QWidget *parent = nullptr);
    ~NewPJGUIModel() = default;

private:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    QHBoxLayout       *mainLayout;
    customNavigator   *navigator;
    customScrollArea  *scrollArea;
    customFrame       *scrollWidget;
    customScrollBlock *blockPic;
    customScrollBlock *blockBinary;

Q_SIGNALS:
    void typeSeleted(CellProjectEntity::ProjectType type);
};

#endif // NEWPJGUIMODEL_H
