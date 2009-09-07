/*
 * LoginSession.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "LoginSession.h"

#include "LoginClient.h"
#include "LoginClientThread.h"

#include "LoginMessageProcessorThread.h"

#include "../../server/login/packets/AccountVersionMessage.h"


LoginSession::LoginSession(int instance) : Logger("LoginSession" + String::valueOf(instance)) {
	selectedCharacter = -1;
	LoginSession::instance = instance;

	accountID = 0;
}

void LoginSession::run() {
	LoginClient* login = new LoginClient("127.0.0.1", 44453);
	login->setLoginSession(this);
	login->initialize();
	login->setLoggingName("LoginClient" + String::valueOf(instance));

	LoginClientThread* loginThread = new LoginClientThread(login);
	loginThread->start();

	LoginMessageProcessorThread* messageProcessor = new LoginMessageProcessorThread("LoginMessageProcessor", login);
	messageProcessor->start();

	if (!login->connect()) {
		error("could not connect to login server");
		exit(1);
		return;
	}

	info("connected to login server", true);

	char userinput[32];
	char passwordinput[32];

	info("insert user", true);
	fgets(userinput, sizeof(userinput), stdin);

	info("insert password", true);
	fgets(passwordinput, sizeof(passwordinput), stdin);

	String user, password;
	user = userinput;
	user = user.replaceFirst("\n", "");

	password = passwordinput;
	password = password.replaceFirst("\n", "");

	BaseMessage* acc = new AccountVersionMessage(user, password, "20050408-18:00");
	login->sendMessage(acc);

	info("sent account version message", true);

	lock();

	sessionFinalized.wait(this);

	unlock();
}
