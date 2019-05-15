// demo_producer.cpp

#include "demo_producer.hpp"

#include "ns3/log.h"
#include "ns3/ptr.h"
#include "ns3/packet.h"
#include "ns3/ndnSIM/helper/ndn-stack-helper.hpp"
#include "ns3/ndnSIM/helper/ndn-fib-helper.hpp"

#include "ns3/random-variable-stream.h"

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
  
  NS_LOG_DEBUG("Receive the incoming interest for" << interest->getName());

  // as per received packet decide the action to be taken
  if ( interest->getName().compare("/prefix/req"))  //if requets is fpr prefix "/prefix/req" 
  {
	auto interest_resp = std::make_shared<ndn::Interest>("/prefix/rep");
	Ptr<UniformRandomVariable> rand = CreateObject<UniformRandomVariable>();
	interest_resp->setNonce(rand->GetValue(0, std::numeric_limits<uint32_t>::max()));
	interest_resp->setInterestLifetime(ndn::time::seconds(3));

	NS_LOG_DEBUG("Sending Interest packet for " << interest_resp->getName()<< "\n");

	// Call trace (for logging purposes)
	m_transmittedInterests(interest_resp, this, m_face);

	m_appLink->onReceiveInterest(*interest_resp);
  }

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

