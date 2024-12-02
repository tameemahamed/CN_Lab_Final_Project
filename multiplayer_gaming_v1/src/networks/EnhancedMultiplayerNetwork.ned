package multiplayer_gaming_v1.networks;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.StandardHost;
import inet.node.ethernet.EthernetSwitch;
import inet.node.wireless.AccessPoint;

import multiplayer_gaming_v1.applications.GameApp;
import multiplayer_gaming_v1.applications.LoadBalancer;
import multiplayer_gaming_v1.applications.SecurityModule;
import multiplayer_gaming_v1.applications.AnalyticsCollector;

network EnhancedMultiplayerNetwork
{
    parameters:
        int numClients = default(10);
        int numServers = default(3);
        int numRegions = default(2);
        double networkLatency @unit(ms) = default(50ms);
        double bandwidthPerClient @unit(Mbps) = default(10Mbps);

    types:
        // Custom channel type with configurable latency and bandwidth
        channel GameNetworkChannel extends ned.DatarateChannel
        {
            delay = networkLatency;
            datarate = bandwidthPerClient;
        }

    submodules:
        // Network Configurator for IP address management
        configurator: Ipv4NetworkConfigurator {
            @display("p=50,50;i=block/network");
        }

        // Load Balancer for distributing game server loads
        loadBalancer: LoadBalancer {
            @display("p=150,100;i=block/routing");
        }

        // Security Module for authentication and protection
        securityModule: SecurityModule {
            @display("p=250,100;i=block/security");
        }

        // Analytics Collector for performance tracking
        analyticsCollector: AnalyticsCollector {
            @display("p=350,100;i=block/awareness");
        }

        // Central network switch
        centralSwitch: EthernetSwitch {
            @display("p=250,250;i=device/switch");
        }

        // Game Servers
        gameServer[numServers]: StandardHost {
            @display("p=100,400,row,100;i=device/server");
        }

        // Game Clients
        gameClient[numClients]: StandardHost {
            @display("p=400,400,row,100;i=device/laptop");
        }

        // Regional Access Points (for simulating geographical distribution)
        regionAccessPoint[numRegions]: AccessPoint {
            @display("p=335,306;i=device/accesspoint");
        }

    connections:
        // Connect Load Balancer to central switch using UDP
        loadBalancer.udp <--> GameNetworkChannel <--> centralSwitch.ethg++;

        // Connect Security Module to central switch using UDP
        securityModule.udp <--> GameNetworkChannel <--> centralSwitch.ethg++;

        // Connect Analytics Collector to central switch using UDP
        analyticsCollector.udp <--> GameNetworkChannel <--> centralSwitch.ethg++;

        // Connect Game Servers to central switch
        for i=0..numServers-1 {
            gameServer[i].ethg++ <--> GameNetworkChannel <--> centralSwitch.ethg++;
        }

        // Connect Game Clients to regional access points
        for i=0..numClients-1 {
            gameClient[i].ethg++ <--> GameNetworkChannel <--> regionAccessPoint[i % numRegions].ethg++;
        }

        // Connect regional access points to central switch
        for i=0..numRegions-1 {
            regionAccessPoint[i].ethg++ <--> GameNetworkChannel <--> centralSwitch.ethg++;
        }
}
