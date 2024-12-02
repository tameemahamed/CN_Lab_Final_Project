package multiplayer_gaming_v1.applications;

import inet.applications.udpapp.UdpBasicApp;

simple AnalyticsCollector extends inet.applications.udpapp.UdpBasicApp {
    parameters:
        @display("i=device/server");
        int localPort0 = default(5000);
    gates:
        inout udp;
}
