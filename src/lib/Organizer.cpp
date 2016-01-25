#include "Organizer.hpp"

Organizer::Organizer() {
	thread_running = false;
	em = new EventManager;
	queueThread = NULL;
}

Organizer::~Organizer() {
	delete em;
	delete queueThread;
}

void Organizer::setHostname(const string& hostname) {
	settings.hostname = hostname;
}

void Organizer::setId(const string& id) {
	settings.id = id;
}

void Organizer::addEvent(const string& data) {
	/* Start a worker thread here if its not already running */

	event_mtx.lock();
	em->addEvent(data);
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
		string json_out = em->getJson(true);
		event_mtx.unlock();

		#ifdef debug
        	httpClient *client = new httpClient(settings.hostname, "/post.php", json_out);
   		#else
        	httpClient *client = new httpClient(settings.hostname, ("/api/missions/" + boost::lexical_cast<string>(settings.id) + "/events"), json_out);
    	#endif

	    if (client->status != httpClient::OK)
	        failCounter++;

    	delete client;

    	/* Sleep thread to let events queue up */
    	boost::this_thread::sleep(boost::posix_time::milliseconds(THREAD_SLEEP_DELAY));

	} while (!em->isEmpty());

	thread_running = false;
}

Organizer::status_t Organizer::getStatus(const string& mission, const string& ip) {
	status_t result;

    ptree pt_;
    pt_.put("mission", mission);
    pt_.put("ip", ip);
    ostringstream json_out;
    write_json(json_out, pt_);

    httpClient *client = new httpClient(settings.hostname, "/api/missions", json_out.str());
    if (client->status == httpClient::OK) {
        /* Read json response */
        stringstream ss;
        ss.str(client->getResult());

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss ,pt);

        result.id = pt.get<string>("_id");
        result.status = Organizer::OK;

    } else if (client->status == httpClient::CONNECTION_FAILED)
    	result.status = Organizer::CONNECTION_FAILED;
    else
    	result.status = Organizer::UNKNOWN;

    delete client;
    return result;
}
