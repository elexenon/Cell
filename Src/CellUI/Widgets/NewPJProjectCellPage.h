#ifndef NEWPJPROJECTPAGE_H
#define NEWPJPROJECTPAGE_H

#include "../CustomBaseWidgets/newPJPageBase.h"

class QComboBox;


class NewPJProjectCellPage : public newPJPageBase{
    Q_OBJECT
public:
    explicit NewPJProjectCellPage(QWidget *parent = nullptr);
    ~NewPJProjectCellPage() = default;

private:
    virtual void init() override;
    virtual void setEventConnections() override;

};

#endif // NEWPJPROJECTPAGE_H
