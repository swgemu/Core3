/*
 * LoginProcessServerImplementation.cpp
 *
 *  Created on: Oct 13, 2010
 *      Author: crush
 */

#include "engine/engine.h"
#include "LoginServer.h"
#include "LoginPacketHandler.h"
#include "LoginMessageProcessorThread.h"
#include "LoginProcessServerImplementation.h"

LoginProcessServerImplementation* LoginProcessServerImplementation::instance = NULL;

LoginProcessServerImplementation::LoginProcessServerImplementation(LoginServer* serv, int processingThreads)
		: ServiceMessageHandlerThread("LoginProcessorServer") {

	server = serv;

	processors = NULL;
	procThreadCount = processingThreads;

	loginphandler = NULL;

	instance = this;

	setLogging(false);
}

LoginProcessServerImplementation::~LoginProcessServerImplementation() {
	if (processors != NULL) {
		free(processors);
		processors = NULL;
	}

	if (loginphandler != NULL) {
		delete loginphandler;
		loginphandler = NULL;
	}
}

void LoginProcessServerImplementation::init() {
	loginphandler = new LoginPacketHandler("LoginPacketHandler", this);
	loginphandler->setLogging(false);

	if (procThreadCount < 1)
		throw new Exception("invalid login processor thread count");

	processors = (LoginMessageProcessorThread**) malloc(procThreadCount * sizeof(LoginMessageProcessorThread*));

	for (int i = 0; i < procThreadCount; ++i) {
		StringBuffer name;
		name << "LoginProcessor" << i;

		processors[i] = new LoginMessageProcessorThread(name.toString(), loginphandler);
	}
}

void LoginProcessServerImplementation::run() {
	info("starting processor instances..");

	for (int i = 0; i < procThreadCount; ++i) {
		LoginMessageProcessorThread* processor = processors[i];
		processor->start(this);
	}

	info("processor instances started");
}

void LoginProcessServerImplementation::stop() {
	flushMessages();

	info("stopping processor instances..");

	for (int i = 0; i < procThreadCount; ++i) {
		LoginMessageProcessorThread* processor = processors[i];
		processor->stop();

		delete processor;
	}

	info("processor instances stopped");
}
