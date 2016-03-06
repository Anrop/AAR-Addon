#pragma once

#include "json.hpp"

class EventManager {
public:
    void addEvent(const std::string& data);
    std::string getJson();
    void clearEvents();
    bool isEmpty();
    int count();
private:
    nlohmann::json events;
};
