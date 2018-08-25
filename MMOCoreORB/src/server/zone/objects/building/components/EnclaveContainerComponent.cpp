#include "EnclaveContainerComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
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

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == nullptr)
		return false;

	bool storedPet = false;

	for (int i = 0; i < ghost->getActivePetsSize(); ++i) {
		ManagedReference<AiAgent*> object = ghost->getActivePet(i);

		if (object != nullptr) {
			ManagedReference<PetControlDevice*> pcd = object->getControlDevice().get().castTo<PetControlDevice*>();

			if (pcd == nullptr)
				continue;

			Reference<PetControlDeviceStoreObjectTask*> task = new PetControlDeviceStoreObjectTask(pcd, creature, true);
			task->execute();

			storedPet = true;
		}
	}

	if (storedPet)
		creature->sendSystemMessage("@pvp_rating:enclave_deny_pet_entry"); // As you are not permitted to bring any pets or hirelings into the enclave. They have been returned to your data pad for you.

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

	if (frsData == nullptr)
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

	if (ghost == nullptr)
		return false;

	if (ghost->hasGodMode())
		return true;

	int enclaveType = 0;

	ManagedReference<SceneObject*> enclave = sceneObject->getParent().get();

	if (enclave == nullptr)
		return false;

	if (enclave->getServerObjectCRC() == STRING_HASHCODE("object/building/yavin/light_enclave.iff"))
		enclaveType = FrsManager::COUNCIL_LIGHT;
	else if (enclave->getServerObjectCRC() == STRING_HASHCODE("object/building/yavin/dark_enclave.iff"))
		enclaveType = FrsManager::COUNCIL_DARK;
	else
		return false;

	FrsData* frsData = ghost->getFrsData();

	if (frsData == nullptr)
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

int EnclaveContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) const {
	CreatureObject* creo = object->asCreatureObject();

	if (creo == nullptr || sceneObject->getObjectID() != FrsManager::ARENA_CELL)
		return ContainerComponent::notifyObjectRemoved(sceneObject, object, destination);

	FrsManager* frsMan = creo->getZoneServer()->getFrsManager();

	if (frsMan->isPlayerFightingInArena(creo->getObjectID())) {
		frsMan->handleLeftArena(creo);
	}

	return ContainerComponent::notifyObjectRemoved(sceneObject, object, destination);
}
