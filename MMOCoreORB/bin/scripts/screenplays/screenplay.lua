function printf(...) io.write(string.format(unpack(arg))) end

function writeData(key, data)
	writeSharedMemory(string.format(key), data)
end

function writeStringData(key, data)
	writeStringSharedMemory(string.format(key), string.format(data))
end

function deleteData(key)
	deleteSharedMemory(string.format(key))
end

function deleteStringData(key)
	deleteStringSharedMemory(string.format(key))
end

function readData(key)
	return readSharedMemory(string.format(key))
end

function readStringData(key)
	return readStringSharedMemory(string.format(key))
end

Object = {
}

-- for creation of new instances
function Object:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

ScreenPlay = Object:new {
	screenplayName = "",
	numerOfActs = 0,
	startingEvent = nil,

	lootContainers = {},
	lootLevel = 0,
	lootGroups = {},
	lootContainerRespawn = 1800 -- 30 minutes
}

function ScreenPlay:initializeLootContainers()
	for k,v in pairs(self.lootContainers) do
		local pContainer = getSceneObject(v)
		if (pContainer ~= nil) then
			createObserver(OPENCONTAINER, self.screenplayName, "spawnContainerLoot", pContainer)
			self:spawnContainerLoot(pContainer)

			local container = LuaSceneObject(pContainer)
			container:setContainerDefaultAllowPermission(MOVEOUT + OPEN)
			container:setContainerComponent("PlaceableLootContainerComponent")
		end
	end
end

function ScreenPlay:spawnContainerLoot(pContainer)
	local container = LuaSceneObject(pContainer)
	local time = getTimestamp()

	if (readData(container:getObjectID()) > time) then
		return
	end

	--If it has loot already, then exit.
	if (container:getContainerObjectsSize() > 0) then
		return
	end

	createLootFromCollection(pContainer, self.lootGroups, self.lootLevel)

	writeData(container:getObjectID(), time + self.lootContainerRespawn)
end

-- Perform the supplied function with an ai agent created from the pointer.
-- @param pCreatureObject a pointer to a creature object that is an AiAgent.
-- @param performThisFunction a function that takes an ai agent as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil.
function ScreenPlay.withCreatureAiAgent(pCreatureObject, performThisFunction)
	if pCreatureObject == nil then
		return nil
	end
	local aiAgent = LuaAiAgent(pCreatureObject)
	return performThisFunction(aiAgent)
end

-- Perform the supplied function with a scene object created from the pointer.
-- @param pSceneObject a pointer to a scene object.
-- @param performThisFunction a function that takes a scene object as its argument.
-- @return whatever performThisFunction returns or nil if the pSceneObject pointer is nil.
function ScreenPlay.withSceneObject(pSceneObject, performThisFunction)
	if pSceneObject == nil then
		return nil
	end
	local sceneObject = LuaSceneObject(pSceneObject)
	return performThisFunction(sceneObject)
end

-- Perform the supplied function with a creature object created from the pointer.
-- @param pCreatureObject a pointer to a creature object.
-- @param performThisFunction a function that takes a creature object as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil.
function ScreenPlay.withCreatureObject(pCreatureObject, performThisFunction)
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
function ScreenPlay.withPlayerObject(pPlayerObject, performThisFunction)
	if pPlayerObject == nil then
		return nil
	end
	local playerObject = LuaPlayerObject(pPlayerObject)
	return performThisFunction(playerObject)
end

-- Perform the supplied function with a city region created from the pointer.
-- @param pCityRegion a pointer to a city region.
-- @param performThisFunction a function that takes a city region as its argument.
-- @return whatever performThisFunction returns or nil if the pCityRegion pointer is nil.
function ScreenPlay.withCityRegion(pCityRegion, performThisFunction)
	if pCityRegion == nil then
		return nil
	end
	local cityRegion = LuaCityRegion(pCityRegion)
	return performThisFunction(cityRegion)
end

-- Perform the supplied function with a player object fetched from the creature object pointer.
-- @param pCreatureObject a pointer to a creature object.
-- @param performThisFunction a function that takes a player object as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil or does not have a player object.
function ScreenPlay.withCreaturePlayerObject(pCreatureObject, performThisFunction)
	return ScreenPlay.withCreatureObject(pCreatureObject, function(creatureObject)
		return ScreenPlay.withPlayerObject(creatureObject:getPlayerObject(), performThisFunction)
	end)
end

-- Perform the supplied function with a creature object and a player object fetched from the creature object pointer.
-- @param pCreatureObject a pointer to a creature object.
-- @param performThisFunction a function that takes a creature object and a player object as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil or does not have a player object.
function ScreenPlay.withCreatureAndPlayerObject(pCreatureObject, performThisFunction)
	return ScreenPlay.withCreatureObject(pCreatureObject, function(creatureObject)
		return ScreenPlay.withPlayerObject(creatureObject:getPlayerObject(), function(playerObject)
			return performThisFunction(creatureObject, playerObject)
		end)
	end)
end

Act = Object:new {

}

return ScreenPlay
