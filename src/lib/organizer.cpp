#include "common.h"

using namespace std;


/*
	Organizers purpose is to get external data and put it in a buffer (EventManager),
	create a thread if one doesnt exist with a http client and recursively spawn http clients in that thread
	until the buffer of events is empty
*/
class Organizer {
public:
	Organizer();
	void set_hostname(string hostname);
	void set_id(string id);

	enum status_response {OK, UNAUTHORIZED, CONNECTION_FAILED, UNKNOWN};
	struct status_t {
		string id;
		status_response status;
	};

	struct config_t {
    	string hostname;
    	string id;
	};

	Organizer::status_t get_status(const string& s_mission, const string& s_ip);
private:
	config_t settings;
	bool thread_running;
};

Organizer::Organizer() {
	thread_running = false;
}

void Organizer::set_hostname(string hostname) {
	settings.hostname = hostname;
}

void Organizer::set_id(string id) {
	settings.id = id;
}

Organizer::status_t Organizer::get_status(const string& s_mission, const string& s_ip) {
	status_t result;

    ptree pt_;
    pt_.put("mission", s_mission);
    pt_.put("ip", s_ip);
    std::ostringstream json_out;
    write_json(json_out, pt_);

    cout << "sending:" << endl << json_out.str() << endl;

    #ifdef debug
        httpClient *client = new httpClient(settings.hostname, "/post.php", json_out.str());
    #else
        httpClient *client = new httpClient(settings.hostname, "/realtime", json_out.str());
    #endif
    if (client->status == httpClient::OK) {
        /* Read json response */

        std::stringstream ss;
        ss.str(client->get_result());

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss ,pt);

        string status = pt.get<std::string>("status");
        result.id = pt.get<std::string>("id");

        if (status == "ok")
            result.status = Organizer::OK;
        else {
            /* remote server returned non-OK status code. */
            result.status = Organizer::UNKNOWN;
        }
    } else {
    	/* Socked probably failed */
    	result.status = Organizer::CONNECTION_FAILED;
    }

    delete client;
    return result;
}