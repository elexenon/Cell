#ifndef CELLNET_H
#define CELLNET_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include "CellLayer.h"

struct NetParam{
    double LR;
    double LRDecay;
    double momentumPara;

    int numEpochs;
    int batchSize;
    int accFreq;
    int snapInterval;

    bool useBatch;
    bool updateFreq;
    bool saveSnapShot;
    bool useFineTune;

    std::string updateMethod;
    std::string preTrainModel;

    std::vector<std::string> layers;
    std::vector<std::string> layerTypes;

    std::unordered_map<std::string, Param> LParams;

    void
    readNetParam(std::string &filePath);
};

#endif
