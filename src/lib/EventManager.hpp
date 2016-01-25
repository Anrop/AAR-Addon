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
