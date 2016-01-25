#include "common.h"

#define THREAD_SLEEP_DELAY 500

using namespace std;


/*
  Organizers purpose is to get external data and put it in a buffer (EventManager),
  create a thread if one doesnt exist with a http client and recursively spawn http clients in that thread
  until the buffer of events is empty
*/

class Organizer {
public:
  Organizer();
  ~Organizer();
  void setHostname(const string& hostname);
  void setId(const string& id);
  void addEvent(const string& data);

  enum status_response {OK, UNAUTHORIZED, CONNECTION_FAILED, UNKNOWN};
  struct status_t {
    string id;
    status_response status;
  };

  struct config_t {
      string hostname;
      string id;
  };

  Organizer::status_t getStatus(const string& mission, const string& ip);
private:
  config_t settings;
  bool thread_running;
  EventManager *em;
  boost::mutex event_mtx;
  boost::thread *queueThread;

  void processEventQueue();
};
