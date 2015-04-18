/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BUFFLIST_H_
#define BUFFLIST_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/buffs/Buff.h"

class BuffList : public Serializable {
protected:
	bool spiceActive;
	VectorMap<uint32, ManagedReference<Buff*> > buffList;
	Mutex mutex;

public:
	BuffList();
	BuffList(const BuffList& bf);

	void sendTo(CreatureObject* player);
	void sendDestroyTo(CreatureObject* player);

	void updateBuffsToDatabase();

	void addBuff(Buff* buff);
	bool removeBuff(uint32 buffcrc);
	void removeBuff(Buff* buff);

	void clearBuffs(bool updateclient);

	int findBuff(Buff* buff);

	String getDurationString(bool showhours = true, bool showminutes = true) const;

	//Getters
	inline int getBuffListSize() const {
		return buffList.size();
	}

	Buff* getBuffByIndex(int index) {
		Locker guard(&mutex);

		if (index < 0 || index >= buffList.size())
			return NULL;

		Buff* buff = buffList.elementAt(index).getValue();

		return buffList.elementAt(index).getValue();
	}

	Buff* getBuffByCRC(uint32 buffcrc) {
		Locker guard(&mutex);

		if (buffList.contains(buffcrc))
			return buffList.get(buffcrc);

		return NULL;
	}

	long long getModifierByName(const String& skillMod) {
		Locker guard(&mutex);

		int mod = 0;

		for (int i = 0; i < buffList.size(); i++) {
			Buff* temp = buffList.get(i);
			mod += temp->getSkillModifierValue(skillMod);
		}

		return mod;
	}

	bool hasBuff(uint32 buffcrc) {
		Locker guard(&mutex);

		return buffList.contains(buffcrc);
	}

	inline bool hasSpice() {
		return spiceActive;
	}
};


#endif /* BUFFLIST_H_ */
