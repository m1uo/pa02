// Winter'24
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
#include <functional>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    map<string, double> mp;

    

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
            mp[movieName] = movieRating;
        
    }

    movieFile.close();

    if (argc == 2){
            for (const auto& [name, rating] : mp) {
                cout << name << ", " << rating << endl;
            }
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    // cout << "No movies found with prefix "<<"<replace with prefix>" << endl;
    vector<string> v;
    for (string pre : prefixes) {
        map<double, set<string>> pre_mp;
        bool inRange = false;
        for (const auto& [name, rating] : mp) {
            if (name.find(pre) == 0) {
                pre_mp[rating].insert(name);
                inRange = true;
            }
            else if (inRange) {
                break;
            }
        }
        if (!inRange) {
            cout << "No movies found with prefix "<< pre << endl;
            continue;
        }
        bool first = true;
        for (const auto& [rating,names] : pre_mp) {
            for (string name: names) {
                if (first) {
                    std::ostringstream oss;
                    oss << "Best movie with prefix " << pre << " is: " << name << " with rating " << rating;
                    v.push_back(oss.str());
                    first = false;
                }
                cout << name << ", " << rating << endl;
            }
        }
        cout << endl;
    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    // cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;
    for (string s : v) {
        cout << s << endl;
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}