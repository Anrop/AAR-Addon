#include "Utils.hpp"

void Utils::unquoteArmaString(std::string *s) {
    if (s->size() > 0) {
        if (s->front() == '"')
            s->erase(0, 1);
    }

    if (s->size() > 0) {
        if (s->back() == '"') {
            s->erase(s->size() - 1);
        }
    }
        
    if (s->size() > 0) {
        bool lastQuote = false;
        for (std::string::iterator it = s->begin(); it != s->end(); it++) {
            if (*it == '"') {
                if (!lastQuote) {
                    lastQuote = true;
                } else {
                    s->erase(it);
                    it--;
                    lastQuote = false;
                }
            } else {
                lastQuote = false;
            }
        }
    }
};
