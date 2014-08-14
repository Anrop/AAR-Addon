#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//#define _WIN32_WINNT 0x0601
#include "common.h"
#define debug true

#include "httpClient.cpp"
#include "json.cpp"
#include "organizer.cpp"

/*
    Windows
    COMPILE WITH:
    -D_WIN32_WINNT=0x0501
    -lboost_system -lboost_thread -lboost_date_time -lwsock32 -lws2_32
*/

using namespace std;

Organizer *organizer = NULL;

extern "C" int APIENTRY DllMain( HINSTANCE hinstDLL, DWORD ul_reason_for_call, LPVOID lpvReserved )
{

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        //organizer = new Organizer();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:

        //delete organizer;
        break;
    }
    return TRUE;
}

extern "C"
{
  __declspec(dllexport) void __stdcall _RVExtension(char *output, int outputSize, const char *function);
};

void __stdcall _RVExtension(char *output, int outputSize, const char *function)
{
    if(!organizer) {
        cout << "creating Organizer" << endl;
        organizer = new Organizer();
    }

    /* Format of function should be function name;data*/
    string s_function(function);
    string function_ = s_function.substr(0, s_function.find(';'));
    string data = s_function.substr(s_function.find(';')+1, s_function.length());

    if (function_ == "setup") {
            cout << "setting hostname to " << data << endl;
            organizer->set_hostname(data);
    }
    else if (function_ == "status") {
        cout << "doing status" << endl;

        Organizer::status_t status = organizer->get_status(data, "127.0.0.1");
        if (status.status == Organizer::OK) {
            organizer->set_id(status.id);
            cout << status.id << endl;
            snprintf(output, outputSize, "%s", status.id.c_str());
        } else {
            if (status.status == Organizer::CONNECTION_FAILED) {
                //cout << "Organizer reports connection failed. Check config" << endl;
            } else {
                //cout << "Organizer reports unknonwn error." << endl;
            }
            strncpy(output, "-1", outputSize);
        }
    } else if (function_ == "event") {
        cout << "adding event: " << data << endl;
        organizer->add_event(data);
    }
}

