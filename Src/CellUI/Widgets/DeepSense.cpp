#include "DeepSense.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

DeepSense::DeepSense(QWidget *parent):
    QWidget(parent)
{
    resize(1400, 800);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(CHAR2STR("DeepSense"));
}
