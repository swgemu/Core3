JediManager = require("managers.jedi.jedi_manager")
require("managers.jedi.village.village_jedi_manager_holocron")
require("managers.jedi.village.old_man_conv_handler")
local Glowing = require("managers.jedi.village.glowing")
local Logger = require("utils.logger")
local SithShadowEncounter = require("managers.jedi.village.sith_shadow_encounter")
local SithShadowIntroTheater = require("managers.jedi.village.sith_shadow_intro_theater")
require("managers.jedi.village.village_jedi_manager_township")

jediManagerName = "VillageJediManager"

NOTINABUILDING = 0

VillageJediManager = JediManager:new {
	screenplayName = jediManagerName,
	jediManagerName = jediManagerName,
	jediProgressionType = VILLAGEJEDIPROGRESSION,
	startingEvent = nil,
}

-- Handling of the useItem event.
-- @param pSceneObject pointer to the item object.
-- @param itemType the type of item that is used.
-- @param pCreatureObject pointer to the creature object that used the item.
function VillageJediManager:useItem(pSceneObject, itemType, pCreatureObject)
	Logger:log("useItem called with item type " .. itemType, LT_INFO)
	if itemType == ITEMHOLOCRON then
		VillageJediManagerHolocron.useHolocron(pSceneObject, pCreatureObject)
	end
	if itemType == ITEMWAYPOINTDATAPAD then
		SithShadowEncounter:useWaypointDatapad(pSceneObject, pCreatureObject)
	end
	if itemType == ITEMTHEATERDATAPAD then
		SithShadowIntroTheater:useTheaterDatapad(pSceneObject, pCreatureObject)
	end
end

-- Handling of the checkForceStatus command.
-- @param pCreatureObject pointer to the creature object of the player who performed the command
function VillageJediManager:checkForceStatusCommand(pCreatureObject)
	Glowing:checkForceStatusCommand(pCreatureObject)
end

-- Handling of the onPlayerLoggedIn event. The progression of the player will be checked and observers will be registered.
-- @param pCreatureObject pointer to the creature object of the player who logged in.
function VillageJediManager:onPlayerLoggedIn(pCreatureObject)
	Glowing:onPlayerLoggedIn(pCreatureObject)
end

registerScreenPlay("VillageJediManager", true)

return VillageJediManager
