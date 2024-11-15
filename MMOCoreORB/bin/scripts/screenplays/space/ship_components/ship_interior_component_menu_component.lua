--Copyright (C) 2007 <SWGEmu>

--This File is part of Core3.

--This program is free software; you can redistribute
--it and/or modify it under the terms of the GNU Lesser
--General Public License as published by the Free Software
--Foundation; either version 2 of the License,
--or (at your option) any later version.

--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--See the GNU Lesser General Public License for
--more details.

--You should have received a copy of the GNU Lesser General
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

--Linking Engine3 statically or dynamically with other modules
--is making a combined work based on Engine3.
--Thus, the terms and conditions of the GNU Lesser General Public License
--cover the whole combination.

--In addition, as a special exception, the copyright holders of Engine3
--give you permission to combine Engine3 program with free software
--programs or libraries that are released under the GNU LGPL and with
--code included in the standard release of Core3 under the GNU LGPL
--license (or modified versions of such code, with unchanged license).
--You may copy and distribute such a system following the terms of the
--GNU LGPL for Engine3 and the licenses of the other code concerned,
--provided that you include the source code of that other code when
--and as the GNU LGPL requires distribution of source code.

--Note that people who make modified versions of Engine3 are not obligated
--to grant this special exception for their modified versions;
--it is their choice whether to do so. The GNU Lesser General Public License
--gives permission to release a modified version without this exception;
--this exception also makes it possible to release a modified version
--which carries forward this exception.

ShipInteriorComponentMenuComponent = {
	GENERAL = 1,
	PLASMA_CONDUIT = 2,
	REACTOR = 3,
	ENGINE = 4,
	SHIELD_GENERATOR = 5,
	CAPACITOR = 6,
}

function ShipInteriorComponentMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	print(test)

	menuResponse:addRadialMenuItem(20, 3, "@space/space_interaction:repair")
end

function ShipInteriorComponentMenuComponent:handleObjectMenuSelect(pComponent, pPlayer, selectedID)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() or pComponent == nil) then
		return 0
	end

	print("Interior Component Menu Selected ID " .. selectedID .. " Container ID: " .. SceneObject(pComponent):getObjectID())

	if (selectedID ~= 20) then
		return 0
	end

	-- Make sure player is within 10m
	if (not CreatureObject(pPlayer):isInRangeWithObject3d(pComponent, 10)) then
		CreatureObject(pPlayer):sendSystemMessage("@space/space_interaction:target_too_far")
		return 0
	end

	local pShip = SceneObject(pPlayer):getRootParent()

	if (pShip == nil or not SceneObject(pShip):isShipObject()) then
		return 0
	end

	local conditionDamage = TangibleObject(pComponent):getConditionDamage()

	if (conditionDamage < 1) then
		CreatureObject(pPlayer):sendSystemMessage("@space/space_interaction:no_damage_to_repair") -- "That component is not damaged."
		return 0
	end

	local ship = LuaShipObject(pShip)

	if (ship == nil) then
		return 0
	end

	-- Faction Check
	local shipFaction = TangibleObject(pShip):getFaction()

	if (shipFaction ~= FACTIONNEUTRAL and shipFaction ~= CreatureObject(pPlayer):getFaction()) then
		CreatureObject(pPlayer):sendSystemMessage("@space/space_interaction:wrong_faction")
		return 0
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return 0
	end

	local componentName = SceneObject(pComponent):getObjectName()
	local componentType = 0

	local pRepairKit = nil

	if (string.find(componentName, "plasma") ~= nil) then
		componentType = self.PLASMA_CONDUIT
		pRepairKit = getContainerObjectByTemplate(pInventory, "object/tangible/ship/crafted/repair/repair_kit_plasma_conduit.iff", true)
	elseif (string.find(componentName, "reactor") ~= nil) then
		componentType = self.REACTOR
		pRepairKit = getContainerObjectByTemplate(pInventory, "object/tangible/ship/crafted/repair/reactor_repair_kit.iff", true)
	elseif (string.find(componentName, "engine") ~= nil) then
		componentType = self.ENGINE
		pRepairKit = getContainerObjectByTemplate(pInventory, "object/tangible/ship/crafted/repair/engine_repair_kit.iff", true)
	elseif (string.find(componentName, "shield") ~= nil) then
		componentType = self.SHIELD_GENERATOR
		pRepairKit = getContainerObjectByTemplate(pInventory, "object/tangible/ship/crafted/repair/shield_repair_kit.iff", true)
	elseif (string.find(componentName, "capacitor") ~= nil) then
		componentType = self.CAPACITOR
		pRepairKit = getContainerObjectByTemplate(pInventory, "object/tangible/ship/crafted/repair/capacitor_repair_kit.iff", true)
	end

	if (pRepairKit == nil) then
		componentType = self.GENERAL
		pRepairKit = getContainerObjectByTemplate(pInventory, "object/tangible/ship/crafted/repair/generic_repair_kit.iff", true)
	end

	print("Component Name: " .. componentName .. " Type: " .. type)

	if (componentType < self.GENERAL or pRepairKit == nil) then -- or check for kits by type
		CreatureObject(pPlayer):sendSystemMessage("@space/space_interaction:no_kits")
		return 0
	end

	-- "wrong_repair_kit", "That repair kit is not the correct type to fix this component."

	local componentID = SceneObject(pRepairKit):getObjectID()

	print("Repair Kit ID: " .. componentID)


	ship:repairInteriorComponent(pPlayer, pComponent, pRepairKit, componentType)


	--[[

		"damage_left_chassis", "You did not have enough repair kits to completely repair your Chassis. %DI points of damage remain."
		"damage_left_component", "Not all damage was repaired. %DI points of damage remain on the %TO. "
		"damage_left_component_armor", "Not all armor damage was repaired. %DI points of armor damage remain."

		"repaired_x_armor_component_damage", "You have fixed %DI points of armor damage on the %TO."
		"repaired_x_armor_component_damage_destroy_kit", "You have fixed %DI points of armor damage on the %TO. The repair kit is used up."
		"repaired_x_chassis_damage", "You have fixed %DI points of chassis damage."
		"repaired_x_chassis_damage_destroy_kit", "You have fixed %DI points of chassis damage. The repair kit is used up."
		"repaired_x_component_damage", "You have fixed %DI points of damage on the %TO."
		"repaired_x_component_damage_destroy_kit", "You have fixed %DI points of damage on the %TO. The repair kit is used up."
		"repairo_beginning", "Beginning repair procedure."
		"repairo_cant_heal_enemy", "Repair target is identified as a possible enemy. Aborting procedure."
		"repairo_out_of_range", "Either your ship or the target ship aren't positioned close enough to the repair target to begin the procedure."

		"repair_arrive_hyperspace", "Repair ship now arriving from hyperspace."




		"fix_hull", "You succesfully patch the hull leak. The repair kit is consumed in the process."
		"fix_plasma_conduit", "You succesfully patch the broken plasma conduit."
		"fix_plasma_conduit_destroy", "You succesfully patch the broken plasma conduit. The repair kit is consumed in the process."
		"hull_breach", "HULL BREACH! The ship atmosphere is leaking into space. Find the Hull Access panel and patch the leak."
		"hull_breach_damage", "<HULL BREACH!> You choke from lack of air."
		"hyperdrive_recharged", "Hyperdrive recharged."

		"plasma_conduit_burst0", "A reactor conduit has burst!"
		"plasma_conduit_burst1", "An engine conduit has burst!"
		"plasma_conduit_burst12", "A weapon conduit has burst!"
		"plasma_conduit_burst13", "A weapon conduit has burst!"
		"plasma_conduit_burst14", "A weapon conduit has burst!"
		"plasma_conduit_burst15", "A weapon conduit has burst!"
		"plasma_conduit_burst16", "A weapon conduit has burst!"
		"plasma_conduit_burst17", "A weapon conduit has burst!"
		"plasma_conduit_burst18", "A weapon conduit has burst!"
		"plasma_conduit_burst19", "A weapon conduit has burst!"
		"plasma_conduit_burst2", "A shield conduit has burst!"
		"plasma_conduit_burst3", "A shield conduit has burst!"
		"plasma_conduit_burst6", "A capacitor conduit has burst!"
		"plasma_conduit_burst7", "A booster conduit has burst!"
		"plasma_conduit_burst8", "A droid/flight-computer interface conduit has burst!"
		"plasma_leak_begin", "This area of the ship has a PLASMA LEAK! It begins to scorch the flesh from your bones!"
		"plasma_leak_end", "You have successfully escaped the scorching flames of the plasma leak."

		"repair_kit_armor_d", "Armor Repair Kit"
		"repair_kit_armor_n", "Armor Repair Kit"
		"repair_kit_booster_d", "Booster Repair Kit"
		"repair_kit_booster_n", "Booster Repair Kit"
		"repair_kit_capacitor_d", "Weapon Capacitor Repair Kit"
		"repair_kit_capacitor_n", "Weapon Capacitor Repair Kit"
		"repair_kit_chassis", "Chassis Repair Kit"
		"repair_kit_conduit_d", "Conduit Repair Kit"
		"repair_kit_droid_interface_d", "Droid Interface Repair Kit"
		"repair_kit_droid_interface_n", "Droid Interface Repair Kit"
		"repair_kit_engine_d", "Engine Repair Kit"
		"repair_kit_engine_n", "Engine Repair Kit"
		"repair_kit_hull_d", "Hull Repair Kit"
		"repair_kit_hull_n", "Hull Repair Kit"
		"repair_kit_reactor_d", "Reactor Repair Kit"
		"repair_kit_reactor_n", "Reactor Repair Kit"
		"repair_kit_shield_d", "Shield Generator Repair Kit"
		"repair_kit_shield_n", "Shield Generator Repair Kit"
		"repair_kit_ship_d", "This repair kit can be used to repair all ship components and chassis. It cannot be used to patch plasma conduits."
		"repair_kit_ship_n", "All Purpose Ship Repair Kit"
		"repair_kit_weapon_d", "Weapon Repair Kit"
		"repair_kit_weapon_n", "Weapon Repair Kit"

	]]

	return 0
end
