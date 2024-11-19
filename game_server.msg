message PlayerAction {
    string playerId;
    string action; // e.g., "move", "shoot"
}

message GameStateUpdate {
    string gameState; // e.g., "player1_pos: (x,y)"
}

