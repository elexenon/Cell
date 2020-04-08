#ifndef CELLLAYER_H
#define CELLLAYER_H

#include <iostream>

struct Param{
    int convStride;
    int convPad;
    int convWidth;
    int convHeight;
    int convKernels;

    int poolStride;
    int poolWidth;
    int poolHeight;

    int fcKernels;
};

#endif
