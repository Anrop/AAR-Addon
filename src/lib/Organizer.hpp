#include <boost/thread.hpp>
#include "EventManager.cpp"
#include "httpClient.cpp"

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
  string getMissionId();
  void setMissionId(const string& id);
  void addEvent(const string& data);

  enum status_response {OK, UNAUTHORIZED, CONNECTION_FAILED, PARSE_ERROR, UNKNOWN};

  struct config_t {
      string hostname;
      string id;
  };

  status_response createMission(const string& mission, const string& world);
  status_response parseCreateMission(const string& data);
private:
  config_t settings;
  bool thread_running;
  EventManager em;
  boost::mutex event_mtx;
  boost::thread *queueThread;

  void processEventQueue();
};
