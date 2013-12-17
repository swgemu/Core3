
class TransferPetTask : public Task {
	ManagedReference<CreatureObject*> player;
	ManagedReference<PetControlDevice*> petControlDevice;
	ManagedReference<CreatureObject*> targetPlayer;
public:
	TransferPetTask(CreatureObject* player, PetControlDevice* petControlDevice, CreatureObject* targetPlayer) {
		this->player = player;
		this->petControlDevice = petControlDevice;
		this->targetPlayer = targetPlayer;
	}

	void run() {
		ManagedReference<AiAgent*> pet = cast<AiAgent*>(petControlDevice->getControlledObject());

		Locker locker(player);
		Locker clocker(pet, player);

		pet->setCreatureLink(targetPlayer);
		pet->setFaction(targetPlayer->getFaction());
		pet->setFollowObject(targetPlayer);

		if (targetPlayer->getPvpStatusBitmask() & CreatureFlag::PLAYER)
			pet->setPvpStatusBitmask(targetPlayer->getPvpStatusBitmask() - CreatureFlag::PLAYER, true);
		else
			pet->setPvpStatusBitmask(targetPlayer->getPvpStatusBitmask(), true);

		clocker.release();

		Locker clocker2(targetPlayer, player);

		ManagedReference<SceneObject*> targetDatapad = targetPlayer->getSlottedObject("datapad");
		ManagedReference<PlayerObject*> targetGhost = targetPlayer->getPlayerObject();
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		targetDatapad->transferObject(petControlDevice, -1);

		ghost->removeFromActivePets(pet);
		targetGhost->addToActivePets(pet);

		targetDatapad->broadcastObject(petControlDevice, true);

		player->sendSystemMessage("@pet/pet_menu:pet_transfer_succeed"); // The pet has been successfully transferred
	}
};
