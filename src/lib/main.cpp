// internal working name: gestapo

// http://stackoverflow.com/questions/2114466/creating-json-arrays-in-boost-using-property-trees

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <iostream>

#include "httpClient.cpp"
#include "json.cpp"

#define debug true


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
using boost::asio::ip::tcp;

boost::mutex mtx_;
boost::mutex s_mtx_;

bool threadRunning;
std::string out_buffer;


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

void addData(const string& data) {
    mtx_.lock();
        out_buffer += data;
    mtx_.unlock();

    // Check if thread is running, if not then start it.
    s_mtx_.lock();
        bool _running = threadRunning;
    s_mtx_.unlock();

    if (!_running) {
        cout << "thread not running, starting" << endl;
        s_mtx_.lock();
            threadRunning = true;
        s_mtx_.unlock();
        boost::thread workerThread(workerFunc);
    }
}

/* ----------------------------------------------------------------------------------------------- */

struct config_t {
    std::string hostname;
};

config_t config;

/*  Post mission name and ip to server, get id and status response */
std::string get_id(const string& s_mission, const string& s_ip) {
    std::string result = "";

    ptree pt_;
    pt_.put("mission", s_mission);
    pt_.put("ip", s_ip);
    std::ostringstream json_out;
    write_json(json_out, pt_);

    cout << "sending:" << endl << json_out.str() << endl;

    #ifdef debug
        httpClient *client = new httpClient(config.hostname, "/post.php", json_out.str());
    #else
        httpClient *client = new httpClient(config.hostname, "/realtime", json_out.str());
    #endif
    if (client->status == httpClient::OK) {
        /* Read json response */

        std::stringstream ss;
        ss.str(client->get_result());

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss ,pt);

        std::string status = pt.get<std::string>("status");
        std::string id = pt.get<std::string>("id");

        if (status == "ok")
            result = id;
        else
            result = status;
    }

    delete client;
    return result;
}

int main()
{
    config.hostname = "sigkill.me";
    cout << "ID from server: " << get_id("zargabad.pbo", "127.0.0.1") << endl;
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
