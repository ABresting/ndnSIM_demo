// demo_producer.cpp

#include "demo_producer.hpp"

#include "ns3/log.h"

#include "ns3/ndnSIM/helper/ndn-fib-helper.hpp"

NS_LOG_COMPONENT_DEFINE("Demo_Producer");

namespace ns3 {

// Necessary if you are planning to use ndn::AppHelper
NS_OBJECT_ENSURE_REGISTERED(Demo_Producer);

TypeId
Demo_Producer::GetTypeId()
{
  static TypeId tid = TypeId("Demo_Producer").SetParent<ndn::App>().AddConstructor<Demo_Producer>();

  return tid;
}

Demo_Producer::Demo_Producer()
{
}

void
Demo_Producer::OnInterest(std::shared_ptr<const ndn::Interest> interest)
{
  ndn::App::OnInterest(interest); // forward call to perform app-level tracing
  // do nothing else (hijack interest)

  NS_LOG_DEBUG("Do nothing for incoming interest for" << interest->getName());
}

void
Demo_Producer::StartApplication()
{
  App::StartApplication();

  // equivalent to setting interest filter for "/prefix" prefix
  ndn::FibHelper::AddRoute(GetNode(), "/prefix/req", m_face, 0);
}

void
Demo_Producer::StopApplication()
{
  App::StopApplication();
}

} // namespace ns3
