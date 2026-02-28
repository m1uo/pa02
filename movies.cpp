#include "movies.h"

bool compare(const std::pair<std::string, double>& a,
                   const std::pair<std::string, double>& b) {
    if (a.second != b.second) {
        return a.second > b.second;
    }
    return a.first < b.first;
}
