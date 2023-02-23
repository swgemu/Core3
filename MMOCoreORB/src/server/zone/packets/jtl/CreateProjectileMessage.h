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

class CreateProjectileMessage : public BaseMessage {
private:
	const static constexpr float positionScale = 32767.f / 8000.f;

public:
	CreateProjectileMessage(Vector3 position, Vector3 direction, uint8 component, uint8 projectile, uint8 weapon, uint16 shipID, uint32 sequence) {
		insertShort(0x12);
		insertInt(0xB88AF9A5);

		insertShort(shipID);
		insertByte(weapon);
		insertByte(projectile);
		insertByte(component);

		insertSignedShort((int16) (position.getX() * positionScale));
		insertSignedShort((int16) (position.getZ() * positionScale));
		insertSignedShort((int16) (position.getY() * positionScale));

		insertSignedShort((int16) (direction.getX() * positionScale));
		insertSignedShort((int16) (direction.getZ() * positionScale));
		insertSignedShort((int16) (direction.getY() * positionScale));

		insertInt(sequence);
	}
};

class CreateProjectileMessageCallback : public MessageCallback {
	uint16 shipID;

	uint8 weaponIndex;
	uint8 projectileType;
	uint8 componentIndex;

	Vector3 position;
	Vector3 direction;

	uint32 sequence;

	float speed;
	float range;

public:
	CreateProjectileMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		shipID = 0;

		weaponIndex = 0;
		projectileType = 0;
		componentIndex = 0;

		position = Vector3(0,0,0);
		direction = Vector3(0,0,0);

		sequence = 0;

		speed = 0.f;
		range = 0.f;
	}

	void parse(Message* message) {
		shipID = message->parseShort();

		weaponIndex = message->parseByte();
		projectileType = message->parseByte();
		componentIndex = message->parseByte();

		float posX = message->parseSignedShort();
		float posZ = message->parseSignedShort();
		float posY = message->parseSignedShort();
		position = Vector3(posX, posY, posZ) * (8000.f / 32767.f);

		float dirX = message->parseSignedShort();
		float dirZ = message->parseSignedShort();
		float dirY = message->parseSignedShort();
		direction = Vector3(dirX, dirY, dirZ) * (8000.f / 32767.f);

		sequence = message->parseInt();
	}

	void run() {
		auto pilot = client->getPlayer();
		if (pilot == nullptr) {
			return;
		}

		auto root = pilot->getRootParent();
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

		range = data->getRange();
		if (range == 0.f) {
			range = 512.f;
		}

		speed = data->getSpeed();
		if (speed == 0.f) {
			speed = 550.f;
		}

		uint16 uniqueID = ship->getUniqueID();
		if (shipID != uniqueID) {
			shipID = uniqueID;
		}

		float currentEnergy = ship->getCapacitorEnergy();
		float cost = weapon->getEnergyPerShot();
		if (currentEnergy < cost) {
			return;
		}

		Locker lock(pilot);
		Locker cross(ship, pilot);

		ship->setCapacitorEnergy(currentEnergy - cost, true);

		auto projectile = new ShipManager::ShipProjectile(ship, weaponIndex, projectileType, componentIndex, position, direction, speed, range, System::getMiliTime());
		shipManager->addProjectile(projectile);

		CreateProjectileMessage* message = new CreateProjectileMessage(position, direction, componentIndex, projectileType, weaponIndex, shipID, sequence);
		pilot->broadcastMessage(message, false);

/*
		uint32 syncStamp = System::getMiliTime() & 0xFFFFFFFF;

		StringBuffer msg;

		msg << "CreateProjectileMessageCallback: " << endl
		<< " shipID:         " << shipID << endl
		<< " weaponIndex:    " << weaponIndex << endl
		<< " projectileType: " << projectileType << endl
		<< " componentIndex: " << componentIndex << endl
		<< " position:       " << position.getX() << ", " << position.getZ() << ", "  << position.getY() << endl
		<< " direction:      " << direction.getX() << ", " << direction.getZ() << ", "  << direction.getY() << endl
		<< " range:          " << range << endl
		<< " speed:          " << speed << endl
		<< " sequence:       " << sequence << endl
		<< " syncLong:       " << syncStamp << endl
		<< "----------------------------------------------------------------";

		pilot->sendSystemMessage(msg.toString());
*/
	}

	const char* getTaskName() {
		return "CreateProjectileMessage";
	}
};

#endif /* CREATEPROJECTICEMESSAGE_H_ */
