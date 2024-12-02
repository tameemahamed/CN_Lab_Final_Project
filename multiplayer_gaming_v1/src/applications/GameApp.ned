package multiplayer_gaming_v1.applications;

import inet.applications.udpapp.UdpBasicApp;

simple GameApp extends inet.applications.udpapp.UdpBasicApp {
    parameters:
        @display("i=device/pc");
        int localPort0 = default(1000);
        int destPort0 = default(2000);
        int clientId = default(1);
        bool isServer = default(false);
        string regionId = default("region1");
}
