/*
 * LoginSession.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "LoginClient.h"
#include "LoginClientThread.h"

#include "server/login/packets/AccountVersionMessage.h"

#include "LoginSession.h"

#include "ClientCore.h"

LoginSession::LoginSession(const String& username, const String& password) : Logger("LoginSession") {
	LoginSession::username = username;
	LoginSession::password = password;

	loginThread = nullptr;

	accountID = 0;
	sessionID = "";
	lastError = "";
	lastErrorCode = 0;
	loginStartTime.updateToCurrentTime();
	setLogLevel(static_cast<Logger::LogLevel>(ClientCore::getLogLevel()));
}

LoginSession::~LoginSession() {
	if (login != nullptr) {
		login->disconnect();
	}
}

void LoginSession::run() {
	// Load config properties
	Core::initializeProperties("Client3");

	String loginHost = ClientCore::getLoginHost();
	int loginPort = ClientCore::getLoginPort();

	info(true) << "Creating login client...";
	login = new LoginClient(loginHost, loginPort);
	login->setLoginSession(this);
	login->initialize();

	info(true) << "Starting login thread...";
	loginThread = new LoginClientThread(login);
	loginThread->start();

	info(true) << "Attempting to connect to " << loginHost << ":" << loginPort << "...";
	if (!login->connect()) {
		info(true) << "ERROR: Could not connect to login server at " << loginHost << ":" << loginPort;
		info(true) << "Make sure the login server is running on port " << loginPort;
		return;
	}

	info(true) << "Connected to login server";

	info(true) << "Creating AccountVersionMessage...";
	String clientVersion = ClientCore::getClientVersion();
	BaseMessage* acc = new AccountVersionMessage(username, password, clientVersion);

	info(true) << "Sending login request...";
	login->sendMessage(acc);

	info(true) << "Waiting for response...";

	// Wait for packets to be processed by the packet handler
	lock();
	Time timeout;
	timeout.addMiliTime(ClientCore::getLoginTimeout() * 1000);
	bool timedOut = !sessionFinalized.timedWait(this, &timeout);
	unlock();

	if (timedOut) {
		setError("Login timeout waiting for server response", 1);
		info(true) << "Login process timed out.";
	} else if (accountID == 0) {
		setError("Login failed - no account ID received", 2);
		info(true) << "Login process failed.";
	} else {
		info(true) << "Login process completed successfully.";
	}
}

void LoginSession::cleanup() {
	info(true) << "Cleaning up login session...";

	if (login != nullptr) {
		login->disconnect();
	}

	if (loginThread != nullptr) {
		loginThread->stop();

		Socket* socket = login->getClient()->getSocket();
		if (socket != nullptr) {
			socket->shutdown(SHUT_RDWR);
			socket->close();
		}

		loginThread = nullptr;
	}

	info(true) << "Login session cleanup complete.";
}

void LoginSession::sendMessage(BaseMessage* msg) {
	if (login != nullptr) {
		login->sendMessage(msg);
	}
}

JSONSerializationType LoginSession::collectStats() {
	JSONSerializationType stats;
	stats["elapsedMs"] = loginStartTime.miliDifference();
	stats["packetCount"] = login != nullptr ? login->getPacketCount() : 0;
	stats["success"] = (accountID != 0);
	stats["username"] = username.toCharArray();
	return stats;
}
