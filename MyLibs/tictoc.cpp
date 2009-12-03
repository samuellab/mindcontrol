/* 
 * File:   tictoc.cpp
 * Author: Marc
 * 
 * Created on December 3, 2009, 12:07 PM
 */

#include "tictoc.h"
#include <limits>
#include <map>
#include <ctime>
#include <sstream>
using namespace std;
using namespace TICTOC;

struct TICTOC::_tictoc_data {
    int ncalls;
    time_t starttime;
    time_t totaltime;
    time_t maxtime;
    time_t mintime;
    bool ticked;
    int numblowntics;
};

static _tictoc_data ntt();

_tictoc_data ntt() {
    _tictoc_data tt;
    tt.ncalls = 0;
    tt.starttime = 0;
    tt.totaltime = 0;
    tt.maxtime = 0;
    tt.mintime = UINT_MAX;
    tt.ticked = false;
    tt.numblowntics = 0;
}
tictoc::tictoc() {
}

tictoc::~tictoc() {
}

void tictoc::tic(const string &name, bool notick) {
    if (notick)
        return;
    
    _tictoc_data *td;
    map<string, _tictoc_data>::iterator it;
    it = tt.find(name);
    if (it == tt.end()) {
        _tictoc_data tdtemp = ntt();
        it = tt.insert(tt.begin(), pair<string, _tictoc_data>(name, tdtemp));
    }
    td = &(it->second);
    td->starttime = clock();
    if (td->ticked) {
        ++(td->numblowntics);
    }
    td->ticked = true;
}
void tictoc::tic(const char* name, bool notick) {
    tic (string(name), notick);
}

long tictoc::toc(const string &name, bool notock) {
    if (notock) {
        return 0;
    }
    _tictoc_data *td;
    map<string, _tictoc_data>::iterator it;
    it = tt.find(name);
    if (it == tt.end()) {
        return NOT_FOUND; //key not found
    }
    td = &(it->second);
    if (!td->ticked) {
        return NOT_TICKED; //toc called without tic
    }
    ++(td->ncalls);
    td->ticked = false;
    time_t et = clock() - td->starttime;
    td->maxtime = et > td->maxtime ? et : td->maxtime;
    td->mintime = et < td->mintime ? et : td->mintime;
    td->totaltime += et;
    return et;
}

long tictoc::toc(const char* name, bool notock) {
    return toc(string(name), notock);
}

void tdpToSS (stringstream &s, const pair<string, _tictoc_data> &p) {
    s << "  name: " << p.first << "\n";
    s << "  ncalls: " << p.second.ncalls << "\n";
    s << "  totaltime: " << (1.0 * p.second.totaltime) / CLOCKS_PER_SEC << "\n";
    s << "  maxtime: " << (1.0 * p.second.maxtime) / CLOCKS_PER_SEC << "\n";
    s << "  mintime: " << (1.0 * p.second.mintime) / CLOCKS_PER_SEC << "\n";
    s << "  numblowntics: " << p.second.numblowntics << "\n";
}
void tdpToSS (stringstream &s, const pair<string, _tictoc_data> *p) {
    tdpToSS(s,*p);
}

string tictoc::generateReport() {
    stringstream s;
    map<string, _tictoc_data>::iterator it;
    for (it = tt.begin(); it != tt.end(); ++it) {
        s<<"-\n";
        tdpToSS(s, *it);
        
    }
    return s.str();
}
char *tictoc::generateReportCstr() {
    string s = generateReport();
    char *c = (char *) malloc(s.length() + 1);
    assert (c != NULL);
    strcpy(c, s.c_str());
    return c;
}

void tictoc::clear() {
    tt.clear();
}

