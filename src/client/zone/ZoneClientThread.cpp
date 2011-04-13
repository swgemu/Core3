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
}

void ZoneClientThread::run() {
	client->recieveMessages();
}
