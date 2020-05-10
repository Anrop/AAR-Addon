#include "ArgsProcessor.hpp"
#include "Utils.hpp"

ArgsProcessor::ArgsProcessor(Organizer *organizer) {
    this->organizer = organizer;
}

ArgsProcessor::argsProcessed ArgsProcessor::processUnitPosition(const char **argv, int argc) {
    std::string id(*argv++);
    std::string lifeState(*argv++);
    std::string name(*argv++);
    auto dir = atof(*argv++);
    auto posX = atof(*argv++);
    auto posY = atof(*argv++);
    auto posZ = atof(*argv++);
    std::string side(*argv++);
    std::string uid(*argv++);
    std::string vehicleId(*argv++);

    Utils::unquoteArmaString(&id);
    Utils::unquoteArmaString(&lifeState);
    Utils::unquoteArmaString(&name);
    Utils::unquoteArmaString(&side);
    Utils::unquoteArmaString(&uid);
    Utils::unquoteArmaString(&vehicleId);

    nlohmann::json j;
    j["type"] = "UnitPosition";
    j["player"]["name"] = name;
    j["player"]["uid"] = uid;
    j["unit"]["id"] = id;
    j["unit"]["life_state"] = lifeState;
    j["unit"]["name"] = name;
    j["unit"]["position"]["dir"] = dir;
    j["unit"]["position"]["x"] = posX;
    j["unit"]["position"]["y"] = posY;
    j["unit"]["position"]["z"] = posZ;
    j["unit"]["side"] = side;

    if (!vehicleId.empty()) {
        j["unit"]["vehicle_id"] = vehicleId;
    }

    auto json_str = j.dump();

    auto cacheLookup = unitsCache.find(id);
    if (cacheLookup != unitsCache.end()) {
        auto cached = cacheLookup->second;

        if (json_str.compare(cached) == 0) {
            return ArgsProcessor::EVENT_CACHED;
        }
    }

    unitsCache[id] = json_str;

    EventManager::event_added result = this->organizer->addEvent(json_str);

    if (result == EventManager::EVENT_OK) {
        return ArgsProcessor::EVENT_OK;
    } else {
        return ArgsProcessor::EVENT_ERROR;
    }
}

ArgsProcessor::argsProcessed ArgsProcessor::processVehiclePosition(const char **argv, int argc) {
    std::string id(*argv++);
    std::string name(*argv++);
    auto dir = atof(*argv++);
    auto posX = atof(*argv++);
    auto posY = atof(*argv++);
    auto posZ = atof(*argv++);
    std::string side(*argv++);
    std::string simulation(*argv++);

    Utils::unquoteArmaString(&id);
    Utils::unquoteArmaString(&name);
    Utils::unquoteArmaString(&side);
    Utils::unquoteArmaString(&simulation);

    nlohmann::json j;
    j["type"] = "VehiclePosition";
    j["vehicle"]["id"] = id;
    j["vehicle"]["name"] = name;
    j["vehicle"]["position"]["dir"] = dir;
    j["vehicle"]["position"]["x"] = posX;
    j["vehicle"]["position"]["y"] = posY;
    j["vehicle"]["position"]["z"] = posZ;
    j["vehicle"]["side"] = side;
    j["vehicle"]["simulation"] = simulation;

    auto json_str = j.dump();

    auto cacheLookup = vehicleCache.find(id);
    if (cacheLookup != vehicleCache.end()) {
        auto cached = cacheLookup->second;

        if (json_str.compare(cached) == 0) {
            return ArgsProcessor::EVENT_CACHED;
        }
    }

    vehicleCache[id] = json_str;

    EventManager::event_added result = this->organizer->addEvent(json_str);

    if (result == EventManager::EVENT_OK) {
        return ArgsProcessor::EVENT_OK;
    } else {
        return ArgsProcessor::EVENT_ERROR;
    }
}
