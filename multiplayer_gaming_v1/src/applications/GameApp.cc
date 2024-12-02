#include "GameApp.h"
#include "inet/common/ModuleAccess.h"
#include "inet/networklayer/common/L3AddressResolver.h"

Define_Module(GameApp);

GameApp::GameApp() {
    gameUpdateTimer = nullptr;
    heartbeatTimer = nullptr;
    stateSyncTimer = nullptr;
}

GameApp::~GameApp() {
    cancelAndDelete(gameUpdateTimer);
    cancelAndDelete(heartbeatTimer);
    cancelAndDelete(stateSyncTimer);
}

void GameApp::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        localPort = par("localPort");
        destPort = par("destPort");
        clientId = par("clientId");
        isServer = par("isServer");
        regionId = par("regionId");
        maxPlayers = par("maxPlayers");

        // Set up statistics
        socket.setOutputGate(gate("udpOut"));
        socket.bind(localPort);

        if (!isServer) {
            gameUpdateTimer = new cMessage("gameUpdateTimer");
            scheduleAt(simTime() + uniform(0.1, 0.5), gameUpdateTimer);
        }
    }
}

void GameApp::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        sendGameUpdate();
        scheduleAt(simTime() + uniform(1.0, 2.0), msg);
    } else {
        auto packet = check_and_cast<GamePacket *>(msg);
        processGameUpdate(packet);
        delete msg;
    }
}

void GameApp::processGameUpdate(GamePacket *packet) {
    EV << "Processing game update from client " << packet->getClientId() << "\n";

    if (isServer) {
        auto response = new GamePacket("response");
        response->setMessageType(GAME_UPDATE);
        response->setClientId(packet->getClientId());
        response->setServerId(clientId);
        response->setTimestamp(simTime());

        socket.sendTo(response, L3AddressResolver().resolve("client"), destPort);
    }
}

void GameApp::sendGameUpdate() {
    if (!isServer) {
        auto packet = new GamePacket("gameUpdate");
        packet->setMessageType(GAME_UPDATE);
        packet->setClientId(clientId);
        packet->setTimestamp(simTime());

        socket.sendTo(packet, L3AddressResolver().resolve("server"), destPort);
    }
}

void GameApp::finish() {
    EV << "GameApp finished.\n";
}
```

#### **GameApp.ned**
```ned
package enhanced_multiplayer_gaming.applications;

import inet.applications.udpapp.UdpBasicApp;

simple GameApp extends inet.applications.udpapp.UdpBasicApp {
    parameters:
        @display("i=device/pc");
        int localPort = default(1000);
        int destPort = default(2000);
        int clientId = default(1);
        bool isServer = default(false);
        string regionId = default("region1");
}
