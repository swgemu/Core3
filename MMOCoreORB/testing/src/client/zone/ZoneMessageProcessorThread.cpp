/*
 * ZoneMessageProcessorThread.cpp
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#include "ZoneMessageProcessorThread.h"
#include "ZoneClient.h"

ZoneMessageProcessorThread::ZoneMessageProcessorThread(const String& s, ZoneClient* zoneClient) : Logger(s), Thread() {
	phandler = new ZonePacketHandler("ZonePacketHandler", zoneClient->getZone());
	client = zoneClient;
}

void ZoneMessageProcessorThread::run() {
	Message* msg;

	while ((msg = client->getMessage()) != NULL) {
		//ServerCore::workLock.lock();
		//info("processing login message");

		try {
			phandler->handleMessage(msg);
		} catch (PacketIndexOutOfBoundsException& e) {
			System::out << e.getMessage();

			StringBuffer str;
			str << "incorrect packet - " << msg->toStringData();
			error(str);

			e.printStackTrace();
		} catch (DatabaseException& e) {
			StringBuffer msg;
			msg << e.getMessage();
			error(msg);

			e.printStackTrace();
		} catch (ArrayIndexOutOfBoundsException& e) {
			StringBuffer msg;
			msg << e.getMessage();
			error(msg);

			e.printStackTrace();
		} catch (...) {
			System::out << "[LoginMessageProcessor] unreported Exception caught\n";
		}

		//info("finished processing login message");
		//ServerCore::workLock.unlock();
		delete msg;
	}

	//server->flushMessages();
}
