package multiplayer_gaming_v1.applications;

import inet.applications.udpapp.UdpBasicApp;

simple LoadBalancer extends inet.applications.udpapp.UdpBasicApp {
    parameters:
        @display("i=device/router");
        int localPort0 = default(3000);
    gates:
        inout udp;
}
