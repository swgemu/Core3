/*
 * LoginSession.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "LoginClient.h"
#include "LoginClientThread.h"

#include "../../server/login/packets/AccountVersionMessage.h"

#include "LoginSession.h"

LoginSession::LoginSession(int instance) : Logger("LoginSession" + String::valueOf(instance)) {
	selectedCharacter = -1;
	LoginSession::instance = instance;

	loginThread = NULL;

	accountID = 0;
	sessionID = 0;
	setLogging(false);
}

LoginSession::~LoginSession() {
	if (loginThread != NULL)
		loginThread->stop();
}

int accountSuffix = 0;

void LoginSession::run() {
	Reference<LoginClient*> login = new LoginClient(44453, "LoginClient" + String::valueOf(instance));
	login->setLoginSession(this);
	login->initialize();

	loginThread = new LoginClientThread(login);
	loginThread->start();

	if (!login->connect()) {
		error("could not connect to login server");
		return;
	}

	info("connected to login server");

#ifdef WITH_STM
	TransactionalMemoryManager::commitPureTransaction();
#endif

	char userinput[32];
	char passwordinput[32];

	info("insert user");
	/*fgets(userinput, sizeof(userinput), stdin);

	info("insert password", true);
	fgets(passwordinput, sizeof(passwordinput), stdin);

	String user, password;
	user = userinput;
	user = user.replaceFirst("\n", "");

	password = passwordinput;
	password = password.replaceFirst("\n", "");*/

	//BaseMessage* acc = new AccountVersionMessage(user, password, "20050408-18:00");
	BaseMessage* acc = new AccountVersionMessage("Akimaki" + String::valueOf(accountSuffix++), "4823848", "20050408-18:00");
	login->sendMessage(acc);

	info("sent account version message");

	lock();

	Time timeout;
	timeout.addMiliTime(2000);

	sessionFinalized.timedWait(this, &timeout);

	unlock();

	login->disconnect();
}
