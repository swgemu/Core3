/*
 * LoginMessageProcessorThread.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */


#include "LoginMessageProcessorThread.h"
#include "LoginClient.h"
#include "LoginPacketHandler.h"

LoginMessageProcessorThread::LoginMessageProcessorThread(const String& s, LoginClient* loginClient) : Logger(s), Thread() {
	phandler = new LoginPacketHandler(loginClient->getLoginSession());
	client = loginClient;
}

void LoginMessageProcessorThread::run() {
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
