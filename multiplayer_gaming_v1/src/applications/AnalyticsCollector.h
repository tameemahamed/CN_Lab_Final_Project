#ifndef __ANALYTICSCOLLECTOR_H
#define __ANALYTICSCOLLECTOR_H

#include <omnetpp.h>
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "../messages/GamePacket_m.h"

using namespace omnetpp;
using namespace inet;

class AnalyticsCollector : public cSimpleModule {
protected:
    int localport0;
    UdpSocket socket;

    void processAnalytics(GamePacket *packet);

    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
