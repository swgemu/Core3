/*
 * TerminalImplementation.cpp
 *
 *  Created on: 11/08/2009
 *      Author: victor
 */

#include "server/zone/objects/tangible/terminal/Terminal.h"

void TerminalImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("Terminal");
}
