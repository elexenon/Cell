#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>
#include "../../CellCore/Kits/CellUtility.h"

class customLineEdit : public QLineEdit{
    Q_OBJECT
public:
    explicit customLineEdit(QWidget *parent = nullptr);

private:
    void init();

    CellUiGlobal::COLOR_SCHEME m_mode;

public Q_SLOTS:
    void setColorScheme(CellUiGlobal::COLOR_SCHEME mode);
};

#endif // CUSTOMLINEEDIT_H
