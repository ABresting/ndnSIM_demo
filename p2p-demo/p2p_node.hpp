// demo_producer.hpp

#ifndef DEMO_PROD_H_
#define DEMO_PROD_H_

#include "ns3/ndnSIM/apps/ndn-app.hpp"
#include "ns3/log.h"
#include "ns3/ptr.h"
#include "ns3/packet.h"
#include "ns3/ndnSIM-module.h"

namespace ns3 {

class P2P_Node : public ndn::App {
public:
  static TypeId
  GetTypeId();

  P2P_Node();

  // Receive all Interests but do nothing in response
  void
  OnInterest(std::shared_ptr<const ndn::Interest> interest);

private:

  void
  Register(std::string name, std::string pk);

  void
  Query(std::string name);

  void
  Validate(std::string name, std::string pk);

  void
  Update(std::string name, std::string pk);

  void
  Revoke(std::string name, std::string pk);

  void
  SendInterest(std::string prefix);

protected:
  // inherited from Application base class.
  virtual void
  StartApplication();


  virtual void
  StopApplication();

protected:
  double m_frequency; // Frequency of interest packets (in hertz)1

};

} // namespace ns3

#endif // DEMO_PROD_H_
