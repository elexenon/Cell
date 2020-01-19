// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CELL_UTIL_H
#define CELL_UTIL_H

namespace CellUiConst{
extern const char* const  INSTANCE_IS_ON;

extern const QString IMG_DIR;
extern const QString FONT_DIR;
extern const QString STYLESHEET_DIR;
extern const QString LIB_DIR;

extern const QString QSS_CUSTOMFRAME_WITH_RADIUS;
extern const QString QSS_CUSTOMFRAME;

extern const QString QSS_CUSTOMLABEL;
extern const QString QSS_CUSTOMLABEL_BACK;
extern const QString QSS_CUSTOMLABEL_TRANSPARENT;

extern const QString QSS_CUSTOMBUTTON_STATIC;
extern const QString QSS_CUSTOMBUTTON_DYNAMIC;
extern const QString QSS_CUSTOMBUTTON_CHECKABLE;

extern const QColor GRAYLEVEL255;
extern const QColor GRAYLEVEL70;
extern const QColor GRAYLEVEL100;
extern const QColor GRAYLEVEL180;
extern const QColor GRAYLEVEL45;
extern const QColor GRAYLEVEL218;
extern const QColor GRAYLEVEL30;
extern const QColor GRAYLEVEL247;
extern const QColor GRAYLEVEL130;
} // namespace CellUiConst{

class QGraphicsDropShadowEffect;
class QPropertyAnimation;
class StyleSheetLoader;
class QGraphicsEffect;
class QGraphicsOpacityEffect;
class QFrame;
class QLabel;

namespace CellUiGlobal{
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
enum LINE_TYPE{
    HLine = 0x0004,
    VLine = 0x0005,
};

enum ANIMIDURATION{
    CELL_GLOBALANIMIDURATION = 700,
    CELL_GLOBALPAGESWITCHDURATION = 300
};
extern void setDropShadowEffect(QList<QGraphicsDropShadowEffect*> &&animis,
                                const QList<QWidget*> &modules,
                                const QPoint &offset,
                                const QColor &color, int blurRadius);
extern void setPropertyAnimation(QList<QPropertyAnimation*> &&animis,
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
                                    CellUiGlobal::FADE_TYPE type);
extern QFrame* getLine(CellUiGlobal::LINE_TYPE type);
extern void setCustomTextLabel(QLabel *label, const QString& fontName, int fontPixelSize, const QString& text = " ");
extern void multiModulesOneStyleSheet(const QList<QWidget*> &modules, const QString &qss);
} // namespace CellUiGlobal{

namespace CellEntityTools{
extern StyleSheetLoader * const styleSheetLoader;
} // namespace CellEntityTools{

#include <QMetaType> // Q_DECLARE_METATYPE()
Q_DECLARE_METATYPE(CellUiGlobal::COLOR_SCHEME);

#endif

