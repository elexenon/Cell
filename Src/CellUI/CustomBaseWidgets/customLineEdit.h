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

    Cell::ColorScheme mMode;

public Q_SLOTS:
    void setColorScheme(Cell::ColorScheme mode);
};

#endif // CUSTOMLINEEDIT_H
