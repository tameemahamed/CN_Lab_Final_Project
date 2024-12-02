
#ifndef __SECURITYMODULE_H
#define __SECURITYMODULE_H

#include <omnetpp.h>
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "GamePacket_m.h"

using namespace omnetpp;
using namespace inet;

class SecurityModule : public cSimpleModule {
protected:
    int localport0;
    UdpSocket socket;

    void processSecurityPacket(GamePacket *packet);

    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
