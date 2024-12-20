//
// Generated file, do not edit! Created by opp_msgtool 6.0 from messages/GamePacket.msg.
//

#ifndef __GAMEPACKET_M_H
#define __GAMEPACKET_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

// cplusplus {{
#include "inet/common/packet/chunk/Chunk_m.h"
#include <vector>


namespace inet;

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

class GameState {
    double positionX;
    double positionY;
    double positionZ;
    double velocityX;
    double velocityY;
    double velocityZ;
    int health;
    int score;
    std::vector<int> inventory;
}

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

packet LoadBalancerPacket extends GamePacket {
    int currentLoad;
    int maxLoad;
    bool isAvailable;
    double serverScore;
    double cpuUsage;
    double memoryUsage;
    double networkUsage;
    int activeConnections;
    vector<double> historicalLoads;
}

packet SecurityPacket extends GamePacket {
    string encryptedPayload;
    string signature;
    int securityLevel;
    bool isAuthenticated;
    vector<string> securityFlags;
}

packet AnalyticsPacket extends GamePacket {
    double averageLatency;
    double packetLoss;
    double jitter;
    int playerCount;
    map<string, double> metrics;
    vector<string> events;
}
// }}


namespace omnetpp {


}  // namespace omnetpp

#endif // ifndef __GAMEPACKET_M_H

