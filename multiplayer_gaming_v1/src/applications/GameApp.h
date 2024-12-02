#ifndef __GAMEAPP_H
#define __GAMEAPP_H

#include <omnetpp.h>
#include <map>
#include <queue>
#include <vector>
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "GamePacket_m.h"
#include "SecurityUtils.h"
#include "GameMetrics.h"

using namespace omnetpp;
using namespace inet;

class GameApp : public cSimpleModule, public ILifecycle {
protected:
    // Parameters
    int localPort;
    int destPort;
    int clientId;
    bool isServer;
    std::string regionId;
    int maxPlayers;

    // State variables
    UdpSocket socket;
    cMessage *gameUpdateTimer;
    cMessage *heartbeatTimer;
    cMessage *stateSyncTimer;
    std::map<int, simtime_t> clientLatencies;
    std::map<int, GameState> playerStates;

    // Security and Performance Metrics
    SecurityUtils securityUtils;
    std::string securityToken;
    GameMetrics metrics;

    // Protected Methods
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    virtual bool handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback) override;

    void processGameUpdate(GamePacket *packet);
    void sendGameUpdate();
    void sendHeartbeat();

public:
    GameApp();
    virtual ~GameApp();
};

#endif
