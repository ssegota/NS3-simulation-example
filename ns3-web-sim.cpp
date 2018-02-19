/*
                                       n7 ----- n8
                                       /
                                      /
  n3 ----\                 /-------- n6 ----- n9
          \               /                    \
  n2 ---- n4 ----------- n5 -------- n11        \
          /               \                     n10
  n1 ----/                 \-------- n12
  /
 /
n0

 */

#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/internet-module.h>
#include <ns3/point-to-point-module.h>
#include <ns3/applications-module.h>

using namespace ns3;
//stvaranje globalnih varijabli za odbačene i primljene pakete
int g_droppedPacketsAtNode4=0;
int g_droppedPacketsAtNode5=0;
//funkcija za ispis i brojanje odbačenih paketa
void QueueTailDropAtNode4 (Ptr<const Packet> p){
	g_droppedPacketsAtNode4++;
}
//f-ja za ispisi brojanje dostavljenih paketa
void QueueTailDropAtNode(Ptr<const Packet> p){
	g_droppedPacketsAtNode5++;
}


int main ()
{
	
//omogučavanje ispisa
	LogComponentEnable ("OnOffApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("PacketSink", LOG_LEVEL_INFO);
  	LogComponentEnable ("ErrorModel", LOG_LEVEL_INFO);
/////Stvaranje ćvorova prema zadanom layoutu mreže
	NodeContainer allNodes, nodes01, nodes14, nodes24, nodes34, nodes45, nodes512, nodes511, nodes56, nodes67, nodes78, nodes69, nodes910;
	allNodes.Create (13);
	
	nodes01.Add(allNodes.Get (0));
	nodes14.Add (allNodes.Get (1));
	nodes24.Add (allNodes.Get (2));
	nodes34.Add (allNodes.Get (3));
	nodes45.Add (allNodes.Get (4));
	nodes56.Add (allNodes.Get (5));
	nodes511.Add (allNodes.Get (5));
	nodes512.Add (allNodes.Get (5));
	nodes67.Add (allNodes.Get (6));
	nodes69.Add (allNodes.Get (6));
	nodes78.Add (allNodes.Get (7));
	nodes910.Add (allNodes.Get (9));
	nodes01.Add(allNodes.Get (1));
	nodes14.Add (allNodes.Get (4));
	nodes24.Add (allNodes.Get (4));
	nodes34.Add (allNodes.Get (4));
	nodes45.Add (allNodes.Get (5));
	nodes56.Add (allNodes.Get (6));
	nodes511.Add (allNodes.Get (11));
	nodes512.Add (allNodes.Get (12));
	nodes67.Add (allNodes.Get (7));
	nodes69.Add (allNodes.Get (9));
	nodes78.Add (allNodes.Get (8));
	nodes910.Add (allNodes.Get (10));
	

////////////////////Definicija parametara mreže
	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("100Mbps"));
	pointToPoint.SetChannelAttribute ("Delay", StringValue ("20ms"));

	PointToPointHelper pointToPoint2;
	pointToPoint2.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
	pointToPoint2.SetChannelAttribute ("Delay", StringValue ("50ms"));
/////////////////Stvaranje uređaja na čvorovima
	NetDeviceContainer devices01, devices14, devices24, devices34, devices45, devices56, devices511, devices512, devices67, devices69, devices78, devices910;
	devices01 = pointToPoint.Install (nodes01);
	devices14 = pointToPoint.Install (nodes14);
	devices24 = pointToPoint.Install (nodes24);
	devices34 = pointToPoint.Install (nodes34);
	devices45 = pointToPoint2.Install (nodes45);
	devices56 = pointToPoint2.Install (nodes56);
	devices511 = pointToPoint.Install (nodes511);
	devices512 = pointToPoint.Install (nodes512);
	devices67 = pointToPoint.Install (nodes67);
	devices69 = pointToPoint.Install (nodes69);
	devices78 = pointToPoint.Install (nodes78);
	devices910 = pointToPoint.Install (nodes910);
/////////////////////////////Sim greške

/////////////////////////////

	InternetStackHelper stack;
	stack.Install (allNodes);
//////////////////Dodjela adresa uređajima na čvorovima
	
	Ipv4AddressHelper address1;
	address1.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces01 = address1.Assign (devices01);
	
	Ipv4AddressHelper address2;
	address2.SetBase ("10.1.2.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces14 = address2.Assign (devices14);
	
	Ipv4AddressHelper address3;
	address3.SetBase ("10.1.3.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces24 = address3.Assign (devices24);
	
	Ipv4AddressHelper address4;
	address4.SetBase ("10.1.4.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces34 = address4.Assign (devices34);

	
	Ipv4AddressHelper address5;
	address5.SetBase ("10.1.5.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces45 = address5.Assign (devices45);
	
	
	Ipv4AddressHelper address6;
	address6.SetBase ("10.1.6.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces56 = address6.Assign (devices56);
	
	
	Ipv4AddressHelper address7;
	address7.SetBase ("10.1.7.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces511 = address7.Assign (devices511);
	
	
	Ipv4AddressHelper address8;
	address8.SetBase ("10.1.8.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces512 = address8.Assign (devices512);
	
	
	Ipv4AddressHelper address9;
	address9.SetBase ("10.1.9.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces67 = address9.Assign (devices67);
	
	
	Ipv4AddressHelper address10;
	address10.SetBase ("10.1.10.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces69 = address10.Assign (devices69);
	
	
	Ipv4AddressHelper address11;
	address11.SetBase ("10.1.11.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces78 = address11.Assign (devices78);
	
	
	Ipv4AddressHelper address12;
	address12.SetBase ("10.1.12.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces910 = address12.Assign (devices910);




/////////////////Stvaranje routing tablica
	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
	
///////Stvaranje TCP aplikacija i sinkova
////sinkovi
	PacketSinkHelper sink1 ("ns3::TcpSocketFactory", InetSocketAddress (interfaces78.GetAddress(1), 8));
	ApplicationContainer apps1 = sink1.Install (nodes910.Get (1));
	apps1.Start (Seconds (4.0));
	apps1.Stop (Seconds (1201.0));
//  
    PacketSinkHelper sink2 ("ns3::TcpSocketFactory", InetSocketAddress (interfaces910.GetAddress(1), 9));
	ApplicationContainer apps2 = sink2.Install (nodes512.Get (1));
	apps2.Start (Seconds (4.0));
	apps2.Stop (Seconds (1201.0));
//  
  PacketSinkHelper sink3 ("ns3::TcpSocketFactory", InetSocketAddress (interfaces512.GetAddress(1), 10));
	ApplicationContainer apps3 = sink3.Install (nodes512.Get (1));
	apps3.Start (Seconds (4.0));
	apps3.Stop (Seconds (1201.0));
///TCP on-off aplikacije
	OnOffHelper onOffApp1 ("ns3::TcpSocketFactory", InetSocketAddress (interfaces78.GetAddress (1), 8));
	onOffApp1.SetAttribute ("DataRate", StringValue ("30Mbps"));
	onOffApp1.SetAttribute ("PacketSize", UintegerValue (2048));
	onOffApp1.SetAttribute ("OnTime", StringValue ("ns3::UniformRandomVariable[Min=20.0|Max=60.0]"));
	onOffApp1.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=5.0]"));
  
    OnOffHelper onOffApp2 ("ns3::TcpSocketFactory", InetSocketAddress (interfaces910.GetAddress (1), 9));
	onOffApp2.SetAttribute ("DataRate", StringValue ("30Mbps"));
	onOffApp2.SetAttribute ("PacketSize", UintegerValue (2048));
	onOffApp2.SetAttribute ("OnTime", StringValue ("ns3::UniformRandomVariable[Min=20.0|Max=60.0]"));
	onOffApp2.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=5.0|"));

    OnOffHelper onOffApp3 ("ns3::TcpSocketFactory", InetSocketAddress (interfaces512.GetAddress (1), 10));
	onOffApp3.SetAttribute ("DataRate", StringValue ("30Mbps"));
	onOffApp3.SetAttribute ("PacketSize", UintegerValue (2048));
	onOffApp3.SetAttribute ("OnTime", StringValue ("ns3::UniformRandomVariable[Min=20.0][Max=60.0]"));
	onOffApp3.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=5.0|"));


//Instalacija aplikacija na zadanim čvorovima
	ApplicationContainer clientApps1 = onOffApp1.Install (nodes01.Get (0));
	clientApps1.Start (Seconds (5.0));
	clientApps1.Stop (Seconds (1200.0));
  
	ApplicationContainer clientApps2 = onOffApp2.Install (nodes01.Get (1));
	clientApps2.Start (Seconds (5.0));
	clientApps2.Stop (Seconds (1200.0));
  
	ApplicationContainer clientApps3 = onOffApp3.Install (nodes34.Get (0));
	clientApps3.Start (Seconds (5.0));
	clientApps3.Stop (Seconds (1200.0));

///////pokretanje simulacije
	Simulator::Run ();
	Simulator::Destroy ();
//ispis globalnih varijabli za dostavljene i odbačene pakete
	std::cout<<"Packets Dropped:\t"<<g_droppedPackets<<"\nPackets Received\t"<<g_receivedPackets<<std::endl;
	return 0;
}


	
