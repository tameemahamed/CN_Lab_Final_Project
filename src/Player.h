
#ifndef PLAYER_H
#define PLAYER_H

#include <omnetpp.h>
#include "GameServer_m.h"

using namespace omnetpp;

class Player : public cSimpleModule {
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif

