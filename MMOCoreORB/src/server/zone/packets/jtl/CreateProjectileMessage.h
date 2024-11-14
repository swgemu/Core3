/*
 * CreateProjecticeMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef CREATEPROJECTICEMESSAGE_H_
#define CREATEPROJECTICEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/packets/ship/PackedPosition.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/objects/ship/components/ShipWeaponComponent.h"
#include "server/zone/packets/MessageCallback.h"
#include "server/zone/managers/spacecombat/SpaceCombatManager.h"
#include "server/zone/managers/spacecombat/projectile/ShipMissile.h"
#include "server/zone/managers/spacecombat/projectile/ShipCountermeasure.h"

class CreateProjectileMessage : public BaseMessage {
private:
	constexpr static float directionScale = PackedPosition::positionScale * ShipProjectile::positionScale;

public:
	CreateProjectileMessage(Vector3 position, Vector3 direction, uint8 component, uint8 projectile, uint8 weapon, uint16 shipID, uint32 sequence) {
		insertShort(0x12);
		insertInt(0xB88AF9A5);

		insertShort(shipID);
		insertByte(weapon);
		insertByte(projectile);
		insertByte(component);

		PackedPosition packed;

		packed.set(position);
		packed.write(this);

		packed.set(direction);
		packed.write(this);

		insertInt(sequence);
	}

	CreateProjectileMessage(ShipObject* ship, const ShipProjectile* projectile, uint32 syncStamp = 0) {
		insertShort(0x12);
		insertInt(0xB88AF9A5);

		insertShort(ship->getUniqueID());
		insertByte(projectile->getWeaponSlot());
		insertByte(projectile->getProjectileType());
		insertByte(projectile->getComponentSlot());

		PackedPosition packed;

		packed.set(projectile->getThisPosition());
		packed.write(this);

		Vector3 dirScaled = projectile->getDirection() * directionScale;
		writeSignedShort(dirScaled.getX());
		writeSignedShort(dirScaled.getZ());
		writeSignedShort(dirScaled.getY());

		insertInt(syncStamp ? syncStamp : ship->getSyncStamp());
	}
};

class CreateProjectileMessageCallback : public MessageCallback {
protected:
	uint16 shipID;
	uint8 weaponIndex;
	uint8 projectileType;
	uint8 componentIndex;
	Vector3 position;
	Vector3 direction;
	uint32 sequence;

public:
	CreateProjectileMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		shipID = 0;
		weaponIndex = 0;
		projectileType = 0;
		componentIndex = 0;
		position = Vector3(0,0,0);
		direction = Vector3(0,0,0);
		sequence = 0;
	}

	void parse(Message* message) {
		shipID = message->parseShort();
		weaponIndex = message->parseByte();
		projectileType = message->parseByte();
		componentIndex = message->parseByte();

		PackedPosition packed;

		packed.parse(message);
		position = packed.get();

		packed.parse(message);
		direction = packed.get();

		sequence = message->parseInt();
	}

	void run() {
		ManagedReference<CreatureObject*> pilot = client->getPlayer();
		if (pilot == nullptr) {
			return;
		}

		ManagedReference<SceneObject*> root = pilot->getRootParent();
		if (root == nullptr) {
			return;
		}

		auto ship = root->asShipObject();
		if (ship == nullptr) {
			return;
		}

		uint32 slot = Components::WEAPON_START + weaponIndex;
		uint32 crc = ship->getShipComponentMap()->get(slot);

		if (crc == 0 || !ship->isComponentFunctional(slot)) {
			return;
		}

		auto shipManager = ShipManager::instance();
		if (shipManager == nullptr) {
			return;
		}

		auto data = shipManager->getProjectileData(crc);
		if (data == nullptr) {
			return;
		}

		Locker lock(pilot);
		Locker cross(ship, pilot);

		pilot->setSyncStamp(sequence);

		float energyPerShot = ship->getEnergyPerShotMap()->get(slot);

		if (energyPerShot > 0.f) {
			float energyEfficiency = Math::clamp(0.1f, ship->getComponentEnergyEfficiencyMap()->get(slot), 10.f);
			float actualEnergyCost = energyPerShot / energyEfficiency;
			float capacitorEnergy = ship->getCapacitorEnergy();

			if (capacitorEnergy < actualEnergyCost) {
				return;
			}

			ship->setCapacitorEnergy(capacitorEnergy - actualEnergyCost, true);
		}

		if (data->isCountermeasure()) {
			launchCountermeasure(ship, pilot, data);
		} else if (data->isMissile()) {
			launchMissile(ship, pilot, data);
		} else {
			auto projectile = new ShipProjectile(ship, weaponIndex, projectileType, componentIndex, position, direction, data->getSpeed(), data->getRange(), 1.f, System::getMiliTime());
			projectile->readProjectileData(data);

			SpaceCombatManager::instance()->addProjectile(ship, projectile, pilot);
		}
	}

	void launchCountermeasure(ShipObject* ship, CreatureObject* pilot, const ShipProjectileData* data) const {
		auto shipManager = ShipManager::instance();

		if (shipManager == nullptr) {
			return;
		}

		int slot = Components::WEAPON_START + weaponIndex;
		int ammoType = ship->getAmmoClassMap()->get(slot);

		int currentAmmo = ship->getCurrentAmmoMap()->get(slot);

		if (currentAmmo < 1) {
			return;
		}

		auto counterData = shipManager->getCountermeasureData(ammoType);

		if (counterData == nullptr) {
			return;
		}

		auto deltaVector = ship->getDeltaVector();

		if (deltaVector == nullptr) {
			return;
		}

		ship->setCurrentAmmo(slot, currentAmmo - 1, nullptr, DeltaMapCommands::SET, deltaVector);
		deltaVector->sendMessages(ship);

		auto counter = new ShipCountermeasure(ship, weaponIndex, projectileType, componentIndex, position, direction, data->getSpeed(), data->getRange(), 1.f, System::getMiliTime());

		counter->readProjectileData(data);
		counter->readCountermeasureData(counterData);

		SpaceCombatManager::instance()->addCountermeasure(ship, counter);
	}

	void launchMissile(ShipObject* ship, CreatureObject* pilot, const ShipProjectileData* data) const {
		auto targetID = pilot->getTargetID();
		if (targetID == 0) {
			return;
		}

		auto zoneServer = pilot->getZoneServer();
		if (zoneServer == nullptr) {
			return;
		}

		auto target = zoneServer->getObject(targetID, false);
		if (target == nullptr || !target->isShipObject()) {
			return;
		}

		auto targetShip = target->asShipObject();
		if (targetShip == nullptr) {
			return;
		}

		auto shipManager = ShipManager::instance();
		if (shipManager == nullptr) {
			return;
		}

		int weaponSlot = Components::WEAPON_START + weaponIndex;
		int ammoType = ship->getAmmoClassMap()->get(weaponSlot);

		int currentAmmo = ship->getCurrentAmmoMap()->get(weaponSlot);
		if (currentAmmo < 1) {
			return;
		}

		auto missileData = shipManager->getMissileData(ammoType);
		if (missileData == nullptr) {
			return;
		}

		auto deltaVector = ship->getDeltaVector();
		if (deltaVector == nullptr) {
			return;
		}

		ship->setCurrentAmmo(weaponSlot, currentAmmo - 1, nullptr, DeltaMapCommands::SET, deltaVector);
		deltaVector->sendMessages(ship);

		auto missile = new ShipMissile(ship, weaponIndex, projectileType, componentIndex, position, direction, data->getSpeed(), data->getRange(), 1.f, System::getMiliTime());
		missile->readProjectileData(data);
		missile->readMissileData(missileData);

		missile->setTarget(targetShip);
		missile->calculateTimeToHit();

		String slotName = Components::shipComponentSlotToString(componentIndex);

		if (slotName != "") {
			uint32 componentCrc = targetShip->getShipComponentMap()->get(componentIndex);
			if (componentCrc == 0) {
				return;
			}

			auto collisionData = shipManager->getCollisionData(targetShip);
			if (collisionData == nullptr) {
				return;
			}

			const auto& hardpoints = collisionData->getHardpoints(slotName);
			const auto& hardpoint = hardpoints.get(componentCrc);
			const auto& hardpointPosition = hardpoint.getSphere().getCenter();

			missile->setHardpointTranslation(hardpointPosition);
		}

		SpaceCombatManager::instance()->addMissile(ship, missile);
	}

	const char* getTaskName() {
		return "CreateProjectileMessage";
	}
};

#endif /* CREATEPROJECTICEMESSAGE_H_ */
