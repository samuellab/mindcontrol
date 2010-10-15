/*
 * Copyright 2010 Andrew Leifer et al <leifer@fas.harvard.edu>
 * This file is part of MindControl.
 *
 * MindControl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU  General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MindControl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MindControl. If not, see <http://www.gnu.org/licenses/>.
 *
 * For the most up to date version of this software, see:
 * http://github.com/samuellab/mindcontrol
 *
 *
 *
 * NOTE: If you use any portion of this code in your research, kindly cite:
 * Leifer, A.M., Fang-Yen, C., Gershow, M., Alkema, M., and Samuel A. D.T.,
 * 	"Optogenetic manipulation of neural activity with high spatial resolution in
 *	freely moving Caenorhabditis elegans," Nature Methods, Submitted (2010).
 */


/* 
 * File:   tictoc.cpp
 * Author: Marc
 * 
 * Created on December 3, 2009, 12:07 PM
 */

#include "tictoc.h"
#include <limits>
#include <map>
#include <sstream>
#include "Timer.h"

using namespace std;
using namespace TICTOC;

tictoc::tictoc() {
    tim = new Timer();
    tim->start();
    enabled = true;
}
tictoc::~tictoc() {
    delete tim;
}

struct TICTOC::_tictoc_data {
    int ncalls;
    double starttime;
    double totaltime;
    double maxtime;
    double mintime;
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
    tt.mintime = INT_MAX;
    tt.ticked = false;
    tt.numblowntics = 0;
    return tt;
}




void tictoc::tic(const string &name, bool notick) {
    if (!enabled || notick)
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

double tictoc::toc(const string &name, bool notock) {
    if (!enabled || notock) {
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
    double et = clock() - td->starttime;
    td->maxtime = et > td->maxtime ? et : td->maxtime;
    td->mintime = et < td->mintime ? et : td->mintime;
    td->totaltime += et;
    return et;
}

double tictoc::toc(const char* name, bool notock) {
    return toc(string(name), notock);
}

void tdpToSS (stringstream &s, const pair<string, _tictoc_data> &p) {
    s << "  name: " << p.first << "\n";
    s << "  ncalls: " << p.second.ncalls << "\n";
    s << "  totaltime: " << (1.0 * p.second.totaltime) / tictoc::TICKS_PER_SEC << "\n";
    s << "  maxtime: " << (1.0 * p.second.maxtime) / tictoc::TICKS_PER_SEC << "\n";
    s << "  mintime: " << (1.0 * p.second.mintime) / tictoc::TICKS_PER_SEC << "\n";
    s << "  avg time: " << (1.0 * p.second.totaltime) / (p.second.ncalls *tictoc::TICKS_PER_SEC) << "\n";
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

double tictoc::clock() {
    return tim->getElapsedTimeInMicroSec();
}

void tictoc::clear() {
    tt.clear();
}

tictoc &TICTOC::timer() {
    static tictoc t;
    return t;
}

