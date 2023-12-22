local Logger = require("utils.logger")
require("utils.helpers")

ChassisDealer = ScreenPlay:new {
	CHASSIS_DEBUG = false,

	--{name = "", certification = ""},

	ships_table = {
		-- Starter Ships
		{name = "player_basic_z95", certification = "cert_starships_z95headhunter"},
		{name = "player_basic_tiefighter", certification = "cert_starships_tiefighterlight"},
		{name = "player_basic_hutt_light", certification = "cert_starships_lighthuttfighter"},
		{name = "player_sorosuub_space_yacht", certification = ""},

		-- Freelance Ships
		{name = "player_blacksun_heavy_s01", certification = "cert_starships_heavyblacksunfighter"},
		{name = "player_blacksun_heavy_s02", certification = "cert_starships_heavyblacksunfighter"},
		{name = "player_blacksun_heavy_s03", certification = "cert_starships_heavyblacksunfighter"},
		{name = "player_blacksun_heavy_s04", certification = "cert_starships_heavyblacksunfighter"},
		{name = "player_blacksun_light_s01", certification = "cert_starships_lightblacksunfighter"},
		{name = "player_blacksun_light_s02", certification = "cert_starships_lightblacksunfighter"},
		{name = "player_blacksun_light_s03", certification = "cert_starships_lightblacksunfighter"},
		{name = "player_blacksun_light_s04", certification = "cert_starships_lightblacksunfighter"},
		{name = "player_blacksun_medium_s01", certification = "cert_starships_mediumblacksunfighter"},
		{name = "player_blacksun_medium_s02", certification = "cert_starships_mediumblacksunfighter"},
		{name = "player_blacksun_medium_s03", certification = "cert_starships_mediumblacksunfighter"},
		{name = "player_blacksun_medium_s04", certification = "cert_starships_mediumblacksunfighter"},
		{name = "player_firespray", certification = "cert_starships_firespray"},
		{name = "player_hutt_heavy_s01", certification = "cert_starships_heavyhuttfighter"},
		{name = "player_hutt_heavy_s02", certification = "cert_starships_heavyhuttfighter"},
		{name = "player_hutt_light_s01", certification = "cert_starships_lighthuttfighter"},
		{name = "player_hutt_light_s02", certification = "cert_starships_lighthuttfighter"},
		{name = "player_hutt_medium_s01", certification = "cert_starships_mediumhuttfighter"},
		{name = "player_hutt_medium_s02", certification = "cert_starships_mediumhuttfighter"},
		{name = "player_hutt_turret_ship", certification = "cert_starships_hutt_turret_ship"},
		{name = "player_prototype_hutt_light", certification = "cert_starships_lighthuttfighter"},
		{name = "player_yt1300", certification = "cert_starships_yt1300"},
		{name = "player_yt1300_decorated_01", certification = "cert_starships_yt1300"},

		-- Rebel Ships
		{name = "player_awing", certification = "cert_starships_awing"},
		{name = "player_bwing", certification = "cert_starships_bwing"},
		{name = "player_prototype_z95", certification = "cert_starships_z95headhunter"},
		{name = "player_xwing", certification = "cert_starships_xwing"},
		{name = "player_ykl37r", certification = "cert_starships_ykl37r"},
		{name = "player_ywing", certification = "cert_starships_ywing"},
		{name = "player_ywing_longprobe", certification = "cert_starships_ywinglongprobe"},
		{name = "player_z95", certification = "cert_starships_z95headhunter"},

		-- Imperial Ships
		{name = "player_decimator", certification = "cert_starships_decimator"},
		{name = "player_prototype_tiefighter", certification = "cert_starships_tiefighterlight"},
		{name = "player_tie_in", certification = "cert_starships_tiefighterin"},
		{name = "player_tie_light_duty", certification = "cert_starships_tiefighterlight"},
		{name = "player_tieadvanced", certification = "cert_starships_tieadvanced"},
		{name = "player_tieaggressor", certification = "cert_starships_tieadvanced"},
		{name = "player_tiebomber", certification = "cert_starships_tiebomber"},
		{name = "player_tiefighter", certification = "cert_starships_tiefighter"},
		{name = "player_tieinterceptor", certification = "cert_starships_tieinterceptor"},
		{name = "player_tieoppressor", certification = "cert_starships_tieoppressor"},
	},
}

registerScreenPlay("ChassisDealer", false)

--[[

	Handle Ship Chassis

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
		return true
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil or not PlayerObject(pGhost):hasAbility(certificationNeeded)) then
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