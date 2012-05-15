/*
 * LairSpawnGroup.h
 *
 *  Created on: 11/12/2011
 *      Author: victor
 */

#ifndef LAIRSPAWNGROUP_H_
#define LAIRSPAWNGROUP_H_

#include "SpawnGroup.h"
#include "LairSpawn.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

	class LairSpawnGroup : public SpawnGroup {
	protected:
		Vector<Reference<LairSpawn*> > lairList;
		int maxSpawnLimit;

	public:
		LairSpawnGroup(const LairSpawnGroup& sp) : SpawnGroup(sp) {
			lairList = sp.lairList;
			maxSpawnLimit = sp.maxSpawnLimit;
		}

		LairSpawnGroup(const String& name, LuaObject& obj) : SpawnGroup(name, obj) {
			maxSpawnLimit = obj.getIntField("maxSpawnLimit");
			LuaObject lairSpawns = obj.getObjectField("lairSpawns");

			for (int i = 1; i <= lairSpawns.getTableSize(); ++i) {
				lua_rawgeti(lairSpawns.getLuaState(), -1, i);
				LuaObject spawn(lairSpawns.getLuaState());

				if (spawn.isValidTable()) {
					Reference<LairSpawn*> lairSpawn = new LairSpawn();
					lairSpawn->readObject(spawn);

					lairList.add(lairSpawn);
				}

				spawn.pop();
			}

			lairSpawns.pop();
		}

		Vector<Reference<LairSpawn*> >* getLairList() {
			return &lairList;
		}

		int getMaxSpawnLimit() {
			return maxSpawnLimit;
		}
	};

}
}
}
}

using namespace server::zone::managers::creature;


#endif /* LAIRSPAWNGROUP_H_ */
