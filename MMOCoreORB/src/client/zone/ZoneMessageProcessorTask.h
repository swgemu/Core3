/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ZONEMESSAGEPROCESSORTASK_H_
#define ZONEMESSAGEPROCESSORTASK_H_

#include "ZonePacketHandler.h"


class ZoneMessageProcessorTask : public Task {
	Message* message;

	ZonePacketHandler* packetHandler;

public:
	ZoneMessageProcessorTask(Message* msg, ZonePacketHandler* handler) {
		message = msg;

		packetHandler = handler;
	}

	~ZoneMessageProcessorTask() {
		delete message;
		message = NULL;
	}

	void run() {
		try {
			Reference<BaseClient*> client = (BaseClient*) message->getClient();

			if (client->isAvailable())
				packetHandler->handleMessage(message);
		} catch (PacketIndexOutOfBoundsException& e) {
			System::out << e.getMessage();

			/*	StringBuffer str;
					str << "incorrect packet - " << msg->toStringData();
					error(str);*/

			e.printStackTrace();
		} catch (Exception& e) {
			StringBuffer msg;
			msg << e.getMessage();
			//error(msg);

			e.printStackTrace();
		}

		delete message;
		message = NULL;

	}

};

#endif /*LOGINMESSAGEPROCESSORTASK_H_*/
