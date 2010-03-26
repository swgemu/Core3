/*
 * LoginMessageProcessorThread.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef LOGINMESSAGEPROCESSORTHREAD_H_
#define LOGINMESSAGEPROCESSORTHREAD_H_

#include "engine/engine.h"

class LoginClient;
class LoginPacketHandler;

class LoginMessageProcessorThread : public Logger, public Thread {
	LoginPacketHandler* phandler;
	LoginClient* client;

public:
	LoginMessageProcessorThread(const String& s, LoginClient* loginClient);

	void run();
};



#endif /* LOGINMESSAGEPROCESSORTHREAD_H_ */
