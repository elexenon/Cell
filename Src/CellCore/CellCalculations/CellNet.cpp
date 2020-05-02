#include <json/json.h>
#include <fstream>
#include <cassert>

#include "CellNet.h"

void NetParam::readNetParam(std::string &filePath){
    std::ifstream inFS;
    inFS.open(filePath);
    assert(inFS.is_open());

    Json::Reader reader;
    Json::Value  value;

    // 读取Json train对象参数
    if(reader.parse(inFS, value)){
        if(!value["train"].isNull()){
            auto &params = value["train"];
            this->LR = params["learning rate"].asDouble();
            this->LRDecay = params["LR decay"].asDouble();
            this->updateMethod = params["update method"].asString();
            this->momentumPara = params["momentum parameter"].asDouble();
            this->numEpochs = params["num epochs"].asInt();
            this->useBatch = params["use batch"].asBool();
            this->batchSize = params["batch size"].asInt();
            this->accFreq = params["acc frequence"].asInt();
            this->updateFreq = params["update frequence"].asBool();
            this->saveSnapShot = params["save snapshot"].asBool();
            this->snapInterval = params["snapshot interval"].asInt();
            this->useFineTune = params["fine_tune"].asBool();
            this->preTrainModel = params["pre train model"].asString();
        }
    }

    if(!value["net"].isNull()){
        auto &nparam = value["net"];
        for(int i = 0;i < (int)nparam.size();i ++){
            auto &ii = nparam[i];
            this->layers.push_back(ii["name"].asString());
            this->layerTypes.push_back(ii["type"].asString());

            std::string netType = ii["type"].asString();

            if(netType == "Conv"){
                int num = ii["kernel num"].asInt();
                int width = ii["kernel width"].asInt();
                int height = ii["kernel height"].asInt();
                int pad = ii["pad"].asInt();
                int stride = ii["stride"].asInt();

                this->LParams[netType].convKernels = num;
                this->LParams[netType].convWidth = width;
                this->LParams[netType].convHeight = height;
                this->LParams[netType].convPad = pad;
                this->LParams[netType].convStride = stride;
            }
            if(netType == "Pool"){
                int width = ii["kernel width"].asInt();
                int height = ii["kernel height"].asInt();
                int stride = ii["stride"].asInt();

                this->LParams[netType].poolWidth = width;
                this->LParams[netType].poolHeight = height;
                this->LParams[netType].poolStride = stride;
            }
            if(netType == "Fc"){
                int num = ii["kernel num"].asInt();

                this->LParams[netType].fcKernels = num;
            }
        }
    }
}
