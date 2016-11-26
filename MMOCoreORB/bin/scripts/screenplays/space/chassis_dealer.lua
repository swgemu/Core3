local Logger = require("utils.logger")
require("utils.helpers")


-- Key is ship name, values are blueprint name, blueprint path, and deed path.
ships = {
	blacksun_heavy_s01 = {name = "Rihkxyrk Attack Ship Chassis Blueprints, Style 1", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s01_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s01_deed.iff"},
	blacksun_heavy_s02 = {name = "Rihkxyrk Attack Ship Chassis Blueprints, Style 2", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s02_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s02_deed.iff"},
	blacksun_heavy_s03 = {name = "Rihkxyrk Attack Ship Chassis Blueprints, Style 3", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s03_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s03_deed.iff"},
	blacksun_heavy_s04 = {name = "Rihkxyrk Attack Ship Chassis Blueprints, Style 4", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s04_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s04_deed.iff"}
}

ChassisDealer = Object:new {}

function ChassisDealer:playerHasValidBlueprints(pPlayer)
	if (#self:getValidBlueprints(pPlayer) > 0) then
		return true
	end

	return false
end

function ChassisDealer:getValidBlueprints(pPlayer)
	if (pPlayer == nil) then
		return {}
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
	local returnBluePrints = {}

	if (pInventory == nil) then
		return returnBluePrints
	end

	foreach(ships, function(theShip)
		local pObject = getContainerObjectByTemplate(pInventory, theShip.blueprint, true)
		if (pObject ~= nil) then
			local string = SceneObject(pObject):getCustomObjectName()
			if (string ~= nil and string ~= "") then
				local option = {string, 0}
				table.insert(returnBluePrints, option)
			end
		end
	end)

	return returnBluePrints
end

function ChassisDealer:getPathByName(objectName)
	local returnString = nil

	foreach(ships, function(theShip)
		if (string.find(objectName, theShip.name) ~= nil) then
			returnString = theShip.blueprint
		end
	end)

	return returnString
end

function ChassisDealer:getChassisFromBlueprint(objectPath)
	local returnString = nil

	foreach(ships, function(theShip)
		if (theShip.blueprint == objectPath) then
			returnString = theShip.deedObject
		end
	end)

	return returnString
end

return ChassisDealer
