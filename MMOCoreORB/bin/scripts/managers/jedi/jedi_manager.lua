JediManager = require("screenplays.screenplay")

if _TEST then
	NOJEDIPROGRESSION = 0
	HOLOGRINDJEDIPROGRESSION = 1
	VILLAGEJEDIPROGRESSION = 2
	CUSTOMJEDIPROGRESSION = 3

	ITEMHOLOCRON = 0
	ITEMWAYPOINTDATAPAD = 1
	ITEMTHEATERDATAPAD = 2
end

jediProgressionType = VILLAGEJEDIPROGRESSION

jediManagerName = "JediManager"

customJediProgressionFile = "scripts/managers/jedi/custom_jedi_manager.lua"

function printf(...) io.write(string.format(table.unpack({...}))) end

JediManager = ScreenPlay:new {
	screenplayName = jediManagerName,
	jediManagerName = jediManagerName,
	jediProgressionType = NOJEDIPROGRESSION,
}

-- Default handling of the start event.
function JediManager:start()
	-- Default behaviour for the start event, do nothing.
end

-- Default handling of the onPlayerCreated event.
-- @param pCreatureObject pointer to the creature object for the player that was created.
function JediManager:onPlayerCreated(pCreatureObject)
	-- Default behaviour for the onPlayerCreated event, do nothing.
end

-- Default handling of the onPlayerLoggedIn event.
-- @param pCreatureObject pointer to the creature object for the player that logged in.
function JediManager:onPlayerLoggedIn(pCreatureObject)
	-- Default behaviour for the onPlayerLoggedIn event, do nothing.
end

-- Default handling of the onPlayerLoggedOut event.
-- @param pCreatureObject pointer to the creature object for the player that logged out.
function JediManager:onPlayerLoggedOut(pCreatureObject)
	-- Default behaviour for the onPlayerLoggedOut event, do nothing.
end

-- Default handling of the checkForceStatus command.
-- @param pCreatureObject pointer to the creature object for the player that performed the command.
function JediManager:checkForceStatusCommand(pCreatureObject)
	-- Default behaviour for the checkForceStatus command, do nothing.
end

-- Default handling of the onSkillRevoked event.
-- @param pCreatureObject pointer to the creature object that revoked a skill
-- @param pSkill skill that was revoked
function JediManager:onSkillRevoked(pCreatureObject, pSkill)
	-- Default behaviour for the onPlayerLoggedOut event, do nothing.
end

-- Default handling of the useItem event.
-- @param pSceneObject pointer to the item object.
-- @param itemType the type of item that is used.
-- @param pCreatureObject pointer to the creature object that used the item.
function JediManager:useItem(pSceneObject, itemType, pCreatureObject)
	-- Default behaviour for the useItem event, do nothing.
end

--Check for force skill prerequisites
function JediManager:canLearnSkill(pPlayer, skillName)
	-- Default behaviour for the canLearnSkill check, return false.
	return false
end

--Check to ensure force skill prerequisites are maintained
function JediManager:canSurrenderSkill(pPlayer, skillName)
	-- Default behaviour for the canSurrenderSkill check, return true.
	return true
end

function JediManager:onFSTreeCompleted(pCreatureObject, branch)
	-- Default behaviour for the onFSTreesCompleted event, do nothing.
end

return JediManager

