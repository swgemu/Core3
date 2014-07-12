/*
 * LairSpawn.h
 *
 *  Created on: 11/12/2011
 *      Author: victor
 */

#ifndef LAIRSPAWN_H_
#define LAIRSPAWN_H_

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
		float size;

		String lairTemplateName;

	public:
		LairSpawn() : Object() {
			spawnLimit = -1;
			minDifficulty = 1;
			maxDifficulty = 1;
			numberToSpawn = 0;
			weighting = 1;
			size = 25;
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
			size = obj.getFloatField("size");
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

		float getSize() {
			return size;
		}

		String getLairTemplateName() {
			return lairTemplateName;
		}
	};

}
}
}
}

using namespace server::zone::managers::creature;


#endif /* LAIRSPAWN_H_ */
