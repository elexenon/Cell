// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CELLNAMESPACE_H
#define CELLNAMESPACE_H

namespace Cell{
    enum class FadeAnimiType{
        FadeIn,
        FadeOut
    };

    enum class ColorScheme{
        Bright,
        Dark
    };

    enum class SwitchMode{
        OnGoing,
        Instant
    };

    enum LineType{
        HLine = 0x0004,
        VLine = 0x0005,
    };

    enum generalItem{
        FrameRadius = 8
    };

    enum AnimiDuration{
        GlobalDuration = 700,
        GlobalPageSwitchDuration = 300
    };
     
    enum CellGrayColor{
        CGL0 = 0,
        CGL30 = 30,
        CGL45 = 45,
        CGL60 = 60,
        CGL70 = 70,
        CGL80 = 80,
        CGL100 = 100,
        CGL130 = 130,
        CGL180 = 180,
        CGL218 = 218,
        CGL230 = 230,
        CGL235 = 235,
        CGL240 = 240,
        CGL245 = 245,
        CGL247 = 247,
        CGL255 = 255
    };

    enum class CellThemeColor{
        pureGreen,
        NavyBlue,
        CellBlue,
        ExitRed,
        yellowGreen
    };
}

#include <QMetaType> // Q_DECLARE_METATYPE()
Q_DECLARE_METATYPE(Cell::ColorScheme)

#endif // CELLNAMESPACE_H
