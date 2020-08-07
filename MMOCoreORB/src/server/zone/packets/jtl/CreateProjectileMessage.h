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

class CreateProjectileMessage : public BaseMessage {
public:
	CreateProjectileMessage() : BaseMessage() {
		insertShort(0x12);
		insertInt(0xB88AF9A5);  // CRC

		insertShort(0); // shipID
		insertByte(0); // weaponIndex
		insertByte(0); // projectileIndex
		insertByte(0); // component
		insertShort(0); // startPosition
		insertShort(0);
		insertShort(0);

		insertShort(0); // direction
		insertShort(0);
		insertShort(0);

		insertInt(0); // sequence
   }
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

};

class CreateProjectileMessageCallback : public MessageCallback {
	uint16 shipID;
	uint8 weaponIndex;
	uint8 projectileType;
	uint8 componentIndex;
	Vector3 position;
	Vector3 direction;
	uint32 sequence;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	CreateProjectileMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
			MessageCallback(client, server) {

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
		StringBuffer buffer;
		buffer << "CreateProjectileMessage: " << shipID << endl << "weapon: " << weaponIndex << endl << "projectileType:" << projectileType << endl;
		buffer << "ComponentIndex:" << componentIndex << endl << "position: " << position.toString() << endl << "direction: " << direction.toString() << endl << "sequence: " << sequence << endl;
		static Logger logger;
		logger.info(buffer.toString(), true);

		//
		ManagedReference<CreatureObject*> object = client->getPlayer();

		if (object == nullptr)
			return;

		Locker _locker(object);

		ManagedReference<ShipObject*> ship = dynamic_cast<ShipObject*>(object->getParent().get().get());

		if (ship == nullptr)
			return;

		String name = ship->getComponentNameMap()->get(ShipObject::WEAPON_COMPONENT_START+weaponIndex).toString();
		const ShipProjectileData* data = ShipManager::instance()->getProjectileData(name.hashCode());

		ShipWeaponComponent *weapon = cast<ShipWeaponComponent*>(ship->getComponentObject(ShipObject::WEAPON_COMPONENT_START+weaponIndex));

		if (weapon == nullptr) {
			ship->error("Attempted to create projectile with missing weapon : " + String::valueOf(weaponIndex));
			return;
		}

		float currentEnergy = ship->getCapacitorEnergy();
		float cost = weapon->getEnergyPerShot();
		if (cost > currentEnergy) {
			ship->error("Attempted to create projectile with insufficient energy");
			return;
		}

		Locker cross(ship, object);
		ship->setCapacitorEnergy(currentEnergy-cost, true);

		// TODO: Validate shot
		ShipManager::ShipProjectile* projectile = new ShipManager::ShipProjectile(ship, weaponIndex, projectileType, componentIndex, position, direction, data->getSpeed(), data->getRange(), System::getMiliTime());

		// compensate latency for outgoing message
		ShipManager::instance()->addProjectile(projectile);
		CreateProjectileMessage *message = new CreateProjectileMessage(position, direction, componentIndex, projectileType, weaponIndex, ship->getUniqueID(), sequence);

		object->broadcastMessage(message, false);
	}

	const char* getTaskName() {
		return "CreateProjectileMessage";
	}
};

#endif /* CREATEPROJECTICEMESSAGE_H_ */
