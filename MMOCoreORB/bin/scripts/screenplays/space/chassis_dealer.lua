local Logger = require("utils.logger")
require("utils.helpers")

ChassisDealer = ScreenPlay:new {
	CHASSIS_DEBUG = false,

	-- Key is ship name, values are blueprint name, blueprint path, and deed path.
	-- 	blacksun_heavy_s04 = {name = "", tier = 0, certification = "", blueprint = "", deedObject = ""}

	ships_table = {
		-- Starter Ships
		{name = "player_z95", tier = 0, certification = "cert_starships_z95headhunter", blueprint = "object/tangible/ship/components/chassis/z95_chassis_token.iff", deedObject = "z95_chassis_deed"},

		-- Freelance Ships
		{name = "blacksun_heavy_s01_chassis_token", tier = 1, certification = "cert_starships_heavyblacksunfighter", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s01_chassis_token.iff", deedObject = "blacksun_heavy_s01_deed"},
		{name = "blacksun_heavy_s02_chassis_token", tier = 2, certification = "cert_starships_heavyblacksunfighter", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s02_chassis_token.iff", deedObject = "blacksun_heavy_s02_deed"},
		{name = "blacksun_heavy_s03_chassis_token", tier = 3, certification = "cert_starships_heavyblacksunfighter", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s03_chassis_token.iff", deedObject = "blacksun_heavy_s03_deed"},
		{name = "blacksun_heavy_s04_chassis_token", tier = 4, certification = "cert_starships_heavyblacksunfighter", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s04_chassis_token.iff", deedObject = "blacksun_heavy_s04_deed"}

		-- Rebel Ships


		-- Imperial Ships


	},
}

registerScreenPlay("ChassisDealer", false)

--[[

	Handle Ship Blueprints and Deeds

]]

function ChassisDealer:getValidBlueprints(pPlayer)
	local returnBluePrints = {}

	if (pPlayer == nil) then
		return returnBluePrints
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return returnBluePrints
	end

	for i = 1, SceneObject(pInventory):getContainerObjectsSize(), 1 do
		local pObject = SceneObject(pInventory):getContainerObject(i - 1)

		if (pObject ~= nil and SceneObject(pObject):getGameObjectType() == 1073741836) then -- SHIPCHASSIS
			local option = {SceneObject(pObject):getDisplayedName(), SceneObject(pObject):getObjectID()}
			table.insert(returnBluePrints, option)
		end
	end

	return returnBluePrints
end

function ChassisDealer:getPathByName(chassisName)
	local returnString = ""

	foreach(self.ships_table, function(theShip)
		if (string.find(chassisName, theShip.name)) then
			returnString = theShip.blueprint
			return returnString
		end
	end)

	return returnString
end

function ChassisDealer:getChassisFromBlueprint(objectPath)
	local returnString = nil

	foreach(self.ships_table, function(theShip)
		if (theShip.blueprint == objectPath) then
			returnString = theShip.deedObject
		end
	end)

	return returnString
end

function ChassisDealer:checkCertification(pPlayer, chassisName)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return false
	end

	local certificationNeeded = ""

	foreach(self.ships_table, function(theShip)
		if (string.find(chassisName, theShip.name)) then
			certificationNeeded = theShip.certification
		end
	end)

	if (self.CHASSIS_DEBUG) then
		print("Checking for Pilot Certificaition: " .. certificationNeeded)
	end

	if (certificationNeeded == "") then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil or not PlayerObject(pGhost):hasAbility(certificationNeeded)) then
		return false
	end

	return true
end

function ChassisDealer:getShipCost(pPlayer, chassisName)
	local tier = -1
	local isCertified = self:checkCertification(pPlayer, chassisName)

	foreach(self.ships_table, function(theShip)
		if (theShip.name == chassisName) then
			tier = theShip.tier
		end
	end)

	local cost = 10000 + (tier * 5000)

	if (not isCertified) then
		cost = cost * 5
	end

	return cost;
end

function ChassisDealer:checkCost(pPlayer, cost)
	if (pPlayer == nil or cost <= 0) then
		return false
	end

	if (CreatureObject(pPlayer):getCashCredits() < cost) then
		return false
	end

	return true
end

--[[

	Handle Component Sales

]]

function ChassisDealer:getShipComponents(pPlayer)
	local returnComponents = {}

	if (pPlayer == nil) then
		return returnComponents
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return returnComponents
	end

	for i = 1, SceneObject(pInventory):getContainerObjectsSize(), 1 do
		local pObject = SceneObject(pInventory):getContainerObject(i - 1)

		if (pObject ~= nil) then
			--local objectName = SceneObject(pObject):getObjectName()

			--if string.find(objectName, "chassis_token") then
			--	local option = {"@space_crafting_n:" .. objectName, objectName}
			--	table.insert(returnBluePrints, option)
			--end
		end
	end

	return returnComponents
end