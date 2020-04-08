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
}
