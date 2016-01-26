#include "EventManager.hpp"
#include <boost/date_time.hpp>

void EventManager::addEvent(const string& data) {
    json event = json::parse(data);

    boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    event["timestamp"] = boost::posix_time::to_simple_string(now);

    events.push_back(event);
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
