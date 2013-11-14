JediManager = require("managers.jedi.jedi_manager")
require("managers.jedi.village.village_jedi_manager_holocron")
require("managers.jedi.village.old_man_conv_handler")
local Glowing = require("managers.jedi.village.glowing")

jediManagerName = "VillageJediManager"

NOTINABUILDING = 0

VillageJediManager = JediManager:new {
	screenplayName = jediManagerName,
	jediManagerName = jediManagerName,
	jediProgressionType = VILLAGEJEDIPROGRESSION,
	startingEvent = nil,
}

-- Handling of the useHolocron event.
-- @param pSceneObject pointer to the holocron object.
-- @param pCreatureObject pointer to the creature object that used the holocron.
function VillageJediManager:useHolocron(pSceneObject, pCreatureObject)
	VillageJediManagerHolocron.useHolocron(pSceneObject, pCreatureObject)
end

-- Handling of the checkForceStatus command.
-- @param pCreatureObject pointer to the creature object of the player who performed the command
function VillageJediManager:checkForceStatusCommand(pCreatureObject)
	Glowing.checkForceStatusCommand(pCreatureObject)
end

-- Handling of the onPlayerLoggedIn event. The progression of the player will be checked and observers will be registered.
-- @param pCreatureObject pointer to the creature object of the player who logged in.
function VillageJediManager:onPlayerLoggedIn(pCreatureObject)
	Glowing.onPlayerLoggedIn(pCreatureObject)
end

registerScreenPlay("VillageJediManager", true)

return VillageJediManager
