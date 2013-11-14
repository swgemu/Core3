JediManager = require("screenplays.screenplay")

NOJEDIPROGRESSION = 0
HOLOGRINDJEDIPROGRESSION = 1
VILLAGEJEDIPROGRESSION = 2
CUSTOMJEDIPROGRESSION = 3

jediProgressionType = VILLAGEJEDIPROGRESSION

jediManagerName = "JediManager"

customJediProgressionFile = "scripts/managers/jedi/custom_jedi_manager.lua"

function printf(...) io.write(string.format(unpack(arg))) end

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

-- Default handling of the useHolocron event.
-- @param pSceneObject pointer to the holocron object.
-- @param pCreatureObject pointer to the creature object that used the holocron.
function JediManager:useHolocron(pSceneObject, pCreatureObject)
	-- Default behaviour for the useHolocron event, do nothing.
end

return JediManager

