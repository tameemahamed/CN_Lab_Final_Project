
#include "AnalyticsCollector.h"
#include "inet/common/ModuleAccess.h"
#include "../messages/GamePacket.msg"

Define_Module(AnalyticsCollector);

void AnalyticsCollector::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        localport0 = par("localport0");
        socket.setOutputGate(gate("udpOut"));
        socket.bind(localport0);
        EV << "AnalyticsCollector initialized.\n";
    }
}

void AnalyticsCollector::handleMessage(cMessage *msg) {
    auto packet = check_and_cast<GamePacket *>(msg);
    processAnalytics(packet);
    delete msg;
}

void AnalyticsCollector::processAnalytics(GamePacket *packet) {
    EV << "Processing analytics for client " << packet->getClientId() << "\n";
    // Add analytics logic here
}
