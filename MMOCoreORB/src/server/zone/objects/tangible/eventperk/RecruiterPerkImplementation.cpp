#include "server/zone/objects/tangible/eventperk/RecruiterPerk.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/Zone.h"

void RecruiterPerkImplementation::notifyInsertToZone(Zone* zone) {
	if (recruiterTemplate == "")
		return;

	CreatureManager* creatureManager = zone->getCreatureManager();

	CreatureObject* recruiter = creatureManager->spawnCreature(recruiterTemplate.hashCode(), 0, posX, posZ, posY, 0);

	addChildObject(recruiter);
}

void RecruiterPerkImplementation::setupRecruiter(Zone* zone, const String& mobileTemplate, float x, float z, float y) {
	CreatureManager* creatureManager = zone->getCreatureManager();
	printf("Setting up recruiter %s \n", mobileTemplate.toCharArray());
	CreatureObject* recruiter = creatureManager->spawnCreature(mobileTemplate.hashCode(), 0, x, z, y, 0);

	addChildObject(recruiter);

	posX = x;
	posZ = z;
	posY = y;
	recruiterTemplate = mobileTemplate;
}
