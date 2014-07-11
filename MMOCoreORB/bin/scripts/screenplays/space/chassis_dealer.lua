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

function ChassisDealer.playerHasValidBlueprints(pCreatureObject)
	if (ChassisDealer.getValidBlueprints(pCreatureObject) ~= "") then
		return true
	elseif (ChassisDealer.getValidBlueprints(pCreatureObject) == "") then
		return false
	end
end

function ChassisDealer.getValidBlueprints(pCreatureObject)

	local creo = LuaSceneObject(pCreatureObject)
	local inventory = creo:getSlottedObject("inventory")
	local returnBluePrints = {}

	foreach(ships, function(theShip)
		local pointer = getContainerObjectByTemplate(inventory, theShip.blueprint, true)
		if (pointer ~= nil) then
			local pString = LuaSceneObject(pointer)
			local string = pString:getCustomObjectName()
			if (string ~= nil or string ~= "") then
				Logger:log("They have a " .. string, LT_INFO)
				table.insert(returnBluePrints, string)
			end
		end
	end)
	
	return returnBluePrints
	
end

function ChassisDealer.getPathByName(pBlueprintObjectName)
	local returnString = nil
	
	foreach(ships, function(theShip)
			local stringOfName = theShip.name
			if (string.find(pBlueprintObjectName, stringOfName) ~= nil) then
				returnString = theShip.blueprint
				Logger:log("Returning " .. returnString, LT_INFO)
			end
	end)
	
	return returnString
	
end

function ChassisDealer.getChassisFromBlueprint(pObjectPath)
	local returnString = nil

	foreach(ships, function(theShip)
			local string = theShip.blueprint
			if (string == pObjectPath) then
				returnString = theShip.deedObject
			end
	end)
	
	return returnString
end

return ChassisDealer