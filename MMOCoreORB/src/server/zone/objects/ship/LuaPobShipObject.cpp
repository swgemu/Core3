#include "LuaPobShipObject.h"
#include "server/zone/objects/ship/PobShipObject.h"
#include "ShipComponentFlag.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/tangible/ship/crafted/repair/ShipComponentRepairKit.h"
#include "server/zone/objects/tangible/ship/interiorComponents/ShipInteriorComponent.h"

const char LuaPobShipObject::className[] = "LuaPobShipObject";

Luna<LuaPobShipObject>::RegType LuaPobShipObject::Register[] = {
	{ "_setObject", &LuaPobShipObject::_setObject },
	{ "_getObject", &LuaSceneObject::_getObject },
	{ "repairInteriorComponent", &LuaPobShipObject::repairInteriorComponent },
	{ 0, 0}
};

LuaPobShipObject::LuaPobShipObject(lua_State *L) : LuaTangibleObject(L) {
#ifdef DYNAMIC_CAST_LUAOBJECTS
	realObject = dynamic_cast<PobShipObject*>(_getRealSceneObject());
	assert(!_getRealSceneObject() || realObject != nullptr);
#else
	realObject = static_cast<ShipObject*>(lua_touserdata(L, 1));
#endif
}

LuaPobShipObject::~LuaPobShipObject(){
}

int LuaPobShipObject::_setObject(lua_State* L) {
	LuaTangibleObject::_setObject(L);

#ifdef DYNAMIC_CAST_LUAOBJECTS
	auto obj = dynamic_cast<PobShipObject*>(_getRealSceneObject());

	if (obj != realObject)
		realObject = obj;

	assert(!_getRealSceneObject() || realObject != nullptr);
#else
	auto obj = static_cast<PobShipObject*>(lua_touserdata(L, -1));

	if (realObject != obj)
		realObject = obj;
#endif

	return 0;
}
int LuaPobShipObject::repairInteriorComponent(lua_State* L) {
	int numberOfArguments = lua_gettop(L) - 1;

	if (numberOfArguments != 2) {
		realObject->error() << "Improper number of arguments in LuaPobShipObject::repairInteriorComponent.";
		return 0;
	}

	CreatureObject* player = (CreatureObject*)lua_touserdata(L, -2);
	TangibleObject* interiorComponent = (TangibleObject*)lua_touserdata(L, -1);

	if (player == nullptr || interiorComponent == nullptr || !interiorComponent->isShipInteriorComponent()) {
		return 0;
	}

	auto shipInteriorComp = cast<ShipInteriorComponent*>(interiorComponent);

	if (shipInteriorComp == nullptr) {
		return 0;
	}

	int componentSlot = shipInteriorComp->getComponentSlot();

	if (componentSlot < PobShipObject::PLASMA_CONDUIT) {
		return 0;
	}

	auto inventory = player->getInventory();

	if (inventory == nullptr) {
		return 0;
	}

	ShipComponentRepairKit* repairKit = nullptr;

	Locker playerLock(player);

	for (int j = 0; j < inventory->getContainerObjectsSize(); j++) {
		SceneObject* item = inventory->getContainerObject(j);

		if (item == nullptr || !item->isShipComponentRepairKit()) {
			continue;
		}

		repairKit = cast<ShipComponentRepairKit*>(item);

		if (repairKit == nullptr || repairKit->getComponentSlot() == componentSlot) {
			repairKit = nullptr;
			continue;
		}

		break;
	}

	playerLock.release();

	if (repairKit == nullptr) {
		player->sendSystemMessage("@space/space_interaction:no_kits");
		return 0;
	}

	// Lock the ship
	Locker lock(realObject);

	// Cross lock the component
	Locker clock(interiorComponent, realObject);

	auto hitpointsMap = realObject->getCurrentHitpointsMap();
	auto maxHitpointsMap = realObject->getMaxHitpointsMap();

	auto armorMap = realObject->getCurrentArmorMap();
	auto maxArmorMap = realObject->getMaxArmorMap();

	auto deltaVector = realObject->getDeltaVector();

	if (hitpointsMap == nullptr || maxHitpointsMap == nullptr || armorMap == nullptr || maxArmorMap == nullptr || deltaVector == nullptr) {
		return 0;
	}

	int repairCharges = repairKit->getRepairCharges();

	// player->info(true) << "Component Slot: " << componentSlot << " Repair Charges: " << repairCharges;

	if (componentSlot == PobShipObject::PLASMA_CONDUIT) {
		if (!(interiorComponent->getOptionsBitmask() & OptionBitmask::ACTIVATED)) {
			player->sendSystemMessage("@space/space_interaction:no_damage_to_repair"); // "That component is not damaged."
			return 0;
		}

		// Disable the animation
		if (interiorComponent->getOptionsBitmask() & OptionBitmask::ACTIVATED) {
			interiorComponent->setOptionsBitmask(OptionBitmask::DISABLED);
		}

		Locker kitLock(repairKit, realObject);

		if (repairCharges <= 1) {
			repairKit->destroyObjectFromWorld(true);
			repairKit->destroyObjectFromDatabase(true);

			player->sendSystemMessage("@space/space_interaction:fix_plasma_conduit_destroy"); // "You succesfully patch the broken plasma conduit. The repair kit is consumed in the process."
		} else {
			repairKit->setRepairCharges(repairCharges - 1);

			player->sendSystemMessage("@space/space_interaction:fix_plasma_conduit"); // "You succesfully patch the broken plasma conduit."
		}

		// Remove the damage conduit from the ShipsList
		realObject->removeDamagedInteriorComponent(interiorComponent->getObjectID());

		// Shut off the alarms
		realObject->togglePlasmaAlarms();

		// Remove flame dot variable from cell
		auto cellParent = interiorComponent->getParent().get().castTo<CellObject*>();

		if (cellParent != nullptr) {
			Locker cellLock(cellParent, realObject);

			cellParent->setCellFireVariable(-1.f);
		}
	} else {
		auto component = realObject->getComponentObject(componentSlot);

		if (component == nullptr) {
			return 0;
		}

		float hitpointsCurrent = hitpointsMap->get(componentSlot);
		float hitpointsMax = maxHitpointsMap->get(componentSlot);

		int hitPointsDamage = hitpointsMax - hitpointsCurrent;

		float armorCurrent = armorMap->get(componentSlot);
		float armorMax = armorMap->get(componentSlot);

		int armorDamage = armorMax - armorCurrent;

		if (hitPointsDamage == 0 && armorDamage == 0) {
			player->sendSystemMessage("@space/space_interaction:no_damage_to_repair"); // "That component is not damaged."
			return 0;
		}

		// Fix hit points first
		if (hitPointsDamage > 0) {
			Locker kitLock(repairKit, realObject);

			// Damage is greater then available amount repair kit has
			if (hitPointsDamage >= repairCharges) {
				// Destroy the repair kit
				repairKit->destroyObjectFromWorld(true);
				repairKit->destroyObjectFromDatabase(true);

				int repairAmount = (hitPointsDamage - repairCharges);

				// Update the component
				realObject->setComponentHitpoints(componentSlot, repairAmount, nullptr, 2, deltaVector);

				if (realObject->hasComponentFlag(componentSlot, ShipComponentFlag::DISABLED)) {
					realObject->removeComponentFlag(componentSlot, ShipComponentFlag::DISABLED, false);
				}

				StringIdChatParameter destroyMsg("@space/space_interaction:repaired_x_component_damage_destroy_kit"); // "You have fixed %DI points of damage on the %TO. The repair kit is used up."

				destroyMsg.setDI(repairAmount);

				StringBuffer name;
				name << "@space/space_item:" << component->getObjectName()->getStringID();
				destroyMsg.setTO(name.toString());

				player->sendSystemMessage(destroyMsg);

				return 0;
			// Damage is less than the available amount the repair kit has
			} else {
				// Update the component
				realObject->setComponentHitpoints(componentSlot, hitpointsMax, nullptr, 2, deltaVector);

				if (realObject->hasComponentFlag(componentSlot, ShipComponentFlag::DISABLED)) {
					realObject->removeComponentFlag(componentSlot, ShipComponentFlag::DISABLED, false);
				}

				// Calculate remaining amount of repair charges
				repairCharges = repairCharges - hitPointsDamage;

				// Update the kits repair charges
				repairKit->setRepairCharges(repairCharges);

				StringIdChatParameter repairMsg("@space/space_interaction:repaired_x_component_damage"); // "You have fixed %DI points of damage on the %TO."

				repairMsg.setDI(hitPointsDamage);

				StringBuffer name;
				name << "@space/space_item:" << component->getObjectName()->getStringID();
				repairMsg.setTO(name.toString());

				player->sendSystemMessage(repairMsg);
			}
		}

		// Fix armor damage
		if (armorDamage > 0) {
			// Damage is greater then available amount repair kit has
			if (armorDamage >= repairCharges) {
				// Destroy the repair kit
				repairKit->destroyObjectFromWorld(true);
				repairKit->destroyObjectFromDatabase(true);

				int repairAmount = (armorDamage - repairCharges);

				// Update the component
				realObject->setComponentHitpoints(componentSlot, repairAmount, nullptr, 2, deltaVector);

				StringIdChatParameter destroyMsg("@space/space_interaction:repaired_x_armor_component_damage_destroy_kit"); // "You have fixed %DI points of armor damage on the %TO. The repair kit is used up."

				destroyMsg.setDI(repairAmount);

				StringBuffer name;
				name << "@space/space_item:" << component->getObjectName()->getStringID();
				destroyMsg.setTO(name.toString());

				player->sendSystemMessage(destroyMsg);

				return 0;
			// Damage is less than the available amount the repair kit has
			} else {
				// Update the component
				realObject->setComponentHitpoints(componentSlot, hitpointsMax, nullptr, 2, deltaVector);

				// Calculate remaining amount of repair charges
				repairCharges = repairCharges - hitPointsDamage;

				StringIdChatParameter repairMsg("@space/space_interaction:repaired_x_armor_component_damage"); // "You have fixed %DI points of armor damage on the %TO."

				repairMsg.setDI(hitPointsDamage);

				StringBuffer name;
				name << "@space/space_item:" << component->getObjectName()->getStringID();
				repairMsg.setTO(name.toString());

				player->sendSystemMessage(repairMsg);
			}
		}
	}

	return 0;
}
