
#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <omnetpp.h>
#include "Player_m.h" // Include message header for PlayerAction

using namespace omnetpp;

class GameServer : public cSimpleModule {
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void processPlayerAction(PlayerAction *action);
    void updateGameState();
};

#endif

