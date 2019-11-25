// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CELL_UTIL_H
#define CELL_UTIL_H

#include <QMetaType> // Q_DECLARE_METATYPE()

class QGraphicsDropShadowEffect;
class QPropertyAnimation;
class QStyleSheetLoader;
class QGraphicsEffect;
class QGraphicsOpacityEffect;

class CellGlobal{
public:
    enum FADE_TYPE{
        _IN,
        _OUT
    };
    enum PAGE_TYPE{
        _HOME,
        _SETTINGS
    };
    enum COLOR_SCHEME{
        _BRIGHT,
        _DARK
    };
    enum FRAME_TYPE{
        _REGULAR,
        _OPTIONBLOCK
    };
    enum ANIMIDURATION{
        CELL_GLOBALANIMIDURATION = 500,
        CELL_GLOBALPAGESWITCHDURATION = 300
    };
};

namespace CELL_UTIL{
namespace TOOLS{
extern void setDropShadowEffect(QList<QGraphicsDropShadowEffect*> animis,
                                const QList<QWidget*> &modules,
                                const QPoint &offset,
                                const QColor &color, int blurRadius);
extern void setPropertyAnimation(QList<QPropertyAnimation*> animis,
                                 const QByteArray &_property,
                                 const QVariant &s_value,
                                 const QVariant &e_value, int duration,
                                 QEasingCurve curve,
                                 const QList<QWidget*> &modules,
                                 QGraphicsEffect *effect = nullptr);
extern void multiModulesOneStyleSheet(const QList<QWidget*> &modules, const QString &qss);
extern void setFadeInOrOutAnimation(QGraphicsOpacityEffect *eff,
                                    QPropertyAnimation *animi,
                                    QWidget *target,
                                    int duration,
                                    CellGlobal::FADE_TYPE type);
extern QStyleSheetLoader *styleSheetLoader;
} // namespace TOOLS{
namespace LITERAL{
extern const char* const  INSTANCE_IS_ON;
extern const QString      IMG_DIR;
extern const QString      FONT_DIR;
extern const QString      STYLESHEET_DIR;
extern const QString      LIB_DIR;
extern const QString      COLOR_SPACE_GRAY;
extern const QString      QSS_CUSTOMFRAME_WITH_RADIUS;
extern const QString      QSS_CUSTOMFRAME;
extern const QString      QSS_CUSTOMLABEL;
extern const QString      QSS_CUSTOMBUTTON_STATIC;
extern const QString      QSS_CUSTOMBUTTON_DYNAMIC;

extern const QColor       GRAYLEVEL255;
extern const QColor       GRAYLEVEL70;
extern const QColor       GRAYLEVEL45;
extern const QColor       GRAYLEVEL218;
extern const QColor       GRAYLEVEL30;
extern const QColor       GRAYLEVEL247;
} // namespace LITERAL{
} // namespace UTILITY{
Q_DECLARE_METATYPE(CellGlobal::COLOR_SCHEME);

#endif

