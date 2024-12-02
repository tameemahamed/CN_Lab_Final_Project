
#ifndef __LOADBALANCER_H
#define __LOADBALANCER_H

#include <omnetpp.h>
#include <map>
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "GamePacket_m.h"

using namespace omnetpp;
using namespace inet;

class LoadBalancer : public cSimpleModule {
protected:
    int localPort;
    std::map<int, int> serverLoads;
    UdpSocket socket;

    void processRequest(GamePacket *packet);

    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

public:
    LoadBalancer();
};

#endif // __LOADBALANCER_H
```

#### **LoadBalancer.cc**
```cpp
#include "LoadBalancer.h"
#include "inet/common/ModuleAccess.h"
#include "inet/networklayer/common/L3AddressResolver.h"

Define_Module(LoadBalancer);

LoadBalancer::LoadBalancer() {}

void LoadBalancer::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        localPort = par("localPort");
        socket.setOutputGate(gate("udpOut"));
        socket.bind(localPort);
        EV << "LoadBalancer initialized.\n";
    }
}

void LoadBalancer::handleMessage(cMessage *msg) {
    auto packet = check_and_cast<GamePacket *>(msg);
    processRequest(packet);
    delete msg;
}

void LoadBalancer::processRequest(GamePacket *packet) {
    int serverId = 0; // Example: Assign to server 0 for now
    auto response = new GamePacket("loadBalanceResponse");
    response->setClientId(packet->getClientId());
    response->setServerId(serverId);
    response->setMessageType(LOAD_BALANCE_RESPONSE);

    socket.sendTo(response, L3AddressResolver().resolve("server"), localPort);
}
