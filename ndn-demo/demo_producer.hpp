// demo_producer.hpp

#ifndef DEMO_PROD_H_
#define DEMO_PROD_H_

#include "ns3/ndnSIM/apps/ndn-app.hpp"

namespace ns3 {

class Demo_Producer : public ndn::App {
public:
  static TypeId
  GetTypeId();

  Demo_Producer();

  // Receive all Interests but do nothing in response
  void
  OnInterest(std::shared_ptr<const ndn::Interest> interest);

protected:
  // inherited from Application base class.
  virtual void
  StartApplication();

  virtual void
  StopApplication();
};

} // namespace ns3

#endif // DEMO_PROD_H_
