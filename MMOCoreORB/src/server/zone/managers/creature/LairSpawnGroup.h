/*
 * LairSpawnGroup.h
 *
 *  Created on: 11/12/2011
 *      Author: victor
 */

#ifndef LAIRSPAWNGROUP_H_
#define LAIRSPAWNGROUP_H_

#include "SpawnGroup.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

	class LairSpawn : public Object {
	protected:
		int spawnLimit;
		int minDifficulty;
		int maxDifficulty;
		int numberToSpawn;
		int weighting;
		int size;

		String lairTemplateName;

	public:
		LairSpawn() : Object() {
			spawnLimit = 0;
			minDifficulty = 0;
			maxDifficulty = 0;
			numberToSpawn = 0;
			weighting = 0;
			size = 0;
		}

		LairSpawn(const LairSpawn& sp) : Object() {
			spawnLimit = sp.spawnLimit;
			minDifficulty = sp.minDifficulty;
			maxDifficulty = sp.maxDifficulty;
			numberToSpawn = sp.numberToSpawn;
			weighting = sp.weighting;
			size = sp.size;

			lairTemplateName = sp.lairTemplateName;
		}

		LairSpawn& operator=(const LairSpawn& sp) {
			if (this == &sp)
				return *this;

			spawnLimit = sp.spawnLimit;
			minDifficulty = sp.minDifficulty;
			maxDifficulty = sp.maxDifficulty;
			numberToSpawn = sp.numberToSpawn;
			weighting = sp.weighting;
			size = sp.size;

			lairTemplateName = sp.lairTemplateName;

			return *this;
		}

		void readObject(LuaObject& obj) {
			spawnLimit = obj.getIntField("spawnLimit");
			minDifficulty = obj.getIntField("minDifficulty");
			maxDifficulty = obj.getIntField("maxDifficulty");
			numberToSpawn = obj.getIntField("numberToSpawn");
			weighting = obj.getIntField("weighting");
			size = obj.getIntField("size");
			lairTemplateName = obj.getStringField("lairTemplateName");
		}

		int getSpawnLimit() {
			return spawnLimit;
		}

		int getMinDifficulty() {
			return minDifficulty;
		}

		int getMaxDifficulty() {
			return maxDifficulty;
		}

		int getNumberToSpawn() {
			return numberToSpawn;
		}

		int getWeighting() {
			return weighting;
		}

		int getSize() {
			return size;
		}

		String getLairTemplateName() {
			return lairTemplateName;
		}

		friend class LairSpawnGroup;
	};

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
