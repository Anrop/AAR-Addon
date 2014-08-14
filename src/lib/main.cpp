// internal working name: gestapo

#include "common.h"
#define debug true

#include "httpClient.cpp"
#include "json.cpp"
#include "organizer.cpp"

using namespace std;


int main()
{
    Organizer *organizer = new Organizer();
    organizer->set_hostname("sigkill.me");

    Organizer::status_t status = organizer->get_status("zargabad.pbo", "127.0.0.1");
    if (status.status == Organizer::OK) {
        cout << "Organizer reports OK." << endl << "ID: " << status.id << endl;
        organizer->set_id(status.id);
    } else {
        if (status.status == Organizer::CONNECTION_FAILED) {
            cout << "Organizer reports connection failed. Check config" << endl;
        } else {
            cout << "Organizer reports unknonwn error." << endl;
        }
    }

    organizer->add_event("type=player_connected;uid=1337;name=xealot;pid=1000");
    organizer->add_event("type=player_position;name=zip;pid=2000;latitude=265;longitude=195");

    cout << "Press enter to exit (if events are still being transmitted the program will segfault)" << endl;
    cin.get();

    delete organizer;
    return 0;
}
