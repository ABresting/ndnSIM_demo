// ndn-demo.cpp

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/netanim-module.h"

namespace ns3 {

int
main(int argc, char* argv[])
{
  // setting default parameters for PointToPoint links and channels
  Config::SetDefault("ns3::PointToPointNetDevice::DataRate", StringValue("1Mbps"));
  Config::SetDefault("ns3::PointToPointChannel::Delay", StringValue("10ms"));
  Config::SetDefault("ns3::QueueBase::MaxSize", StringValue("20p"));

  // Read optional command-line parameters (e.g., enable visualizer with ./waf --run=<> --visualize
  CommandLine cmd;
  cmd.Parse(argc, argv);

  // Creating nodes
  NodeContainer nodes;
  nodes.Create(3);

  // Connecting nodes using two links via node 1
  PointToPointHelper p2p;
  p2p.Install(nodes.Get(0), nodes.Get(1));
  p2p.Install(nodes.Get(1), nodes.Get(2));
  
  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetDefaultRoutes(true);
  ndnHelper.InstallAll();

  // Choosing forwarding strategy
  ndn::StrategyChoiceHelper::Install(nodes.Get(1),"/prefix", "/localhost/nfd/strategy/best-route");
  

  // Consumer
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  //using the prefix /prefix/req to represent the request for now
  consumerHelper.SetPrefix("/prefix/req");
  consumerHelper.SetAttribute("Frequency", StringValue("1"));
  auto apps = consumerHelper.Install(nodes.Get(0));
  apps.Stop(Seconds(10.0));

  //Producer
  ndn::AppHelper app2("Demo_Producer");
  app2.Install(nodes.Get(2)); // last node
  

  

  Simulator::Stop(Seconds(20.0));

  AnimationInterface anim ("anim1.xml");

  anim.EnablePacketMetadata (true);
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}

} // namespace ns3

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
