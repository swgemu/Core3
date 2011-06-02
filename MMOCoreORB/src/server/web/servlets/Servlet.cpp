/*
 * WebComponent.cpp
 *
 *  Created on: May 31, 2011
 *      Author: kyle
 */

#include "../WebServer.h"
#include "Servlet.h"

Servlet::Servlet(String context) {

	setLogging(true);
	setLoggingName("Webserver:" + context);

	if(!WebServer::instance()->addContext(context, this)) {
		error("Context already exists");
	}
}

Servlet::~Servlet() {
	// TODO Auto-generated destructor stub
}
