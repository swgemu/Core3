/*
 * StaticSpawnAreaImplementation.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: da
 */

#include "StaticSpawnArea.h"
#include "SpawnObserver.h"
#include "server/zone/managers/creature/StaticSpawnGroup.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/aigroup/AiGroup.h"

void StaticSpawnAreaImplementation::spawnCreatures() {
	for (int i = 0; i < spawnCreatureTemplates.size(); ++i) {
		uint32 templateCRC = spawnCreatureTemplates.get(i);

		StaticSpawnGroup* templ = CreatureTemplateManager::instance()->getStaticGroup(templateCRC);

		uint32 crc;
		switch (templ->getType()) {
		case CreatureFlag::HERD:
			crc = String("object/aigroup/herd_group.iff").hashCode();
			break;
		case CreatureFlag::PACK:
			crc = String("object/aigroup/pack_group.iff").hashCode();
			break;
		case CreatureFlag::LAIR:
			crc = String("object/aigroup/lair_group.iff").hashCode();
			break;
		default:
			crc = String("object/aigroup/ai_group.iff").hashCode();
			break;
		}

		ManagedReference<AiGroup*> group = dynamic_cast<AiGroup*>(getZone()->getZoneServer()->createObject(crc, 0));
		if (group == NULL)
			continue;

		float x = templ->getX() + getPositionX();
		float y = templ->getY() + getPositionY();
		float z = templ->getZ() + getPositionZ();

		group->setPosition(x, z, y);

		//group->insertToZone(getZone());
		getZone()->addObject(group, -1, true);

		group->setup(templ);

		groups.put(group);
	}
}

