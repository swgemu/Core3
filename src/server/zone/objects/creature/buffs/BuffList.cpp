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

#include "BuffList.h"
#include "../CreatureObject.h"
#include "../../player/PlayerCreature.h"
#include "server/zone/managers/object/ObjectManager.h"

BuffList::BuffList() {
	spiceActive = false;

	buffList.setNullValue(NULL);
	buffList.setAllowDuplicateInsertPlan();

	addSerializableVariable("spiceActive", &spiceActive);
	addSerializableVariable("buffList", &buffList);
}

BuffList::BuffList(const BuffList& bf) : Object(), Serializable() {
	spiceActive = bf.spiceActive;
	buffList = bf.buffList;

	removedBuffs = bf.removedBuffs;

	addSerializableVariable("spiceActive", &spiceActive);
	addSerializableVariable("buffList", &buffList);
}

void BuffList::updateBuffsToDatabase() {
	for (int i = 0; i < getBuffListSize(); ++i) {
		ManagedReference<Buff*> buff = getBuffByIndex(i);

		if (!buff->isPersistent())
			ObjectManager::instance()->persistObject(buff, 1, "buffs");
		else
			buff->updateToDatabase();
	}

	/*for (int i = 0; i < removedBuffs.size(); ++i) {
		ManagedReference<Buff*> buff = removedBuffs.get(i);

		if (buff->isPersistent())
			ObjectManager::instance()->destroyObjectFromDatabase(buff->_getObjectID());
	}*/

	removedBuffs.removeAll();
}

void BuffList::sendTo(PlayerCreature* player) {
	for (int i = 0; i < buffList.size(); ++i) {
		Buff* buff = buffList.get(i);

		buff->sendTo(player);
	}
}

void BuffList::sendDestroyTo(PlayerCreature* player) {
	for (int i = 0; i < buffList.size(); ++i) {
		Buff* buff = buffList.get(i);

		buff->sendDestroyTo(player);
	}
}

void BuffList::addBuff(CreatureObject* creature, Buff* buff) {
	if (buff == NULL)
		return;

	ManagedReference<Buff*> ref = buff;

	uint32 buffcrc = buff->getBuffCRC();

	//Remove the old buff if it exists. (Exists checked in removeBuff)
	if ((buff->getBuffType() == BuffType::FOOD) && !buff->isAttributeBuff()
			|| (buff->getBuffType() != BuffType::FOOD))
		removeBuff(creature, buffcrc);

	if (!buff->isPersistent())
		ObjectManager::instance()->persistObject(buff, 1, "buffs");

	buffList.put(buffcrc, buff);

	if (buff->isSpiceBuff())
		spiceActive = true;

	if (!buff->isActive())
		buff->activate();
}

void BuffList::removeBuff(CreatureObject* creature, uint32 buffcrc) {
	ManagedReference<Buff*> buff = buffList.get(buffcrc);

	if (buff == NULL)
		return;

	removeBuff(creature, buff);
}

void BuffList::removeBuff(CreatureObject* creature, Buff* buff) {
	if (buff == NULL)
		return;

	ManagedReference<Buff*> ref = buff;

	uint32 buffcrc = buff->getBuffCRC();

	if (buffList.contains(buffcrc)) {
		//This only gets called if the event has been scheduled and is not executing.
		if (buff->isActive())
			buff->clearBuffEvent();

		if (buff->isSpiceBuff())
			spiceActive = false;

		buff->clearBuffEvent();

		removedBuffs.add(buff);

		buffList.drop(buffcrc);

		//Already null checked the buff.
		buff->deactivate();
	}
}

void BuffList::clearBuffs(CreatureObject* creature, bool updateclient) {
	for (int i = 0; i < buffList.size(); ++i) {
		ManagedReference<Buff*> buff = buffList.get(i);

		if (buff != NULL) {
			if (buff->isActive()) {
				//This can only get called if the buff event is scheduled and not currently being executed.
				buff->clearBuffEvent();
				buff->deactivate();

				removedBuffs.add(buff);
			}

		}
	}

	spiceActive = false;
	buffList.removeAll();
}
