// This Module Declares Global Macros For Cell WorkStation Developping.
//
// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.

#ifndef CELLGLOBALMACROS_H
#define CELLGLOBALMACROS_H

//! INTERFACE IMPLEMENTED BY MARCOS OF CPP
#define _interface class

#define DeclareInterface(name) _interface name{\
public:\
    virtual ~name() = default;

#define implements public
//! INTERFACE IMPLEMENTED BY MARCOS OF CPP

# define StaticPublic    public
# define StaticPrivate   private
# define StaticProtected protected

# define CheckablePublic    public
# define CheckablePrivate   private
# define CheckableProtected protected

# define DynamicPublic    public
# define DynamicPrivate   private
# define DynamicProtected protected

#define CHAR2STR(arg) (QStringLiteral(arg))
#define CMPSTR(arg) (QLatin1String(arg))

#define CELL_DEBUG(arg) (QTextStream(stdout) << CHAR2STR("***") + arg + "::")

#define SafeDelete(ptr) \
    if(ptr) { \
        delete(ptr); \
        ptr = nullptr; \
    }

#endif // CELLGLOBALMACROS_H
