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

#include "TangibleObject.h"

#include "../../managers/object/ObjectManager.h"
#include "../scene/variables/CustomizationVariables.h"
#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage6.h"

void TangibleObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("TangibleObject");
}

void TangibleObjectImplementation::loadTemplateData(LuaObject* templateData) {
	targetable = templateData->getByteField("targetable");

	complexity = 100.f;

	volume = 1;

	unknownByte = 1;

	objectCount = 0;

	conditionDamage = 0;
	maxCondition = 6000;

	optionsBitmask = 0;
	pvpStatusBitmask = 0;
}

void TangibleObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending tano baselines");

	BaseMessage* tano3 = new TangibleObjectMessage3(_this);
	player->sendMessage(tano3);

	BaseMessage* tano6 = new TangibleObjectMessage6(_this);
	player->sendMessage(tano6);
}

void TangibleObjectImplementation::setDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	setCombatState();

	if (defenderList.size() == 0) {
		addDefender(defender);
		return;
	}

	ManagedReference<SceneObject*> temp = NULL;

	int i = 0;
	for (; i < defenderList.size(); i++) {
		if (defenderList.get(i) == defender) {
			if (i == 0)
				return;

			temp = defenderList.get(0);

			TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6((TangibleObject*) _this);
			dtano6->startUpdate(0x01);

			defenderList.set(0, defender, dtano6, 2);
			defenderList.set(i, temp, dtano6, 0);

			dtano6->close();

			broadcastMessage(dtano6, true);

			break;
		}
	}
}

void TangibleObjectImplementation::addDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	setCombatState();

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defender == defenderList.get(i))
			return;
	}

	//info("adding defender");

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6((TangibleObject*) _this);
	dtano6->startUpdate(0x01);

	defenderList.add(defender, dtano6);

	dtano6->close();

	broadcastMessage(dtano6, true);
}

void TangibleObjectImplementation::removeDefenders() {
	//info("removing all defenders");
	if (defenderList.size() == 0) {
		//info("no defenders in list");
		return;
	}

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6((TangibleObject*) _this);
	dtano6->startUpdate(0x01);

	defenderList.removeAll(dtano6);

	dtano6->close();

	broadcastMessage(dtano6, true);

	//info("removed all defenders");
}

void TangibleObjectImplementation::removeDefender(SceneObject* defender) {
		//info("trying to remove defender");
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender) {
			info("removing defender");

			TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6(_this);

			dtano6->startUpdate(0x01);

			if (defenderList.size() == 1)
				defenderList.removeAll(dtano6);
			else
				defenderList.remove(i, dtano6);

			dtano6->close();

			broadcastMessage(dtano6, true);

			//info("defender found and removed");
			break;
		}
	}

	if (defenderList.size() == 0)
		clearCombatState(false);

	//info("finished removing defender");
}
