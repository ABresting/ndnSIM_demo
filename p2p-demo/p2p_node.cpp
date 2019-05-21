// demo_producer.cpp

#include "p2p_node.hpp"


#include "ns3/ndnSIM/helper/ndn-stack-helper.hpp"
#include "ns3/ndnSIM/helper/ndn-fib-helper.hpp"

#include "ns3/random-variable-stream.h"

NS_LOG_COMPONENT_DEFINE("P2P_Node");

namespace ns3 {

// Necessary if you are planning to use ndn::AppHelper
NS_OBJECT_ENSURE_REGISTERED(P2P_Node);

TypeId
P2P_Node::GetTypeId()
{
  static TypeId tid =
    TypeId("P2P_Node")
      .SetGroupName("Ndn")
      .SetParent<ndn::App>()
      .AddConstructor<P2P_Node>();

  return tid;
}

P2P_Node::P2P_Node()
{
}

void
Register(std::string name, std::string pk)
{
  //  method to register the content name and public key as a pair
}

void
Query(std::string name)
{
  //  method returns the latest and valid public key
}

void
Validate(std::string name, std::string pk)
{
  //  method wheather this pair is valid or invalid
}

void
Update(std::string name, std::string pk)
{
  //  method to update the corresponding public key for a registered name
}

void
Revoke(std::string name, std::string pk)
{
  //  method to revoke the name and the public key pair
}

void
P2P_Node::SendInterest(std::string prefix)
{
	auto interest = std::make_shared<ndn::Interest>(prefix);
	Ptr<UniformRandomVariable> rand = CreateObject<UniformRandomVariable>();
	interest->setNonce(rand->GetValue(0, std::numeric_limits<uint32_t>::max()));
	interest->setInterestLifetime(ndn::time::seconds(3));

	NS_LOG_DEBUG("Sending Interest packet for " << interest->getName()<< "\n" << " on Node " << GetNode());

	// Call trace (for logging purposes)
	m_transmittedInterests(interest, this, m_face);

	m_appLink->onReceiveInterest(*interest);
}

void
P2P_Node::OnInterest(std::shared_ptr<const ndn::Interest> interest)
{
  ndn::App::OnInterest(interest); // forward call to perform app-level tracing
  
  NS_LOG_DEBUG("Received the incoming interest for" << interest->getName()<< " on Node " << GetNode());

  std::string demo_register_ACK = "/prefix/registerACK";
  std::string demo_query_ACK = "/prefix/queryACK";
  std::string demo_validate_ACK = "/prefix/validateACK";
  std::string demo_update_ACK = "/prefix/updateACK";
  std::string demo_reovke_ACK = "/prefix/revokeACK";
  std::string demo_NACK = "/prefix/NACK";

  // as per received packet decide the action to be taken
  if ( !interest->getName().compare("/prefix/register"))  //if requets is for prefix "/prefix/req" 
  {

   NS_LOG_DEBUG("Entered here");
	 this->SendInterest(demo_register_ACK);

  }else if ( !interest->getName().compare("/prefix/query"))
  {

    this->SendInterest(demo_query_ACK);

  }else if ( !interest->getName().compare("/prefix/validate"))
  {

    this->SendInterest(demo_validate_ACK);

  }else if ( !interest->getName().compare("/prefix/update/%FE%00"))
  {

    this->SendInterest(demo_update_ACK);

  }else if ( !interest->getName().compare("/prefix/revoke"))
  {

    this->SendInterest(demo_reovke_ACK);

  }else
  {

    this->SendInterest(demo_NACK);

  }

}

void
P2P_Node::StartApplication()
{
  App::StartApplication();

  // equivalent to setting interest filter for "/prefix" prefix
  ndn::FibHelper::AddRoute(GetNode(), "/prefix", m_face, 0);
}

void
P2P_Node::StopApplication()
{
  App::StopApplication();
}


} // namespace ns3
