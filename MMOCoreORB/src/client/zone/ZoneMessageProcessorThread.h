/*
 * ZoneMessageProcessorThread.h
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#ifndef ZONEMESSAGEPROCESSORTHREAD_H_
#define ZONEMESSAGEPROCESSORTHREAD_H_

#include "engine/engine.h"

#include "ZonePacketHandler.h"
class ZoneClient;

class ZoneMessageProcessorThread : public Logger, public Thread {
	ZonePacketHandler* phandler;
	ZoneClient* client;

public:
	ZoneMessageProcessorThread(const String& s, ZoneClient* zoneClient);

	void run();
};


#endif /* ZONEMESSAGEPROCESSORTHREAD_H_ */
