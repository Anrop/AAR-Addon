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
	~Organizer();
	void set_hostname(const string& hostname);
	void set_id(const string& id);
	void add_event(const string& data);

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
	EventManager *em;
	boost::mutex event_mtx;
	boost::thread *queueThread = NULL;

	void processEventQueue();
};

Organizer::Organizer() {
	thread_running = false;
	em = new EventManager;
}

Organizer::~Organizer() {
	delete em;
	delete queueThread;
}

void Organizer::set_hostname(const string& hostname) {
	settings.hostname = hostname;
}

void Organizer::set_id(const string& id) {
	settings.id = id;
}

void Organizer::add_event(const string& data) {
	/* Start a worker thread here if its not already running */

	event_mtx.lock();
	em->add_event(data);
	event_mtx.unlock();

	if (!thread_running) {
		// Start thread!
		thread_running = true;

		if (queueThread)
            delete queueThread;

		queueThread = new boost::thread(boost::bind(&Organizer::processEventQueue, this));
	}
}

void Organizer::processEventQueue() {
	/* Supposed to run from an independent thread.
	 This method should recursively spawn a httpClient until EventManager is empty*/
	int failCounter = 0;

	do {
		cout << "sending " << boost::lexical_cast<string>(em->count()) << " events" << endl;
		if (failCounter > 30)
			break;	// Stop attempting to send. Retry at a later point in time when there is new data to send. Keep old data buffered

		event_mtx.lock();
		string json_out = em->get_json(true);
		event_mtx.unlock();

		#ifdef debug
        	httpClient *client = new httpClient(settings.hostname, "/post.php", json_out);
   		#else
        	httpClient *client = new httpClient(settings.hostname, ("/realtime/:" + settings.id), json_out);
    	#endif

	    if (client->status != httpClient::OK)
	        failCounter++;

    	delete client;
	} while (!em->is_empty());

	thread_running = false;
}

Organizer::status_t Organizer::get_status(const string& s_mission, const string& s_ip) {
	status_t result;

    ptree pt_;
    pt_.put("mission", s_mission);
    pt_.put("ip", s_ip);
    ostringstream json_out;
    write_json(json_out, pt_);

    #ifdef debug
        httpClient *client = new httpClient(settings.hostname, "/post.php", json_out.str());
    #else
        httpClient *client = new httpClient(settings.hostname, "/realtime", json_out.str());
    #endif
    if (client->status == httpClient::OK) {
        /* Read json response */

        stringstream ss;
        ss.str(client->get_result());

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss ,pt);

        string status = pt.get<string>("status");
        result.id = pt.get<string>("id");

        if (status == "ok")
            result.status = Organizer::OK;
        else
            result.status = Organizer::UNKNOWN; /* remote server returned non-OK status code. */

    } else if (client->status == httpClient::CONNECTION_FAILED)
    	result.status = Organizer::CONNECTION_FAILED;
    else
    	result.status = Organizer::UNKNOWN;

    delete client;
    return result;
}
