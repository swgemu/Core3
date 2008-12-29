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

#include "StatePack.h"
#include "StatePackImplementation.h"

#include "../../../objects.h"

StatePackImplementation::StatePackImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: StatePackServant(oid, tempCRC, n, tempn, STATEPACK) {
	initialize();
}
StatePackImplementation::StatePackImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: StatePackServant(creature, tempCRC, n, tempn, STATEPACK) {

	name = n;
	templateName = tempn;

	initialize();
}

int StatePackImplementation::useObject(Player* player) {
	if (player->getSkillMod("healing_ability") < medicineUseRequired) {
		player->sendSystemMessage("error_message", "insufficient_skill"); //You lack the skill to use this item.
		return 0;
	}

	uint32 actionCRC = 0x4A386BD5; //healstate
	player->queueHeal((TangibleObject*)_this, actionCRC, CreatureState::getName(state));

	return 0;
}

void StatePackImplementation::initialize() {
	setState(CreatureState::INVALID);
}

void StatePackImplementation::parseItemAttributes() {
	PharmaceuticalImplementation::parseItemAttributes();

	String attr = "state";
	setState(itemAttributes->getUnsignedLongAttribute(attr));
}

void StatePackImplementation::addAttributes(AttributeListMessage* alm) {
	PharmaceuticalImplementation::addHeaderAttributes(alm);

	StringBuffer eff;
	eff << "@obj_attr_n:state_type_" << CreatureState::getName(state);
	alm->insertAttribute("examine_heal_state", eff.toString());

	PharmaceuticalImplementation::addFooterAttributes(alm);
}

void StatePackImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}
