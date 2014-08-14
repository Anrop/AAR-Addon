#include "common.h"

using namespace std;
using namespace boost::spirit;
using boost::property_tree::ptree;

class EventManager {
public:
    void add_event(const string& data);
    string get_json();
    string get_json(bool clear_events);
    void clear_events();
    bool is_empty();
private:
    void addEvent(const string& data, vector< map<string,string> > &events_);
    string generateJson(vector< map<string,string> > &events_);
    vector< map<string,string> > events; 
};

void EventManager::add_event(const string& data) {
    addEvent(data, events);
}

bool EventManager::is_empty() {
    return events.empty();
}

string EventManager::get_json() {
    return EventManager::get_json(false);
}

string EventManager::get_json(bool clear_events) {
    string result = generateJson(events);
    
    if (clear_events)
        EventManager::clear_events();

    return result;
}

void EventManager::clear_events() {
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

    pt.add_child("event", children);

    ostringstream out; 
    write_json(out, pt);
    return out.str();
}
