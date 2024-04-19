/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BUFFLIST_H_
#define BUFFLIST_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

#include "server/zone/objects/creature/buffs/Buff.h"

class BuffList : public Serializable {
protected:
	bool spiceActive;
	VectorMap<uint32, ManagedReference<Buff*> > buffList;
	mutable Mutex mutex;

public:
	BuffList();
	BuffList(const BuffList& bf);

	BuffList& operator=(const BuffList& bf);

	void sendTo(CreatureObject* player) const;
	void sendDestroyTo(CreatureObject* player) const;

	void updateBuffsToDatabase();

	void addBuff(Buff* buff);
	bool removeBuff(uint32 buffcrc);
	void removeBuff(Buff* buff);

	void clearBuffs(bool updateclient, bool removeAll);

	int findBuff(Buff* buff) const;

	String getDurationString(bool showhours = true, bool showminutes = true) const;

	friend void to_json(nlohmann::json& j, const BuffList& l);

	//Getters
	inline int getBuffListSize() const {
		return buffList.size();
	}

	Buff* getBuffByIndex(int index) const {
		Locker guard(&mutex);

		if (index < 0 || index >= buffList.size())
			return nullptr;

		Buff* buff = buffList.elementAt(index).getValue();

		return buffList.elementAt(index).getValue();
	}

	Buff* getBuffByCRC(uint32 buffcrc) const {
		Locker guard(&mutex);

		return buffList.get(buffcrc);
	}

	long long getModifierByName(const String& skillMod) const {
		Locker guard(&mutex);

		int mod = 0;

		for (int i = 0; i < buffList.size(); i++) {
			Buff* temp = buffList.get(i);
			mod += temp->getSkillModifierValue(skillMod);
		}

		return mod;
	}

	bool hasBuff(uint32 buffcrc) const {
		Locker guard(&mutex);

		return buffList.contains(buffcrc);
	}

	inline bool hasSpice() const {
		return spiceActive;
	}

	bool hasTrapBuff() const {
		Locker guard(&mutex);

		for (int i = 0; i < buffList.size(); i++) {
			Buff* temp = buffList.get(i);

			if (temp->isTrapBuff()) {
				return true;
			}
		}

		return false;
	}
};


#endif /* BUFFLIST_H_ */
