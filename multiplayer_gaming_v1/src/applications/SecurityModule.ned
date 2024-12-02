package multiplayer_gaming_v1.applications;

import inet.applications.udpapp.UdpBasicApp;

simple SecurityModule extends inet.applications.udpapp.UdpBasicApp {
    parameters:
        @display("i=device/lock");
        int localPort0 = default(4000);
    gates:
        inout udp;
}
