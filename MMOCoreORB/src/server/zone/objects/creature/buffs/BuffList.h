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

#ifndef BUFFLIST_H_
#define BUFFLIST_H_

#include "engine/engine.h"
#include "Buff.h"

class BuffList : public Serializable {
protected:
	bool spiceActive;
	VectorMap<uint32, ManagedReference<Buff*> > buffList;

public:
	BuffList();
	BuffList(const BuffList& bf);

	void sendTo(CreatureObject* player);
	void sendDestroyTo(CreatureObject* player);

	void updateBuffsToDatabase();

	void addBuff(CreatureObject* creature, Buff* buff);
	bool removeBuff(CreatureObject* creature, uint32 buffcrc);
	void removeBuff(CreatureObject* creature, Buff* buff);

	void clearBuffs(CreatureObject* creature, bool updateclient);

	String getDurationString(bool showhours = true, bool showminutes = true) const;

	//Getters
	inline int getBuffListSize() {
		return buffList.size();
	}

	inline Buff* getBuffByIndex(int index) {
		if (index < 0 || index >= buffList.size())
			return NULL;

		Buff* buff = buffList.elementAt(index).getValue();

		return buffList.elementAt(index).getValue();
	}

	inline Buff* getBuffByCRC(uint32 buffcrc) {
		if (buffList.contains(buffcrc))
			return buffList.get(buffcrc);

		return NULL;
	}

	inline long long getModifierByName(const String& skillMod) {
		int mod = 0;

		for (int i = 0; i < buffList.size(); i++) {
			Buff* temp = buffList.get(i);
			mod += temp->getSkillModifierValue(skillMod);
		}

		return mod;
	}

	inline bool hasBuff(uint32 buffcrc) {
		return buffList.contains(buffcrc);
	}

	inline bool hasSpice() {
		return spiceActive;
	}
};


#endif /* BUFFLIST_H_ */
