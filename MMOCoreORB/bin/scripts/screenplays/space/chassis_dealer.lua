local Logger = require("utils.logger")
require("utils.helpers")


-- Key is ship name, value is blueprint and deed object.
ships = {
	blacksun_heavy_s01 = {blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s01_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s01_deed.iff"},
	blacksun_heavy_s02 = {blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s02_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s02_deed.iff"},
	blacksun_heavy_s03 = {blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s03_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s03_deed.iff"},
	blacksun_heavy_s04 = {blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s04_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s04_deed.iff"}
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

	foreach(ships, function(theShip)
		local pointer = getContainerObjectByTemplate(inventory, theShip.blueprint, true)
		if (pointer ~= nil) then
			local pString = LuaSceneObject(pointer)
			local string = pString:getTemplateObjectPath()
			if (string ~= nil or string ~= "") then
				Logger:log("They have a " .. string, LT_INFO)
				return string
			end
		end
	end)
	
end

function ChassisDealer.getChassisFromBlueprint(pObjectPath)
	foreach(ships, function(theShip)
			local string = theShip.blueprint
			Logger:log("They want a deed from " .. string, LT_INFO)
			if (string == pObjectPath) then
				Logger:log("Generating " .. theShip.deedObject, LT_INFO)
				return theShip.deedObject
			end
	end)
end

return ChassisDealer