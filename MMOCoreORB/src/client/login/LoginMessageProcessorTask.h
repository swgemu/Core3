/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOGINMESSAGEPROCESSORTASK_H_
#define LOGINMESSAGEPROCESSORTASK_H_

#include "engine/engine.h"

#include "LoginPacketHandler.h"


class LoginMessageProcessorTask : public Task {
	Message* message;

	LoginPacketHandler* packetHandler;

public:
	LoginMessageProcessorTask(Message* msg, LoginPacketHandler* handler) {
		message = msg;

		packetHandler = handler;
	}

	~LoginMessageProcessorTask() {
		delete message;
		message = NULL;
	}

	void run() {
		try {
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
