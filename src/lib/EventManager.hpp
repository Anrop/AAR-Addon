#pragma once

#include "json.hpp"

class EventManager {
public:
    enum event_added {EVENT_OK, EVENT_PARSE_ERROR};

    event_added addEvent(const std::string& data);
    std::string getJson();
    void clearEvents();
    bool isEmpty();
    int count();
private:
    nlohmann::json events;
};
