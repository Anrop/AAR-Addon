#include "Organizer.hpp"
#include "httpClient.hpp"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

Organizer::Organizer() {
    thread_running = false;
    queueThread = NULL;
}

Organizer::~Organizer() {
    delete queueThread;
}

void Organizer::setHostname(const string& hostname) {
    settings.hostname = hostname;
}

string Organizer::getMissionId() {
    return settings.id;
}

void Organizer::setMissionId(const string& id) {
    settings.id = id;
}

void Organizer::addEvent(const string& data) {
    /* Start a worker thread here if its not already running */

    event_mtx.lock();
    em.addEvent(data);
    event_mtx.unlock();

    if (!thread_running) {
        // Start thread!
        thread_running = true;

        if (queueThread) {
            delete queueThread;
        }

        queueThread = new boost::thread(boost::bind(&Organizer::processEventQueue, this));
    }
}

void Organizer::processEventQueue() {
    /* Supposed to run from an independent thread.
     This method should recursively spawn a httpClient until EventManager is empty*/
    int failCounter = 0;

    do {
        cout << "sending " << std::to_string(em.count()) << " events" << endl;
        if (failCounter > 30) {
            break;  // Stop attempting to send. Retry at a later point in time when there is new data to send. Keep old data buffered
        }

        event_mtx.lock();
        string json_out = em.getJson();
        em.clearEvents();
        event_mtx.unlock();

        httpClient client = httpClient(settings.hostname, ("/api/missions/" + settings.id + "/events"), json_out);

        if (client.status != httpClient::OK) {
            failCounter++;
        }

        /* Sleep thread to let events queue up */
        boost::this_thread::sleep(boost::posix_time::milliseconds(THREAD_SLEEP_DELAY));

    } while (!em.isEmpty());

    thread_running = false;
}

Organizer::status_response Organizer::parseCreateMission(const string& data) {
    try {
        json jsonData = json::parse(data);
        json missionIdJson = jsonData["id"];

        if (missionIdJson.is_string()) {
            setMissionId(missionIdJson.get<std::string>());
            return OK;
        }

        if (missionIdJson.is_number()) {
            int missionId = missionIdJson.get<int>();
            setMissionId(std::to_string(missionId));
            return OK;
        }

        return UNKNOWN;
    } catch (...) {
        return PARSE_ERROR;
    }
}

Organizer::status_response Organizer::createMission(const string& mission, const string& world) {
    json missionJson;
    missionJson["name"] = mission;
    missionJson["world"] = world;

    httpClient client = httpClient(settings.hostname, "/missions", missionJson.dump());
    if (client.status == httpClient::OK) {
        return parseCreateMission(client.getResult());
    } else if (client.status == httpClient::CONNECTION_FAILED) {
        return CONNECTION_FAILED;
    }

    return UNKNOWN;
}
