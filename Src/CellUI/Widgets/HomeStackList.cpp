#include "HomeStackList.h"

#include "../../CellCore/Kits/CellUtility.h"

#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>

HomeStackList::HomeStackList(QWidget *parent) noexcept:
    customFrame(customFrame::Type::Radius, parent),
    mainLayout(new QVBoxLayout(this)),
    tableView(new QTableView(this)),
    itemModel(new QStandardItemModel)
{
    init();
    setEventConnections();
}

void HomeStackList::init()
{
    mainLayout->setMargin(0);
    mainLayout->addWidget(tableView);

    initTableView();
}

void HomeStackList::setEventConnections()
{
    using namespace CellUiGlobal;
    connect(tableView, &QTableView::doubleClicked, [=](const QModelIndex &index){
        bool isDSPJ = true;
        auto type = CellProjectEntity::getType(index.siblingAtColumn(2).data().toString());
        if(hasAttribute(CellProjectEntity::WSProject, type))
            isDSPJ = false;
        emit openFileByPath(isDSPJ, index.siblingAtColumn(3).data().toString() + "//" +
                                    index.siblingAtColumn(0).data().toString() + ".workshop");
    });
}

void HomeStackList::initTableView()
{
    QStringList headersList;
    headersList << CHAR2STR("名称") << CHAR2STR("修改时间") << CHAR2STR("类型") << CHAR2STR("路径");
    itemModel->setHorizontalHeaderLabels(headersList);

    CellUiGlobal::loader.setFileName(CHAR2STR("TableViewBrightMode.css"));
    tableView->setStyleSheet(CellUiGlobal::loader.content());
    tableView->setFrameShape(QFrame::NoFrame);
    tableView->setFont(QFont(CHAR2STR("Microsoft YaHei UI Light")));
    tableView->setAlternatingRowColors(true);
    tableView->setShowGrid(false);
    tableView->setSortingEnabled(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setModel(itemModel);
    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->horizontalHeader()->setFont(QFont(CHAR2STR("Microsoft YaHei UI Light")));
    tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}
