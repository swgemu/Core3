/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "BuffList.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/object/ObjectManager.h"

BuffList::BuffList() {
	spiceActive = false;

	buffList.setNullValue(NULL);
	buffList.setAllowDuplicateInsertPlan();

	addSerializableVariable("spiceActive", &spiceActive);
	addSerializableVariable("buffList", &buffList);
}

BuffList::BuffList(const BuffList& bf) : Object(), Serializable(), mutex() {
	spiceActive = bf.spiceActive;
	buffList = bf.buffList;

	addSerializableVariable("spiceActive", &spiceActive);
	addSerializableVariable("buffList", &buffList);
}

void BuffList::updateBuffsToDatabase() {
	Locker guard(&mutex);

	for (int i = 0; i < getBuffListSize(); ++i) {
		ManagedReference<Buff*> buff = getBuffByIndex(i);

		if (!buff->isPersistent())
			ObjectManager::instance()->persistObject(buff, 1, "buffs");
		else
			buff->updateToDatabase();
	}
}

void BuffList::sendTo(CreatureObject* player) {
	Locker guard(&mutex);

	for (int i = 0; i < buffList.size(); ++i) {
		Buff* buff = buffList.get(i);

		buff->sendTo(player);
	}
}

void BuffList::sendDestroyTo(CreatureObject* player) {
	Locker guard(&mutex);

	for (int i = 0; i < buffList.size(); ++i) {
		Buff* buff = buffList.get(i);

		buff->sendDestroyTo(player);
	}
}

void BuffList::addBuff(Buff* buff) {
	if (buff == NULL)
		return;

	Locker guard(&mutex);

	ManagedReference<Buff*> ref = buff;

	uint32 buffcrc = buff->getBuffCRC();

	//Remove the old buff if it exists. (Exists checked in removeBuff)
	if ((buff->getBuffType() == BuffType::FOOD && !buff->isAttributeBuff())
			|| (buff->getBuffType() != BuffType::FOOD))
		removeBuff(buffcrc);

	if (!buff->isPersistent())
		ObjectManager::instance()->persistObject(buff, 1, "buffs");

	buffList.put(buffcrc, buff);

	guard.release();

	if (buff->isSpiceBuff())
		spiceActive = true;

	if (!buff->isActive())
		buff->activate();
}

bool BuffList::removeBuff(uint32 buffcrc) {
	Locker guard(&mutex);

	bool ret = false;

	while (buffList.contains(buffcrc)) {
		ret = true;

		ManagedReference<Buff*> buff = buffList.get(buffcrc);

		Locker locker(buff);

		removeBuff(buff);
	}

	return ret;
}

void BuffList::removeBuff(Buff* buff) {
	if (buff == NULL)
		return;

	Locker guard(&mutex);

	ManagedReference<Buff*> ref = buff;

	uint32 buffcrc = buff->getBuffCRC();

	int index = findBuff(buff);

	if (index != -1) {
		if (buff->isSpiceBuff())
			spiceActive = false;

		buff->clearBuffEvent();

		buffList.remove(index);

		mutex.unlock();

		try {
			buff->deactivate();
		} catch (...) {

		}

		if (buff->isPersistent())
			ObjectManager::instance()->destroyObjectFromDatabase(buff->_getObjectID());

		mutex.lock();
	}
}

int BuffList::findBuff(Buff* buff) {
	Locker guard(&mutex);

	uint32 buffCRC = buff->getBuffCRC();

	VectorMapEntry<uint32, ManagedReference<Buff*> > entry(buffCRC);

	int index = buffList.lowerBound(entry);

	if (index < 0)
		return index;

	for (int i = index; i < buffList.size(); ++i) {
		Buff* buffObject = buffList.get(i);

		if (buffObject == buff)
			return i;

		/*uint32 buffObjectCRC = buffObject->getBuffCRC();

		assert(buffObjectCRC == buffCRC);//either we found the buff or its a different buff with the same crc*/
	}

	return -1;
}

void BuffList::clearBuffs(bool updateclient, bool removeAll) {
	Locker guard(&mutex);

	for (int i = buffList.size() -1; i >= 0; i--) {
		ManagedReference<Buff*> buff = buffList.get(i);

		if (!removeAll && !buff->removeOnClearBuffs())
			continue;

		Locker locker(buff);

		buff->clearBuffEvent();

		buffList.remove(i);

		mutex.unlock();

		try {
			//Already null checked the buff.
			if (buff->isSpiceBuff())
				buff->deactivate(false); // this wont create the downer
			else
				buff->deactivate();

			if (buff->isPersistent())
				ObjectManager::instance()->destroyObjectFromDatabase(buff->_getObjectID());
		} catch (...) {

		}

		mutex.lock();
	}

	spiceActive = false;
}
