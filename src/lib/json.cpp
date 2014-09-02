#include "common.h"

using namespace std;
using namespace boost::spirit;
using boost::property_tree::ptree;

class EventManager {
public:
    void addEvent(const string& data);
    string getJson();
    string getJson(bool clear_events);
    void clearEvents();
    bool isEmpty();
    int count();
private:
    void addEvent(const string& data, vector< map<string,string> > &events_);
    string generateJson(vector< map<string,string> > &events_);
    vector< map<string,string> > events; 
};

void EventManager::addEvent(const string& data) {
    addEvent(data, events);
}

bool EventManager::isEmpty() {
    return events.empty();
}

int EventManager::count() {
    return events.size();
}

string EventManager::getJson() {
    return EventManager::getJson(false);
}

string EventManager::getJson(bool clear_events) {
    string result = generateJson(events);
    
    if (clear_events)
        EventManager::clearEvents();

    return result;
}

void EventManager::clearEvents() {
    events.clear();
}

void EventManager::addEvent(const string& data, vector< map<string,string> > &events_) {
    string str = data;

    map<string,string> contents;
    string::iterator first = str.begin();
    string::iterator last  = str.end();

    const bool result = qi::phrase_parse(first,last, 
        *( *(qi::char_-"=")  >> qi::lit("=") >> *(qi::char_-";") >> -qi::lit(";") ),
        ascii::space, contents);                                  

    /* Add local timestamp to the event */
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    contents["timestamp"] = boost::posix_time::to_simple_string(now);
    
    events_.push_back(contents);
}

string EventManager::generateJson(vector< map<string,string> > &events_) {
    ptree pt;
    ptree children;

    for(vector< map<string,string> >::iterator it = events.begin(); it != events.end(); ++it) {
        map<string,string> event = *it;
        map<string, string>::iterator iter;

        ptree child;
        for (iter = event.begin(); iter != event.end(); ++iter) {
            child.put(iter->first, iter->second);
        }
        children.push_back(make_pair("", child));
    }

    pt.add_child("events", children);

    ostringstream out; 
    write_json(out, pt);
    return out.str();
}
