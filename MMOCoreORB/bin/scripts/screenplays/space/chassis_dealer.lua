local Logger = require("utils.logger")
require("utils.helpers")


-- Key is ship name, values are blueprint name, blueprint path, and deed path.
ships = {
    blacksun_light_s01 = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/blacksun_light_s01_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_light_s01_deed.iff"},
    blacksun_light_s02 = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/blacksun_light_s02_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_light_s02_deed.iff"},
    blacksun_light_s03 = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/blacksun_light_s03_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_light_s03_deed.iff"},
    blacksun_light_s04 = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/blacksun_light_s04_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_light_s04_deed.iff"},
    blacksun_medium_s01 = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/blacksun_light_s01_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_light_s01_deed.iff"},
    blacksun_medium_s02 = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/blacksun_light_s02_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_light_s02_deed.iff"},
    blacksun_medium_s03 = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/blacksun_light_s03_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_light_s03_deed.iff"},
    blacksun_medium_s04 = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/blacksun_light_s04_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_light_s04_deed.iff"},
    blacksun_heavy_s01 = {name = "Rihkxyrk Attack Ship Chassis Blueprints, Style 1", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s01_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s01_deed.iff"},
    blacksun_heavy_s02 = {name = "Rihkxyrk Attack Ship Chassis Blueprints, Style 2", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s02_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s02_deed.iff"},
    blacksun_heavy_s03 = {name = "Rihkxyrk Attack Ship Chassis Blueprints, Style 3", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s03_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s03_deed.iff"},
    blacksun_heavy_s04 = {name = "Rihkxyrk Attack Ship Chassis Blueprints, Style 4", blueprint = "object/tangible/ship/components/chassis/blacksun_heavy_s04_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/blacksun_heavy_s04_deed.iff"},
    hutt_light_s01 = {name = "Scyk Light Fighter, Style 1", blueprint = "object/tangible/ship/components/chassis/hutt_light_s01_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/hutt_light_s01_deed.iff"},
    hutt_light_s02 = {name = "Scyk Light Fighter, Style 2", blueprint = "object/tangible/ship/components/chassis/hutt_light_s01_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/hutt_light_s01_deed.iff"},
    hutt_medium_s01 = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/hutt_medium_s01_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/hutt_medium_s01_deed.iff"},
    hutt_medium_s02 = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/hutt_medium_s02_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/hutt_medium_s02_deed.iff"},
    hutt_heavy_s01 = {name = "Kimogila Heavy Fighter, Style 1", blueprint = "object/tangible/ship/components/chassis/hutt_heavy_s01_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/hutt_heavy_s01_deed.iff"},
    hutt_heavy_s02 = {name = "Kimogila Heavy Fighter, Style 2", blueprint = "object/tangible/ship/components/chassis/hutt_heavy_s02_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/hutt_heavy_s02_deed.iff"},


    tiefighter = {name = "TIE Fighter", blueprint = "object/tangible/ship/components/chassis/tiefighter_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/tiefighter_deed.iff"},
    tie_light_duty = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/tie_light_duty_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/tie_light_duty_deed.iff"},
    tie_in = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/tie_in_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/tie_in_deed.iff"},
    tieinterceptor = {name = "TIE Interceptor", blueprint = "object/tangible/ship/components/chassis/tieinterceptor_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/tieinterceptor_deed.iff"},
    tieadvanced = {name = "TIE Advanced", blueprint = "object/tangible/ship/components/chassis/tieadvanced_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/tieadvanced_deed.iff"},
    tieaggressor = {name = "TIE Aggressor", blueprint = "object/tangible/ship/components/chassis/tieaggressor_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/tieaggressor_deed.iff"},
    tiebomber = {name = "TIE Bomber", blueprint = "object/tangible/ship/components/chassis/tiebomber_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/tiebomber_deed.iff"},
    tieoppressor = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/tiebomber_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/tiebomber_deed.iff"},

    awing = {name = "A-Wing", blueprint = "object/tangible/ship/components/chassis/awing_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/awing_deed.iff"},
    bwing = {name = "B-Wing", blueprint = "object/tangible/ship/components/chassis/bwing_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/bwing_deed.iff"},
    xwing = {name = "X-Wing", blueprint = "object/tangible/ship/components/chassis/xwing_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/xwing_deed.iff"},
    ywing_longprobe = {name = "abcd", blueprint = "object/tangible/ship/components/chassis/ywing_longprobe_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/ywing_longprobe_deed.iff"},
    ywing = {name = "Y-Wing", blueprint = "object/tangible/ship/components/chassis/ywing_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/ywing_deed.iff"},
    z95 = {name = "Z95 Headhunter", blueprint = "object/tangible/ship/components/chassis/z95_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/z95_deed.iff"},
    decimator = {name = "Decimnator", blueprint = "object/tangible/ship/components/chassis/decimator_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/decimator_deed.iff"},
    firespray = {name = "KSE Firespray", blueprint = "object/tangible/ship/components/chassis/firespray_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/firespray_deed.iff"},
    ykl37r = {name = "YKL-37R", blueprint = "object/tangible/ship/components/chassis/ykl37r_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/ykl37r_deed.iff"},
    yt1300 = {name = "YT-1300", blueprint = "object/tangible/ship/components/chassis/yt1300_chassis_token.iff", deedObject = "object/tangible/ship/crafted/chassis/yt1300_deed.iff"}
}

ChassisDealer = Object:new {}

function ChassisDealer:playerHasValidBlueprints(pPlayer)
	if (#self:getValidBlueprints(pPlayer) > 0) then
		return true
	end

	return false
end

function ChassisDealer:getValidBlueprintNames(pPlayer)
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



return returnBluePrints
end
function ChassisDealer:getPathByName(objectName)
printf("test");
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
