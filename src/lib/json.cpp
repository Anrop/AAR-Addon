#include "common.h"

using namespace std;
using namespace boost::spirit;
using boost::property_tree::ptree;


/*
    for(std::vector< std::map<std::string,std::string> >::iterator it = events.begin(); it != events.end(); ++it) {
        std::map<std::string,std::string> event = *it;
        std::map<std::string, std::string>::iterator iter;

        cout << "EVENT" << endl << "-----------------------------------------------" << endl;

        for (iter = event.begin(); iter != event.end(); ++iter) {
            cout << iter->first << " = " << iter->second << endl;
        }

        cout << "-----------------------------------------------" << endl;
    }
*/
//std::vector< std::map<std::string,std::string> > events;

/* Todo make thread safe with a mutex */
class EventManager {
public:
    void add_event(const string& data);
    std::string get_json();
    std::string get_json(bool clear_events);
    void clear_events();
private:
    void addEvent(const string& data, std::vector< std::map<std::string,std::string> > &events_);
    std::string generateJson(std::vector< std::map<std::string,std::string> > &events_);
    std::vector< std::map<std::string,std::string> > events; 
};

void EventManager::add_event(const string& data) {
    addEvent(data, events);
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

void testJson() {
    /*
        [
            ["type", "player_connected"],
            ["timestamp", "0"],
            ["id", "1000"],
            ["name", "xealot"],
            ["pid", "player-id"]
        ],
        [
            ["type", "player_connected"],
            ["timestamp", "1"],
            ["id", "1001"],
            ["name", "yolo"],
            ["pid", "player-id"]
        ],
        [
            ["type", "player_connected"],
            ["timestamp", "2"],
            ["id", "1002"],
            ["name", "bolo"],
            ["pid", "player-id"]
        ]

        [["type","player_connected"],["timestamp","0"],["id","1000"],["name","xealot"],["pid","player-id"]],[["type","player_connected"],["timestamp","1"],["id","1001"],["name","yolo"],["pid","player-id"]],[["type","player_connected"],["timestamp","2"],["id","1002"],["name","bolo"],["pid","player-id"]]
    */

    ptree pt;
    ptree children;
    //ptree child1, child2, child3;

    for (int i=0; i < 5; i++) {
        ptree child;

        child.put("type", "player_connected");
        child.put("timestamp", "0");
        child.put("id", "uid-1000");
        child.put("name", "xealot");
        child.put("pid", "player-id");

        children.push_back(std::make_pair("", child));
    }

    /*
    child1.put("childkeyA", 1);
    child1.put("childkeyB", 2);

    child2.put("childkeyA", 3);
    child2.put("childkeyB", 4);

    child3.put("childkeyA", 5);
    child3.put("childkeyB", 6);

    children.push_back(std::make_pair("", child1));
    children.push_back(std::make_pair("", child2));
    children.push_back(std::make_pair("", child3));
    */

    //pt.put("testkey", "testvalue");
    pt.add_child("event", children);

    std::ostringstream out; 
    write_json(out, pt);
    cout << out.str() << endl;
}