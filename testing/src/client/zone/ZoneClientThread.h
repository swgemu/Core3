/*
 * ZoneClientThread.h
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#ifndef ZONECLIENTTHREAD_H_
#define ZONECLIENTTHREAD_H_

#include "engine/engine.h"

class ZoneClient;

class ZoneClientThread : public Thread {
	ZoneClient* client;
public:
	ZoneClientThread(ZoneClient* zoneClient);

	void run();
};


#endif /* ZONECLIENTTHREAD_H_ */
