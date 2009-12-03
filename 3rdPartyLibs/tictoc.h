/* 
 * File:   tictoc.h
 * Author: Marc
 *
 * Created on December 3, 2009, 12:07 PM
 */

#ifndef _TICTOC_H
#define	_TICTOC_H

/* macros to make it easy to track a function execution time
 * just put _TICTOC_TIC_FUNC at the beginning of the function call
 * and put _TICTOC_TOC_FUNC right before any return statement
 */
#define _TICTOC_TIC_FUNC TICTOC::timer.tic(__func__);
#define _TICTOC_TOC_FUNC TICTOC::timer.toc(__func__);

#include <map>
#include <cstring>
class Timer;

namespace TICTOC {
    class tictoc {
    public:
        /* error return values for toc command
         * NOT_FOUND == you called toc on "name" without ever calling tic on "name" first
         * NOT_TICKED == although you called tic on "name", you called toc on "name" twice in a row
         */
        static const int NOT_FOUND = -1;
        static const int NOT_TICKED = -2;
        static const double TICKS_PER_SEC = 1E6;
        /* tictoc()
         * ~tictoc()
         * constructor takes no arguments
         */
        tictoc();
        virtual ~tictoc();

        /* clear()
         *
         * resets tictoc to original state, clearing all information about previously
         * called tics and tocs
         */
        void clear();

        /* void tic (const string &name, bool notick = false);
         * void tic (const char *name, bool notick = false);
         *
         * calling tic starts a timer running associated with "name" (case sensitive)
         * when toc("name") is called, you get the number of clock cycles (usually ms) since
         * tic("name") was last called
         *
         * if tic is called twice in a row without a toc, we reset the starting timer
         * generateReport will note the number of times this happens in the field "numblowntics"
         * 
         */
        void tic (const std::string &name, bool notick = false);
        void tic (const char *name, bool notick = false);

        /* long toc(const string &name, bool notock = false);
         * long toc(const char *name, bool notock = false);         *
         *
         * when toc("name") is called, we stop the timer associated with "name"
         * and return the number of clock cycles (usually ms) since tic("name") was called
         * you can convert to seconds using CLOCKS_PER_SEC
         *
         * if toc("name") is called prior to tic("name"), return value will be NOT_FOUND
         * if tic("name") is called but then toc("name") is called two or more times in succession,
         * return value will be NOT_TICKED
         */

        double toc(const std::string &name, bool notock = false);
        double toc(const char *name, bool notock = false);

        std::string generateReport();
        char *generateReportCstr();

    private:
        double clock();

        tictoc(const tictoc& orig);
        std::map <std::string, struct _tictoc_data> tt;
        Timer *tim;
    };

    /* static tictoc timer
     * 
     * we declare a globally accessible static instance of tictoc
     * TICTOC::timer for convenience.  This way, you can call tic and toc from 
     * multiple libraries and have all the data retained in a single structure
     * without having to pass a pointer to a tictoc object around
     */

    static tictoc timer;
}

#endif	/* _TICTOC_H */

