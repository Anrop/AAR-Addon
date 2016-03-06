#pragma once

#include <boost/thread.hpp>
#include "EventManager.hpp"

#define THREAD_SLEEP_DELAY 500

/*
  Organizers purpose is to get external data and put it in a buffer (EventManager),
  create a thread if one doesnt exist with a http client and recursively spawn http clients in that thread
  until the buffer of events is empty
*/

class Organizer {
public:
  Organizer();
  ~Organizer();
  void setHostname(const std::string& hostname);
  std::string getMissionId();
  void setMissionId(const std::string& id);
  void addEvent(const std::string& data);

  enum status_response {OK, UNAUTHORIZED, CONNECTION_FAILED, PARSE_ERROR, UNKNOWN};

  struct config_t {
      std::string hostname;
      std::string id;
  };

  status_response createMission(const std::string& mission, const std::string& world);
  status_response parseCreateMission(const std::string& data);
private:
  config_t settings;
  bool thread_running;
  EventManager em;
  boost::mutex event_mtx;
  boost::thread *queueThread;

  void processEventQueue();
};
