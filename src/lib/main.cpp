#include <iostream>
#include <nlohmann/json.hpp>

#include "Config.hpp"
#include "ArgsProcessor.hpp"
#include "Organizer.hpp"
#include "Utils.hpp"

using namespace std;

Config config;
Organizer organizer;
ArgsProcessor eventProcessor(&organizer);

extern "C" {
#ifdef WIN32
    __declspec (dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
    __declspec (dllexport) int __stdcall RVExtensionArgs(char *output, int outputSize, const char *function, const char **argv, int argc);
#else
    void RVExtension(char *output, int outputSize, const char *function);
    int RVExtensionArgs(char *output, int outputSize, const char *function, const char **argv, int argc);
#endif
}

#ifdef WIN32
void __stdcall RVExtension(char *output, int outputSize, const char *function)
#else
void RVExtension(char *output, int outputSize, const char *function)
#endif
{
    /* Format of function should be function name;data*/
    string s_function(function);
    string function_ = s_function.substr(0, s_function.find(';'));
    string data = s_function.substr(s_function.find(';')+1, s_function.length());

    if (function_ == "init") {
        bool result = config.parseConfigFile();

        if (result) {
            std::string hostname = config.getHostname();

            if (hostname != "") {
                organizer.setAuthorization(config.getAuthorization());
                organizer.setHostname(hostname);
                strncpy(output, hostname.c_str(), outputSize);
                return;
            }
        }

        strncpy(output, "ERROR", outputSize);
    } else if (function_ == "mission") {
        /* TODO: Get IP of current machine */
        Organizer::status_response status = organizer.createMission(data);
        if (status == Organizer::OK) {
            cout << "Organizer reports connection OK! ID: " << organizer.getMissionId() << endl;
            snprintf(output, outputSize, "%s", organizer.getMissionId().c_str());
        } else {
            if (status == Organizer::CONNECTION_FAILED) {
                cout << "Organizer reports connection failed. Check config" << endl;
            } else if (status == Organizer::PARSE_ERROR) {
                cout << "Organiser reports parse error when creating mission" << endl;
            } else {
                cout << "Organizer reports unknown error." << endl;
            }
            strncpy(output, "-1", outputSize);
        }
    } else if (function_ == "event") {
        EventManager::event_added result = organizer.addEvent(data);

        if (result == EventManager::EVENT_OK) {
            strncpy(output, "OK", outputSize);
        } else {
            strncpy(output, "ERROR", outputSize);
        }
    }
}

#ifdef WIN32
int __stdcall RVExtensionArgs(char *output, int outputSize, const char *function, const char **argv, int argc)
#else
int RVExtensionArgs(char *output, int outputSize, const char *function, const char **argv, int argc)
#endif
{
    std::string s_function(function);
    if (s_function == "unitPosition") {
        auto status = eventProcessor.processUnitPosition(argv, argc);

        if (status == ArgsProcessor::EVENT_OK) {
            strncpy(output, "OK", outputSize);
        } else if (status == ArgsProcessor::EVENT_CACHED) {
            strncpy(output, "CACHED", outputSize);
        }  else if (status == ArgsProcessor::EVENT_ERROR) {
            strncpy(output, "ERROR", outputSize);
        }
    } else if (s_function == "vehiclePosition") {
        auto status = eventProcessor.processVehiclePosition(argv, argc);

        if (status == ArgsProcessor::EVENT_OK) {
            strncpy(output, "OK", outputSize);
        } else if (status == ArgsProcessor::EVENT_CACHED) {
            strncpy(output, "CACHED", outputSize);
        } else if (status == ArgsProcessor::EVENT_ERROR) {
            strncpy(output, "ERROR", outputSize);
        }
    }

    return 0;
}
