
#ifndef DESTROYMISSIONSPAWNGROUP_H_
#define DESTROYMISSIONSPAWNGROUP_H_

#include "server/zone/managers/creature/SpawnGroup.h"
#include "server/zone/managers/creature/LairSpawn.h"

namespace server {
namespace zone {
namespace managers {
namespace mission {

	class DestroyMissionSpawnGroup : public SpawnGroup {
	protected:
		Vector<Reference<LairSpawn*> > destroyMissionList;

	public:
		DestroyMissionSpawnGroup(const DestroyMissionSpawnGroup& sp) : SpawnGroup(sp) {
			destroyMissionList = sp.destroyMissionList;
		}

		DestroyMissionSpawnGroup(const String& name, LuaObject& obj) : SpawnGroup(name, obj) {
			LuaObject destroyMissionSpawns = obj.getObjectField("destroyMissionSpawns");

			for (int i = 1; i <= destroyMissionSpawns.getTableSize(); ++i) {
				lua_rawgeti(destroyMissionSpawns.getLuaState(), -1, i);
				LuaObject spawn(destroyMissionSpawns.getLuaState());

				if (spawn.isValidTable()) {
					Reference<LairSpawn*> destroyMissionSpawn = new LairSpawn();
					destroyMissionSpawn->readObject(spawn);

					destroyMissionList.add(destroyMissionSpawn);
				}

				spawn.pop();
			}

			destroyMissionSpawns.pop();
		}

		Vector<Reference<LairSpawn*> >* getDestroyMissionList() {
			return &destroyMissionList;
		}

	};

}
}
}
}

using namespace server::zone::managers::mission;


#endif /* DESTROYMISSIONSPAWNGROUP_H_ */
