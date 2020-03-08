#ifndef NEWPJPREDICTEARPAGE_H
#define NEWPJPREDICTEARPAGE_H

#include "../CustomBaseWidgets/newPJPageBase.h"

class NewPJPredictEarPage : public newPJPageBase{
    Q_OBJECT
public:
    explicit NewPJPredictEarPage(QWidget *parent = nullptr);
    ~NewPJPredictEarPage() = default;

private:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;
};

#endif // NEWPJPREDICTEARPAGE_H
