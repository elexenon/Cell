// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CELL_UTIL_H
#define CELL_UTIL_H

namespace Cell_Const{
extern const char* const      INSTANCE_IS_ON;
extern constexpr QString      IMG_DIR;
extern constexpr QString      FONT_DIR;
extern constexpr QString      STYLESHEET_DIR;
extern constexpr QString      LIB_DIR;
extern constexpr QString      QSS_CUSTOMFRAME_WITH_RADIUS;
extern constexpr QString      QSS_CUSTOMFRAME;
extern constexpr QString      QSS_CUSTOMLABEL;
extern constexpr QString      QSS_CUSTOMLABEL_TRANSPARENT;
extern constexpr QString      QSS_CUSTOMBUTTON_STATIC;
extern constexpr QString      QSS_CUSTOMBUTTON_DYNAMIC;

extern constexpr QColor       GRAYLEVEL255;
extern constexpr QColor       GRAYLEVEL70;
extern constexpr QColor       GRAYLEVEL45;
extern constexpr QColor       GRAYLEVEL218;
extern constexpr QColor       GRAYLEVEL30;
extern constexpr QColor       GRAYLEVEL247;
} // namespace Cell_Const{

class QGraphicsDropShadowEffect;
class QPropertyAnimation;
class StyleSheetLoader;
class QGraphicsEffect;
class QGraphicsOpacityEffect;

namespace CellGlobal{
enum FADE_TYPE{
    _IN,
    _OUT
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
    CELL_GLOBALANIMIDURATION = 700,
    CELL_GLOBALPAGESWITCHDURATION = 300
};
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
extern void setFadeInOrOutAnimation(QGraphicsOpacityEffect *eff,
                                    QPropertyAnimation *animi,
                                    QWidget *target,
                                    int duration,
                                    CellGlobal::FADE_TYPE type);
extern void multiModulesOneStyleSheet(const QList<QWidget*> &modules, const QString &qss);
} // namespace CellGlobal{

namespace CellEntityTools{
extern StyleSheetLoader * const styleSheetLoader;
} // namespace CellEntityTools{

#include <QMetaType> // Q_DECLARE_METATYPE()
Q_DECLARE_METATYPE(CellGlobal::COLOR_SCHEME);

#endif

