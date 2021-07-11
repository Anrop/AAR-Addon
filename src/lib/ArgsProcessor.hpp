#pragma once

#include "Organizer.hpp"

class ArgsProcessor {
public:
    enum argsProcessed {EVENT_OK, EVENT_ERROR, EVENT_CACHED};

    ArgsProcessor(Organizer *organizer);

    ArgsProcessor::argsProcessed processUnitPosition(const char **argv, int argc);
    ArgsProcessor::argsProcessed processVehiclePosition(const char **argv, int argc);
private:
    Organizer *organizer;
    std::map<std::string, std::string> unitsCache;
    std::map<std::string, std::string> vehicleCache;
};
