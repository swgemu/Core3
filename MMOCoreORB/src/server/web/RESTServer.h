/**
 * @author      : theanswer (theanswer@Victors-MacBook-Pro.local)
 * @file        : RESTServer
 * @created     : Sunday Nov 11, 2018 11:27:17 CET
 */

#pragma once

#include "engine/engine.h"
#include "system/thread/atomic/AtomicBoolean.h"

namespace server {
 namespace web3 {

 class RESTServer {
 protected:
	AtomicBoolean doRun;
	const uint16 port;

 public:
	const static Logger logger;

	RESTServer(uint16 port);
	~RESTServer();

	void start();

	void stop();
};

}
}
