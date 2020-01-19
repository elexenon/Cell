// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CELLGLOBALMACROS_H
#define CELLGLOBALMACROS_H

// INTERFACE IMPLEMENTED BY MARCOS OF CPP
#define _interface class

#define DeclareInterface(name) _interface name{\
public:\
    virtual ~name(){}

#define DeclareInterfaceEnd };

#define implements public
// INTERFACE IMPLEMENTED BY MARCOS OF CPP

# define Static_Public    public
# define Static_Private   private
# define Static_Protected protected

# define Checkable_Public    public
# define Checkable_Private   private
# define Checkable_Protected protected

# define Dynamic_Public    public
# define Dynamic_Private   private
# define Dynamic_Protected protected


#define CHAR2STR(arg) (QString::fromUtf8(arg))

#endif // CELLGLOBALMACROS_H
