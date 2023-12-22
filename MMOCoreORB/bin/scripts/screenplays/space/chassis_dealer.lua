local Logger = require("utils.logger")
require("utils.helpers")

ChassisDealer = ScreenPlay:new {
	CHASSIS_DEBUG = false,

	ships_table = {
		-- Starter Ships
		--{name = "player_basic_z95", certification = "cert_starships_z95headhunter", chassisToken = ""},
		--{name = "player_basic_tiefighter", certification = "cert_starships_tiefighterlight", chassisToken = ""},
		--{name = "player_basic_hutt_light", certification = "cert_starships_lighthuttfighter", chassisToken = ""},
		--{name = "player_sorosuub_space_yacht", certification = "", chassisToken = ""},

		-- Freelance Ships
		{name = "player_blacksun_heavy_s01", certification = "cert_starships_heavyblacksunfighter", chassisToken = "blacksun_heavy_s01_chassis_token"},
		{name = "player_blacksun_heavy_s02", certification = "cert_starships_heavyblacksunfighter", chassisToken = "blacksun_heavy_s02_chassis_token"},
		{name = "player_blacksun_heavy_s03", certification = "cert_starships_heavyblacksunfighter", chassisToken = "blacksun_heavy_s03_chassis_token"},
		{name = "player_blacksun_heavy_s04", certification = "cert_starships_heavyblacksunfighter", chassisToken = "blacksun_heavy_s04_chassis_token"},
		{name = "player_blacksun_light_s01", certification = "cert_starships_lightblacksunfighter", chassisToken = "blacksun_light_s01_chassis_token"},
		{name = "player_blacksun_light_s02", certification = "cert_starships_lightblacksunfighter", chassisToken = "blacksun_light_s02_chassis_token"},
		{name = "player_blacksun_light_s03", certification = "cert_starships_lightblacksunfighter", chassisToken = "blacksun_light_s03_chassis_token"},
		{name = "player_blacksun_light_s04", certification = "cert_starships_lightblacksunfighter", chassisToken = "blacksun_light_s04_chassis_token"},
		{name = "player_blacksun_medium_s01", certification = "cert_starships_mediumblacksunfighter", chassisToken = "blacksun_medium_s01_chassis_token"},
		{name = "player_blacksun_medium_s02", certification = "cert_starships_mediumblacksunfighter", chassisToken = "blacksun_medium_s02_chassis_token"},
		{name = "player_blacksun_medium_s03", certification = "cert_starships_mediumblacksunfighter", chassisToken = "blacksun_medium_s03_chassis_token"},
		{name = "player_blacksun_medium_s04", certification = "cert_starships_mediumblacksunfighter", chassisToken = "blacksun_medium_s04_chassis_token"},
		{name = "player_hutt_heavy_s01", certification = "cert_starships_heavyhuttfighter", chassisToken = "hutt_heavy_s01_chassis_token"},
		{name = "player_hutt_heavy_s02", certification = "cert_starships_heavyhuttfighter", chassisToken = "hutt_heavy_s02_chassis_token"},
		{name = "player_hutt_light_s01", certification = "cert_starships_lighthuttfighter", chassisToken = "hutt_light_chassis_token"},
		{name = "player_hutt_light_s02", certification = "cert_starships_lighthuttfighter", chassisToken = "hutt_light_s02_chassis_token"},
		{name = "player_hutt_medium_s01", certification = "cert_starships_mediumhuttfighter", chassisToken = "hutt_medium_s01_chassis_token"},
		{name = "player_hutt_medium_s02", certification = "cert_starships_mediumhuttfighter", chassisToken = "hutt_medium_s02_chassis_token"},
		{name = "player_hutt_turret_ship", certification = "cert_starships_hutt_turret_ship", chassisToken = "hutt_turret_ship_chassis_token"},
		--{name = "player_prototype_hutt_light", certification = "cert_starships_lighthuttfighter", chassisToken = "hutt_light_chassis_token"},
		{name = "player_yt1300", certification = "cert_starships_yt1300", chassisToken = "yt1300_chassis_token"},
		{name = "player_yt1300_decorated_01", certification = "cert_starships_yt1300", chassisToken = ""},

		-- Rebel Ships
		{name = "player_awing", certification = "cert_starships_awing", chassisToken = "awing_chassis_token"},
		{name = "player_bwing", certification = "cert_starships_bwing", chassisToken = "bwing_chassis_token"},
		--{name = "player_prototype_z95", certification = "cert_starships_z95headhunter", chassisToken = "z95_chassis_token"},
		{name = "player_xwing", certification = "cert_starships_xwing", chassisToken = "xwing_chassis_token"},
		{name = "player_ykl37r", certification = "cert_starships_ykl37r", chassisToken = "ykl37r_chassis_token"},
		{name = "player_ywing", certification = "cert_starships_ywing", chassisToken = "ywing_chassis_token"},
		{name = "player_ywing_longprobe", certification = "cert_starships_ywinglongprobe", chassisToken = "ywing_longprobe_chassis_token"},
		{name = "player_z95", certification = "cert_starships_z95headhunter", chassisToken = "z95_chassis_token"},

		-- Imperial Ships
		{name = "player_decimator", certification = "cert_starships_decimator", chassisToken = "decimator_chassis_token"},
		--{name = "player_prototype_tiefighter", certification = "cert_starships_tiefighterlight", chassisToken = ""},
		{name = "player_tie_in", certification = "cert_starships_tiefighterin", chassisToken = "tie_in_chassis_token"},
		{name = "player_tie_light_duty", certification = "cert_starships_tiefighterlight", chassisToken = "tie_light_duty_chassis_token"},
		{name = "player_tieadvanced", certification = "cert_starships_tieadvanced", chassisToken = "tieadvanced_chassis_token"},
		{name = "player_tieaggressor", certification = "cert_starships_tieaggressor", chassisToken = "tieaggressor_chassis_token"},
		{name = "player_tiebomber", certification = "cert_starships_tiebomber", chassisToken = "tiebomber_chassis_token"},
		{name = "player_tiefighter", certification = "cert_starships_tiefighter", chassisToken = "tiefighter_chassis_token"},
		{name = "player_tieinterceptor", certification = "cert_starships_tieinterceptor", chassisToken = "tieinterceptor_chassis_token"},
		{name = "player_tieoppressor", certification = "cert_starships_tieoppressor", chassisToken = "tieoppressor_chassis_token"},

		-- Special Ships
		{name = "player_firespray", certification = "cert_starships_firespray", chassisToken = "firespray_chassis_token"},
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
		if (string.find(theShip.chassisToken, chassisName)) then
			certificationNeeded = theShip.certification
		end
	end)

	if (self.CHASSIS_DEBUG) then
		print("Checking for Pilot Certificaition for Chassis: " .. chassisName .. " Cert: " .. certificationNeeded)
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