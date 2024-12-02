#include "LoadBalancer.h"
#include "inet/common/ModuleAccess.h"
#include "inet/networklayer/common/L3AddressResolver.h"

Define_Module(LoadBalancer);

LoadBalancer::LoadBalancer() {}

LoadBalancer::~LoadBalancer() {}

void LoadBalancer::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        localPort = par("localPort");

        // Initialize statistics
        loadStats.setName("serverLoadStats");
        loadVector.setName("serverLoadVector");

        // Setup socket
        socket.setOutputGate(gate("udpOut"));
        socket.bind(localPort);

        // Initialize server loads
        for (int serverId : serverPorts) {
            serverLoads[serverId] = 0;
        }
    }
}

void LoadBalancer::handleMessage(cMessage *msg) {
    auto packet = check_and_cast<LoadBalancerPacket *>(msg);

    switch (packet->getMessageType()) {
        case LOAD_BALANCE_REQUEST:
            processLoadBalanceRequest(packet);
            break;

        case GAME_UPDATE:
            // Update server loads based on game updates
            updateServerLoad(packet->getServerId(), packet->getCurrentLoad());
            break;
    }

    delete msg;
}

int LoadBalancer::selectOptimalServer() {
    int optimalServer = -1;
    int minLoad = INT_MAX;

    for (auto const& [serverId, load] : serverLoads) {
        if (load < minLoad) {
            minLoad = load;
            optimalServer = serverId;
        }
    }

    return optimalServer;
}

void LoadBalancer::updateServerLoad(int serverId, int load) {
    serverLoads[serverId] = load;
    loadStats.collect(load);
    loadVector.record(load);
}

void LoadBalancer::processLoadBalanceRequest(LoadBalancerPacket *packet) {
    int optimalServer = selectOptimalServer();

    auto response = new LoadBalancerPacket("loadBalanceResponse");
    response->setMessageType(LOAD_BALANCE_RESPONSE);
    response->setServerId(optimalServer);
    response->setClientId(packet->getClientId());
    response->setTimestamp(simTime());

    socket.sendTo(response, L3AddressResolver().resolve(packet->getSenderModule()->getFullPath().c_str()), packet->getArrivalGate()->getIndex());
}

void LoadBalancer::finish() {
    recordScalar("average server load", loadStats.getMean());
    recordScalar("max server load", loadStats.getMax());
}
