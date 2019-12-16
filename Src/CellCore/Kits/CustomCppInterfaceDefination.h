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

#define DeclareDerivedInterface(name,base) _interface name:public base{\
public:\
    virtual ~name(){}

#define DeclareInterfaceEnd };

#define implements public

#endif // CUSTOMCPPINTERFACEDEFINATION_H
