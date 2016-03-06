#include "EventManager.hpp"
#include <boost/date_time.hpp>

using json = nlohmann::json;
using namespace std;

EventManager::event_added EventManager::addEvent(const string& data) {
    try {
        json event = json::parse(data);

        boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
        event["timestamp"] = boost::posix_time::to_simple_string(now);

        events.push_back(event);
        return EVENT_OK;
      } catch (...) {
          return EVENT_PARSE_ERROR;
      }
}

bool EventManager::isEmpty() {
    return events.empty();
}

int EventManager::count() {
    return events.size();
}

string EventManager::getJson() {
    json root;
    root["events"] = events;
    return root.dump();
}

void EventManager::clearEvents() {
    events.clear();
}
