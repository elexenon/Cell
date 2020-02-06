// This Module Declares Global Macros For Cell WorkStation Developping.
//
// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This File May Be Used Under The Terms Of The GNU General Public License
// version 3.0 As Published By The Free Software Foundation And Appearing In
// The File LICENSE Included In The Packaging Of This File.

#ifndef CELLGLOBALMACROS_H
#define CELLGLOBALMACROS_H

//! INTERFACE IMPLEMENTED BY MARCOS OF CPP
#define _interface class

#define DeclareInterface(name) _interface name{\
public:\
    virtual ~name(){}

#define DeclareInterfaceEnd };

#define implements public
//! INTERFACE IMPLEMENTED BY MARCOS OF CPP

# define Static_Public    public
# define Static_Private   private
# define Static_Protected protected

# define Checkable_Public    public
# define Checkable_Private   private
# define Checkable_Protected protected

# define Dynamic_Public    public
# define Dynamic_Private   private
# define Dynamic_Protected protected


#define CHAR2STR(arg) (QStringLiteral(arg))
#define CMPCHAR(arg) (QLatin1String(arg))

#endif // CELLGLOBALMACROS_H
