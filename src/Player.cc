
#include "Player.h"

Define_Module(Player);

void Player::initialize() {
    // Initialization code here
}

void Player::handleMessage(cMessage *msg) {
    // Handle incoming messages from the server
    if (auto *update = dynamic_cast<GameStateUpdate *>(msg)) {
        EV << "Received game state update: " << update->getGameState() << endl;
        delete update; // Clean up
    }
}

