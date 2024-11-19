
#include "GameServer.h"

Define_Module(GameServer);

void GameServer::initialize() {
    // Initialization code here
}

void GameServer::handleMessage(cMessage *msg) {
    if (auto *action = dynamic_cast<PlayerAction *>(msg)) {
        processPlayerAction(action);
        delete action; // Clean up
    }
}

void GameServer::processPlayerAction(PlayerAction *action) {
    // Update game state based on player action
    EV << "Received action from player: " << action->getPlayerId() << " - " << action->getAction() << endl;
    updateGameState();
}

void GameServer::updateGameState() {
    // Create and send a game state update to all players
    GameStateUpdate *update = new GameStateUpdate("gameStateUpdate");
    update->setGameState("Updated game state");
    // Send to all players (assuming you have a way to reference them)
    // TODO: Implement sending logic
    send(update, "toPlayer");
}

