#include "PersonnelPerkZoneComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/tangible/EventPerkDeedTemplate.h"

void PersonnelPerkZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zne) const {
	if (zne == NULL)
		return;

	if (sceneObject->getServerObjectCRC() == 0x740E97C5 || sceneObject->getServerObjectCRC() == 0xCA8B8505) {
		CreatureManager* creatureManager = zne->getCreatureManager();
		CreatureObject* recruiter = NULL;

		if (sceneObject->getServerObjectCRC() == 0xCA8B8505) // object/tangible/event_perk/imperial_recruiter_perk.iff
			recruiter = creatureManager->spawnCreature(STRING_HASHCODE("imperial_recruiter"), 0, sceneObject->getPositionX(), sceneObject->getPositionZ(), sceneObject->getPositionY(), 0);
		else if (sceneObject->getServerObjectCRC() == 0x740E97C5) // object/tangible/event_perk/rebel_recruiter_perk.iff
			recruiter = creatureManager->spawnCreature(STRING_HASHCODE("rebel_recruiter"), 0, sceneObject->getPositionX(), sceneObject->getPositionZ(), sceneObject->getPositionY(), 0);

		if (recruiter == NULL)
			return;

		sceneObject->addChildObject(recruiter);
	}

	EventPerkDataComponent* data = cast<EventPerkDataComponent*>(sceneObject->getDataObjectComponent()->get());

	if (data == NULL)
		return;

	EventPerkDeed* deed = data->getDeed();

	if (deed == NULL)
		return;

	if (deed->getPerkType() == EventPerkDeedTemplate::HONORGUARD || deed->getPerkType() == EventPerkDeedTemplate::RECRUITER)
		deed->parseChildObjects(sceneObject);
}
