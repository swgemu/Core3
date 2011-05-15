/*
 * ZoneClientThread.cpp
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#include "ZoneClientThread.h"
#include "ZoneClient.h"

ZoneClientThread::ZoneClientThread(ZoneClient* zoneClient) : Thread() {
	client = zoneClient;

	setDetached();
}

ZoneClientThread::~ZoneClientThread() {
	client = NULL;
}

void ZoneClientThread::run() {
	client->getClient()->recieveMessages();
}

void ZoneClientThread::stop() {
	client->getClient()->stop();
}
