#include "EnclaveContainerComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/variables/FrsData.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/intangible/tasks/PetControlDeviceStoreObjectTask.h"
#include "server/zone/managers/frs/FrsManager.h"

bool EnclaveContainerComponent::checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	if (sceneObject->isBuildingObject())
		return checkBuildingPermission(sceneObject, creature, permission);
	else if (sceneObject->isCellObject())
		return checkCellPermission(sceneObject, creature, permission);

	return StructureContainerComponent::checkContainerPermission(sceneObject, creature, permission);
}

bool EnclaveContainerComponent::checkBuildingPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	if (permission != ContainerPermissions::WALKIN)
		return StructureContainerComponent::checkContainerPermission(sceneObject, creature, permission);

	if (!creature->isPlayerCreature()) {
		if (creature->isPet()) {
			ManagedReference<CreatureObject*> owner = creature->getLinkedCreature().get();

			if (owner != NULL) {
				ManagedReference<PetControlDevice*> petControlDevice = creature->getControlDevice().get().castTo<PetControlDevice*>();

				if (petControlDevice == NULL)
					return false;

				Reference<PetControlDeviceStoreObjectTask*> task = new PetControlDeviceStoreObjectTask(petControlDevice, owner, true);
				task->execute();

				owner->sendSystemMessage("@pvp_rating:enclave_deny_pet_entry"); // As you are not permitted to bring any pets or hirelings into the enclave. They have been returned to your data pad for you.
			}
		}

		return false;
	}

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return false;

	if (ghost->hasGodMode())
		return true;

	int enclaveType = 0;

	if (sceneObject->getServerObjectCRC() == STRING_HASHCODE("object/building/yavin/light_enclave.iff"))
		enclaveType = FrsManager::COUNCIL_LIGHT;
	else if (sceneObject->getServerObjectCRC() == STRING_HASHCODE("object/building/yavin/dark_enclave.iff"))
		enclaveType = FrsManager::COUNCIL_DARK;
	else
		return false;

	FrsData* frsData = ghost->getFrsData();

	if (frsData == NULL)
		return false;

	if (frsData->getCouncilType() == enclaveType)
		return true;

	creature->sendSystemMessage("@pvp_rating:enclave_deny_entry"); // A strange force repels you and keeps you from entering.

	return false;
}


bool EnclaveContainerComponent::checkCellPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const {
	if (permission != ContainerPermissions::WALKIN)
		return ContainerComponent::checkContainerPermission(sceneObject, creature, permission);

	if (!creature->isPlayerCreature())
		return false;

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return false;

	if (ghost->hasGodMode())
		return true;

	int enclaveType = 0;

	ManagedReference<SceneObject*> enclave = sceneObject->getParent().get();

	if (enclave == NULL)
		return false;

	if (enclave->getServerObjectCRC() == STRING_HASHCODE("object/building/yavin/light_enclave.iff"))
		enclaveType = FrsManager::COUNCIL_LIGHT;
	else if (enclave->getServerObjectCRC() == STRING_HASHCODE("object/building/yavin/dark_enclave.iff"))
		enclaveType = FrsManager::COUNCIL_DARK;
	else
		return false;

	FrsData* frsData = ghost->getFrsData();

	if (frsData == NULL)
		return false;

	if (frsData->getCouncilType() != enclaveType)
		return false;

	SortedVector<String>* groups = ghost->getPermissionGroups();
	ContainerPermissions* permissions = sceneObject->getContainerPermissions();

	uint16 allowPermissions = 0;

	for (int i = 0; i < groups->size(); ++i) {
		const String& group = groups->get(i);

		uint16 allow = permissions->getAllowPermissions(group);

		allowPermissions |= allow;
	}

	return permission & allowPermissions;
}
