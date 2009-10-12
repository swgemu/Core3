/*
 * TerminalImplementation.cpp
 *
 *  Created on: 11/08/2009
 *      Author: victor
 */

#include "Terminal.h"

/*
TerminalImplementation::TerminalImplementation(LuaObject* templateData) : TangibleObjectImplementation(templateData) {
	setLoggingName("Terminal");
}
*/

void TerminalImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("Terminal");
}
