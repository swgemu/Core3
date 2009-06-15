/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef QUEUECOMMAND_H_
#define QUEUECOMMAND_H_

#include "../../objects/tangible/creature/player/PlayerObject.h"

class QueueCommand : public DistributedObject {
protected:
	String commandName;
	uint32 commandCRC;
	uint64 invalidStatesMask;
	uint32 invalidPosturesMask;
	uint32 range;

public:
	QueueCommand(const String& name) {
		commandName = name;
		commandCRC = name.hashCode();
		invalidStatesMask = 0;
		invalidPosturesMask = 0;
		range = 128;
	}

	~QueueCommand() {

	}

	virtual bool execute(PlayerObject* player, uint32 actioncounter, uint64 targetid, const String& args) {
		return false;
	}

	//Setters
	inline void setCommandName(const String& name) {
		commandName = name;
		commandCRC = name.hashCode();
	}

	inline void setInvalidStatesMask(uint64 mask) {
		invalidStatesMask = mask;
	}

	inline void setInvalidPosturesMask(uint32 mask) {
		invalidPosturesMask = mask;
	}

	inline void setRange(uint32 rng) {
		range = rng;
	}

	//Getters
	inline String& getCommandName() {
		return commandName;
	}

	inline uint32 getCommandCRC() {
		return commandCRC;
	}

	inline uint64 getInvalidStatesMask() {
		return invalidStatesMask;
	}

	inline uint32 getInvalidPosturesMask() {
		return invalidPosturesMask;
	}

	inline uint32 getRange() {
		return range;
	}
};

#endif /* QUEUECOMMAND_H_ */
