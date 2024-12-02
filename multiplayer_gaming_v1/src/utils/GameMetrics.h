#ifndef __GAMEMETRICS_H
#define __GAMEMETRICS_H

#include <vector>
#include <string>
#include "omnetpp.h"

class GameMetrics {
public:
    void recordLatency(double latency);
    void recordLoad(double load);
    double getAverageLatency();
    double getAverageLoad();

    std::string getLatencyHistory();
    std::string getLoadHistory();

private:
    std::vector<double> latencies;
    std::vector<double> loads;
};

#endif
