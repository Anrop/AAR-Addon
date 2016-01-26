#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class EventManager {
public:
    void addEvent(const string& data);
    string getJson();
    void clearEvents();
    bool isEmpty();
    int count();
private:
    json events; 
};
