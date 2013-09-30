NOJEDIPROGRESSION = 0
HOLOCRONJEDIPROGRESSION = 1
VILLAGEJEDIPROGRESSION = 2
CUSTOMJEDIPROGRESSION = 3

jediProgressionType = HOLOCRONJEDIPROGRESSION

jediManagerName = "JediManager"

function printf(...) io.write(string.format(unpack(arg))) end

Object = {
}

function Object:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

JediManager = Object:new {
	jediManagerName = jediManagerName,
	jediProgressionType = NOJEDIPROGRESSION,
	startingEvent = nil,
}

-- Perform the supplied function with a creature object created from the pointer.
-- @param pCreatureObject a pointer to a creature object.
-- @param performThisFunction a function that takes a creature object as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil.
function JediManager.withCreatureObject(pCreatureObject, performThisFunction)
	if pCreatureObject == nil then
		return nil
	end
	local creatureObject = LuaCreatureObject(pCreatureObject)
	return performThisFunction(creatureObject)
end

-- Perform the supplied function with a player object created from the pointer.
-- @param pPlayerObject a pointer to a player object.
-- @param performThisFunction a function that takes a player object as its argument.
-- @return whatever performThisFunction returns or nil if the pPlayerObject pointer is nil.
function JediManager.withPlayerObject(pPlayerObject, performThisFunction)
	if pPlayerObject == nil then
		return nil
	end
	local playerObject = LuaPlayerObject(pPlayerObject)
	return performThisFunction(playerObject)
end

-- Perform the supplied function with a player object fetched from the creature object pointer.
-- @param pCreatureObject a pointer to a creature object.
-- @param performThisFunction a function that takes a player object as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil or does not have a player object.
function JediManager.withCreaturePlayerObject(pCreatureObject, performThisFunction)
	return JediManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return JediManager.withPlayerObject(creatureObject:getPlayerObject(), performThisFunction)
	end)
end

-- Perform the supplied function with a creature object and a player object fetched from the creature object pointer.
-- @param pCreatureObject a pointer to a creature object.
-- @param performThisFunction a function that takes a creature object and a player object as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil or does not have a player object.
function JediManager.withCreatureAndPlayerObject(pCreatureObject, performThisFunction)
	return JediManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return JediManager.withPlayerObject(creatureObject:getPlayerObject(), function(playerObject)
			return performThisFunction(creatureObject, playerObject)
		end)
	end)
end

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

return JediManager

