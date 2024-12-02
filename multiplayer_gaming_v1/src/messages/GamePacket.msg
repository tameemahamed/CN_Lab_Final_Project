// GamePacket.msg
cplusplus {{
#include <vector>
#include <map>
#include <string>
}}

namespace inet;

// Enum for different game message types
enum GameMessageType {
    GAME_JOIN = 0;
    GAME_UPDATE = 1;
    GAME_LEAVE = 2;
    LOAD_BALANCE_REQUEST = 3;
    LOAD_BALANCE_RESPONSE = 4;
    SECURITY_CHECK = 5;
    ANALYTICS_DATA = 6;
    HEARTBEAT = 7;
    GAME_STATE_SYNC = 8;
    PLAYER_ACTION = 9;
}

// Game state representation
class GameState {
    double positionX;
    double positionY;
    double positionZ;
    double velocityX;
    double velocityY;
    double velocityZ;
    int health;
    int score;
    @dynamic vector<int> inventory;
}

// Base GamePacket definition
packet GamePacket {
    int messageType @enum(GameMessageType);
    int clientId;
    int serverId;
    simtime_t timestamp;
    GameState gameState;
    int sequenceNumber;
    double latency;
    string securityToken;
    bool isCompressed;
    int priorityLevel;
    string regionId;
}

// Load Balancer specific packet
packet LoadBalancerPacket extends GamePacket {
    int currentLoad;
    int maxLoad;
    bool isAvailable;
    double serverScore;
    double cpuUsage;
    double memoryUsage;
    double networkUsage;
    int activeConnections;
    @dynamic vector<double> historicalLoads;
}

// Security specific packet
packet SecurityPacket extends GamePacket {
    string encryptedPayload;
    string signature;
    int securityLevel;
    bool isAuthenticated;
    @dynamic vector<string> securityFlags;
}

// Analytics specific packet
packet AnalyticsPacket extends GamePacket {
    double averageLatency;
    double packetLoss;
    double jitter;
    int playerCount;
    @dynamic map<string, double> metrics;
    @dynamic vector<string> events;
}
