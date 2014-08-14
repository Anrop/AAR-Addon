#include "common.h"

using namespace std;
using namespace boost::spirit;
using boost::property_tree::ptree;

class EventManager {
public:
    void add_event(const string& data);
    std::string get_json();
    std::string get_json(bool clear_events);
    void clear_events();
    bool is_empty();
private:
    void addEvent(const string& data, std::vector< std::map<std::string,std::string> > &events_);
    std::string generateJson(std::vector< std::map<std::string,std::string> > &events_);
    std::vector< std::map<std::string,std::string> > events; 
};

void EventManager::add_event(const string& data) {
    addEvent(data, events);
}

bool EventManager::is_empty() {
    return events.empty();
}

std::string EventManager::get_json() {
    return EventManager::get_json(false);
}

std::string EventManager::get_json(bool clear_events) {
    std::string result = generateJson(events);
    
    if (clear_events)
        EventManager::clear_events();

    return result;
}

void EventManager::clear_events() {
    events.clear();
}

void EventManager::addEvent(const string& data, std::vector< std::map<std::string,std::string> > &events_) {
    std::string str = data;

    std::map<std::string,std::string> contents;
    std::string::iterator first = str.begin();
    std::string::iterator last  = str.end();

    const bool result = qi::phrase_parse(first,last, 
        *( *(qi::char_-"=")  >> qi::lit("=") >> *(qi::char_-";") >> -qi::lit(";") ),
        ascii::space, contents);                                  

    events_.push_back(contents);
}

std::string EventManager::generateJson(std::vector< std::map<std::string,std::string> > &events_) {
    ptree pt;
    ptree children;

    for(std::vector< std::map<std::string,std::string> >::iterator it = events.begin(); it != events.end(); ++it) {
        std::map<std::string,std::string> event = *it;
        std::map<std::string, std::string>::iterator iter;

        ptree child;
        for (iter = event.begin(); iter != event.end(); ++iter) {
            child.put(iter->first, iter->second);
        }
        children.push_back(std::make_pair("", child));
    }

    pt.add_child("event", children);

    std::ostringstream out; 
    write_json(out, pt);
    return out.str();
}
