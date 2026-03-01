// Winter'24
// Instructor: Diba Mirza
// Student name: Max Luo and George Tsirigotis
#include <iostream>
#include <fstream>
// #include <map>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <limits>
// #include <iomanip>
// #include <set>
// #include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
    vector<pair<string, double>> movies;

    

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
            movies.push_back(make_pair(movieName, movieRating));
        
    }

    sort(movies.begin(), movies.end());

    movieFile.close();

    if (argc == 2){
            for (const auto& [name, rating] : movies) {
                cout << name << ", " << rating << '\n';
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
    for (const string& pre : prefixes) {
        auto it = lower_bound(movies.begin(), movies.end(), make_pair(pre, -1.0));
        vector<pair<string, double>> matches;
        while (it != movies.end() && it->first.compare(0, pre.size(), pre) == 0) {
            matches.push_back(*it);
            ++it;
        }

        if (matches.empty()) {
            cout << "No movies found with prefix " << pre << '\n';
            continue;
        }

        sort(matches.begin(), matches.end(), compare);

        std::ostringstream oss;
        oss << "Best movie with prefix " << pre << " is: " << matches[0].first
            << " with rating " << matches[0].second;
        v.push_back(oss.str());

        for (const auto& [name, rating] : matches) {
            cout << name << ", " << rating << '\n';
        }
        cout << '\n';
    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    // cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;
    for (string s : v) {
        cout << s << '\n';
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*
    Define:
    n as number of movies
    m as number of prefixes
    k as maximum # of matches for a prefix

    3a)
    Time Complexity
        For each prefix:
        finding the range of titles is O(log n) Note: in absolute worst case, this 
            can be but most movie names are short and not too similar (l log n)
        scanning movies is O(k)
        sorting movies is O(k log k)

        There are m prefixes
        So the total time complexity is O(m(log n + k log k))
        * or O(m(l log n + k log k)) for worst case.
    Timing:

    bash time.sh
        === input_20_random.csv ===
        avg_real_ms 6.471327

        === input_100_random.csv ===
        avg_real_ms 6.667678

        === input_1000_random.csv ===
        avg_real_ms 7.713657

        === input_76920_random.csv ===
        avg_real_ms 86.216202

        [maxluo@csilvm-08 pa02]$ bash time.sh
        === input_20_random.csv ===
        avg_real_ms 6.083347

        === input_100_random.csv ===
        avg_real_ms 6.229739

        === input_1000_random.csv ===
        avg_real_ms 7.742026

        === input_76920_random.csv ===
        avg_real_ms 86.012183

    3b)
    Space Complexity
        The vector of movies is O(n), but not part of auxiliary space
        The vector of prefixes is O(m), but not part of auxiliary space
        The vector v (printing list) os O(m * l)
        The match list is O(k * l)

        So the total space complexity is O(l(k+m))
    
    3c)
    Space/time complexity tradeoffs.
    
    Did you design your algorithm for a low time complexity, a low space complexity, or both? What were your target complexities?
    We designed our algorithm to have reasonable time and space complexity. We did not have a target 
    complexity in mind at first, but just tried to make smart choices in our algorithm that does not 
    increase complexity unnecessarily. In the end, I believe our algorithm was more optimized for space, 
    notably when comapred to a trie approach.

    If you designed your algorithm for a low space complexity,
    Were you able to achieve a low time complexity as well?
    Why or why not?
        We were able to get our algorithm to run relatively fast with decent time complexity, but it is 
        still much slower than storing a prefix tree. However storing the prefix tree would require 
        higher space complexity. In the end, it is a tradeoff; we cannot have the excellent time 
        complexity of a prefix tree without dealing with the space taken by one. 
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
