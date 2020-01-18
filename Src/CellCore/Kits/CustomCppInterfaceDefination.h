// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMCPPINTERFACEDEFINATION_H
#define CUSTOMCPPINTERFACEDEFINATION_H

#define _interface class

#define DeclareInterface(name) _interface name{\
public:\
    virtual ~name(){}

#define DeclareInterfaceEnd };

#define implements public

#define Static_Public    public
#define Static_Private   private
#define Static_Protected protected

#define Checkable_Public    public
#define Checkable_Private   private
#define Checkable_Protected protected

#define Dynamic_Public    public
#define Dynamic_Private   private
#define Dynamic_Protected protected

#endif // CUSTOMCPPINTERFACEDEFINATION_H
