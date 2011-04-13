/*
 * LoginClientThread.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef LOGINCLIENTTHREAD_H_
#define LOGINCLIENTTHREAD_H_

#include "engine/engine.h"

#include "LoginClient.h"

class LoginClientThread : public Thread {
	LoginClient* client;

public:
	LoginClientThread(LoginClient* client) {
		LoginClientThread::client = client;
	}

	void run() {
		client->recieveMessages();
	}
};


#endif /* LOGINCLIENTTHREAD_H_ */
