// internal working name: gestapo

// http://stackoverflow.com/questions/2114466/creating-json-arrays-in-boost-using-property-trees

#include "common.h"
#define debug true

#include "httpClient.cpp"
#include "json.cpp"
#include "organizer.cpp"


/*
TODO: Bygg en funktion för att parsea arma arrayer och bygg upp JSON data baserat på det
Bygg en funktion som genererar ett HTTP POST anrop med JSON (se http.txt)

*/


/*

    boost::mutex mtx_;

    mtx_.lock();
     // Do sth with variable
    mtx_.unlock();

*/

using namespace std;

boost::mutex mtx_;
boost::mutex s_mtx_;


/*
void workerFunc() {
    cout << "thread started" << endl;
    s_mtx_.lock();
        threadRunning = true;
    s_mtx_.unlock();
    cout << "threadRunning locked and true" << endl;

    do {
        httpSocketClient();
        boost::posix_time::seconds workTime(1);
        boost::this_thread::sleep(workTime);
    } while (!out_buffer.empty());

    s_mtx_.lock();
        threadRunning = false;
    s_mtx_.unlock();
    cout << "thread done, exiting" << endl;
}
*/

/* ----------------------------------------------------------------------------------------------- */

int main()
{
    Organizer *organizer = new Organizer();
    organizer->set_hostname("sigkill.me");

    Organizer::status_t status = organizer->get_status("zargabad.pbo", "127.0.0.1");
    if (status.status == Organizer::OK) {
        cout << "Organizer reports OK." << endl << "ID: " << status.id << endl;
    } else {
        if (status.status == Organizer::CONNECTION_FAILED) {
            cout << "Organizer reports connection failed. Check config" << endl;
        } else {
            cout << "Organizer reports unknonwn error." << endl;
        }
    }

    delete organizer;

    /*
    EventManager *em = new EventManager();
    em->add_event("type=player_connected;uid=1337;name=xealot;pid=1000");
    em->add_event("type=player_position;name=zip;pid=2000;latitude=265;longitude=195");
    //cout << em->get_json() << endl;


    httpClient *client = new httpClient("http://sigkill.me/post.php", em->get_json(true));
    if (client->status == httpClient::OK) {
        cout << "http post OK!" << endl;
    } else {
        cout << "failed with error code " << client->status << endl;
    }

    //cout << "'" << client->get_result() << "'" << endl;

    delete client;


    em->add_event("type=player_disconnected;uid=1337;name=xealot;pid=1000");
    //cout << em->get_json() << endl;
    delete em;
    */

    cin.get();
    return 0;
}
