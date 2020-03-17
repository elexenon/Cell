#ifndef HOMESTACKLIST_H
#define HOMESTACKLIST_H

#include "../CustomBaseWidgets/customFrame.h"
#include "../../CellCore/CellProjectEntity.h"

class QVBoxLayout;
class QTableView;
class CellProjectEntity;

class HomeStackList : public customFrame
{
    Q_OBJECT
public:
    explicit HomeStackList(QWidget *parent = nullptr) noexcept;
    ~HomeStackList() = default;

    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    void
    initTableView();

    inline void
    tableAppendRow(const QList<QStandardItem*> &items) { tableInsertRow(-1, items); }

    inline void
    tableInsertRow(int index, const QList<QStandardItem*> &items) {
        if(index < 0) itemModel->appendRow(items);
        else itemModel->insertRow(index, items);
    }

private Q_SLOTS:

private:
    QVBoxLayout        *mainLayout;
    QTableView         *tableView;
    QStandardItemModel *itemModel;

Q_SIGNALS:
    void openFileByPath(bool isDS, const QString &path);
};

#endif // HOMESTACKLIST_H
