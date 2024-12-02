#include "GameMetrics.h"

void GameMetrics::recordLatency(double latency) {
    latencies.push_back(latency);
}

void GameMetrics::recordLoad(double load) {
    loads.push_back(load);
}

double GameMetrics::getAverageLatency() {
    double sum = 0;
    for (double latency : latencies) {
        sum += latency;
    }
    return latencies.empty() ? 0 : sum / latencies.size();
}

double GameMetrics::getAverageLoad() {
    double sum = 0;
    for (double load : loads) {
        sum += load;
    }
    return loads.empty() ? 0 : sum / loads.size();
}

std::string GameMetrics::getLatencyHistory() {
    std::string history;
    for (double latency : latencies) {
        history += std::to_string(latency) + " ";
    }
    return history;
}

std::string GameMetrics::getLoadHistory() {
    std::string history;
    for (double load : loads) {
        history += std::to_string(load) + " ";
    }
    return history;
}
