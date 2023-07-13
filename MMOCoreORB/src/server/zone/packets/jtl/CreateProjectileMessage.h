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

class CreateProjectileMessage : public BaseMessage {
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

	CreateProjectileMessage(ShipObject* ship, ShipObject* receiver, const ShipProjectile& projectile) {
		insertShort(0x12);
		insertInt(0xB88AF9A5);

		insertShort(ship->getUniqueID());
		insertByte(projectile.getWeaponSlot());
		insertByte(projectile.getProjectileType());
		insertByte(projectile.getComponentSlot());

		PackedPosition packed;

		packed.set(projectile.getThisPosition());
		packed.write(this);

		Vector3 dirScaled = projectile.getDirection() * ShipProjectile::positionScale;
		writeSignedShort(dirScaled.getX());
		writeSignedShort(dirScaled.getZ());
		writeSignedShort(dirScaled.getY());

		insertInt(receiver->getSyncStamp());
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

		auto component = ship->getComponentObject(ShipObject::WEAPON_COMPONENT_START + weaponIndex);
		if (component == nullptr) {
			return;
		}

		auto weapon = dynamic_cast<ShipWeaponComponent*>(component);
		if (weapon == nullptr) {
			return;
		}

		auto shipManager = ShipManager::instance();
		if (shipManager == nullptr) {
			return;
		}

		auto data = shipManager->getProjectileData(component->getComponentDataName().hashCode());
		if (data == nullptr) {
			return;
		}

		float range = data->getRange();
		if (range == 0.f) {
			return;
		}

		float speed = data->getSpeed();
		if (speed == 0.f) {
			return;
		}

		float currentEnergy = ship->getCapacitorEnergy();
		float cost = weapon->getEnergyPerShot();
		if (currentEnergy < cost) {
			return;
		}

		uint16 uniqueID = ship->getUniqueID();
		if (shipID != uniqueID) {
			shipID = uniqueID;
		}

		Locker lock(pilot);
		Locker cross(ship, pilot);

		ship->setSyncStamp(sequence);
		ship->setCapacitorEnergy(currentEnergy - cost, true);

		auto spaceCombat = SpaceCombatManager::instance();

		if (spaceCombat != nullptr) {
			auto projectile = ShipProjectile(ship, weaponIndex, projectileType, componentIndex, position, direction, speed, range, 1.f, System::getMiliTime());
			spaceCombat->addProjectile(ship, projectile);
		}
	}

	const char* getTaskName() {
		return "CreateProjectileMessage";
	}
};

#endif /* CREATEPROJECTICEMESSAGE_H_ */
