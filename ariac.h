/*
 (C)Copyright 2012 Adept Technology

     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 If you wish to redistribute ARIA under different terms, contact 
 Adept MobileRobots for information about a commercial version of ARIA at 
 robots@mobilerobots.com or 
 Adept MobileRobots, 10 Columbia Drive, Amherst, NH 03031; +1-603-881-7960
*/

#ifndef _ARIAC_H_
#define _ARIAC_H_

#ifndef ARIA_STATIC
#ifndef AREXPORT
#ifdef WIN32

#define AREXPORT __declspec(dllimport) extern
#else
#define AREXPORT   
#endif
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @mainpage 
ARIAC is a highly simplified C interface (wrapper) to ARIA. It includes
a subset of ArRobot functions for basic connection and control of the robot.

ariac links dynamically to ARIA.  Any program linking to it must also link to
ARIA and dependent libraries:

On Linux, link to libAria, libdl, librt, libm, e.g.:
  gcc -fPIC -o myprog myprog.c -L/usr/local/Aria/lib -lariac -lAria -lpthread -ldl -lrt -lm

On Windows, link to Aria or AriaDebug, ws2_32 and winmm, and include the ARIA
lib directory in the linker path. (Include the ARIA bin directory in system path
or copy DLLs when running the program.)

Once connection is finished, then accessor functions (arrobot_get* and arrobot_set*) may be called from multiple
threads (since they access ARIA in a thread safe way), but connection and
disconnection must happen separately from access. 

*/
    
AREXPORT void arloginfo(const char *m);

AREXPORT void load_aria();
AREXPORT void unload_aria();
AREXPORT void start_arrobot();
AREXPORT void terminate_arrobot();

/** Initialize library, store references to command line arguments if given.
 * Only needs to be called once before any other functions. */
AREXPORT int aria_init(int argc, char **argv);

/** Set a log message handler to call in addition to printing to normal ArLog output destination (which is console/stdout by default) */
AREXPORT void aria_setloghandler(void(*logfn)(const char*));

/** Try connecting to the robot, enable robot motors, then
    start ArRobot's background communications thread.
    Various ARIA objects are created and stored. Call disconnect() or exit() to
    disconnect from the robot and delete stored objects.
    May be called multiple times. If a previous call to connect() resulted
    in a successful connection, then nothing will be done. If there was no
    previous successful connection, try connection (again). May also be called
    after disconnect(), in which case, reconnect to the robot.
    @arg argc Number of command line arguments. Pass 0 if none.
    @arg argv Command line arguments. Pass NULL if none.
    @return 1 If successfully connected, 0 if failed.
*/
AREXPORT int arrobot_connect();

/** Disconnect from robot and clear any saved information. */
AREXPORT void arrobot_disconnect();

/** Block until robot connection is broken (e.g. by robot reset). */
AREXPORT void arrobot_wait();

/** Exit program after quick disconnection from robot and other devices. */
AREXPORT void aria_exit(int code);

AREXPORT double arrobot_getx();
AREXPORT double arrobot_gety();
AREXPORT double arrobot_getth();
AREXPORT double arrobot_getvel();
AREXPORT double arrobot_getrotvel();
AREXPORT double arrobot_getlatvel();
AREXPORT double arrobot_radius();
AREXPORT double arrobot_width();
AREXPORT double arrobot_length();
AREXPORT double arrobot_getleftvel();
AREXPORT double arrobot_getrightvel();
AREXPORT int arrobot_isleftstalled();
AREXPORT int arrobot_isrightstalled();
AREXPORT int arrobot_isstalled();
AREXPORT char arrobot_getdigin();
AREXPORT double arrobot_getsonarrange(int i);
AREXPORT int arrobot_getnumsonar();
#define AR_MAX_NUM_SONAR 16
AREXPORT void arrobot_getsonar(double s[AR_MAX_NUM_SONAR]);
AREXPORT void arrobot_setpose(double x, double y, double th);
AREXPORT void arrobot_stop();
AREXPORT void arrobot_setvel(double vel);
AREXPORT void arrobot_setvel2(double left, double right);
AREXPORT void arrobot_setrotvel(double rotvel);
AREXPORT void arrobot_setlatvel(double vel);
AREXPORT void arrobot_setdeltaheading(double dh);
AREXPORT void arrobot_setdigout(char c);
AREXPORT double arrobot_getbatteryvoltage();
AREXPORT int arrobot_num_front_bumpers();
AREXPORT int arrobot_num_rear_bumpers();
AREXPORT char arrobot_get_front_bumpers();

/** Return 1 if front bumper @arg i is currently pressed */
AREXPORT int arrobot_get_front_bumper(int i);

AREXPORT char arrobot_get_rear_bumpers();

/** Return 1 if front bumper @arg i is currently pressed */
AREXPORT int arrobot_get_rear_bumper(int i);

AREXPORT void arrobot_resetpos();

#ifdef __cplusplus
} // close extern "C"
#endif

#endif
