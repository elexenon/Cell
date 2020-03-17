#ifndef HOMESTACKGRID_H
#define HOMESTACKGRID_H

#include "../CustomBaseWidgets/customFrame.h"
#include "../../CellCore/CellProjectEntity.h"

class CellProjectEntity;
class customScrollBlock;
class customScrollArea;
class ButtonWithIcon;
class QVBoxLayout;
class QHBoxLayout;

class HomeStackGrid : public customFrame
{
    Q_OBJECT
public:
    explicit HomeStackGrid(QWidget *parent = nullptr) noexcept;
    ~HomeStackGrid() noexcept = default;

    void
    insertProject(const CellProjectEntity &entity);

private:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    QVBoxLayout       *mainLayout;
    ButtonWithIcon    *btnDone;
    QHBoxLayout       *btnLayout;
    customScrollArea  *scrollArea;
    customFrame       *scrollWidget;
    QVBoxLayout       *widgetLayout;
    customScrollBlock *blockWorkShop;
    customScrollBlock *blockDeepSense;

    QMap<int, CellProjectEntity> WSMap;
    QMap<int, CellProjectEntity> DSMap;

    int     currID = -1;
    QString currBlock;

Q_SIGNALS:
    void openFileByPath(bool isDS, const QString &path);
};

#endif // HOMESTACKGRID_H
