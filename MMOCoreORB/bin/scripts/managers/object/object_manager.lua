Object = {}

-- for creation of new instances
function Object:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

_localLuaAiAgent = LuaAiAgent(nil)
_localLuaAiAgent1 = LuaAiAgent(nil)
_localLuaAiAgent2 = LuaAiAgent(nil)
_localLuaAiAgent3 = LuaAiAgent(nil)

_localLuaSceneObject = LuaSceneObject(nil)
_localLuaSceneObject1 = LuaSceneObject(nil)
_localLuaSceneObject2 = LuaSceneObject(nil)
_localLuaSceneObject3 = LuaSceneObject(nil)

_localLuaTangibleObject = LuaTangibleObject(nil)
_localLuaTangibleObject1 = LuaTangibleObject(nil)
_localLuaTangibleObject2 = LuaTangibleObject(nil)
_localLuaTangibleObject3 = LuaTangibleObject(nil)

_localLuaCreatureObject = LuaCreatureObject(nil)
_localLuaCreatureObject1 = LuaCreatureObject(nil)
_localLuaCreatureObject2 = LuaCreatureObject(nil)
_localLuaCreatureObject3 = LuaCreatureObject(nil)

_localLuaPlayerObject = LuaPlayerObject(nil)
_localLuaBuildingObject = LuaBuildingObject(nil)
_localLuaCityRegion = LuaCityRegion(nil)
_localLuaActiveArea = LuaActiveArea(nil)

AiAgent = function(pAiAgent)
  if (pAiAgent == nil) then
    return nil
  end

  _localLuaAiAgent:_setObject(pAiAgent)

  return _localLuaAiAgent
end

AiAgent1 = function(pAiAgent)
  if (pAiAgent == nil) then
    return nil
  end

  _localLuaAiAgent1:_setObject(pAiAgent)

  return _localLuaAiAgent1
end

AiAgent2 = function(pAiAgent)
  if (pAiAgent == nil) then
    return nil
  end

  _localLuaAiAgent2:_setObject(pAiAgent)

  return _localLuaAiAgent2
end

AiAgent3 = function(pAiAgent)
  if (pAiAgent == nil) then
    return nil
  end

  _localLuaAiAgent3:_setObject(pAiAgent)

  return _localLuaAiAgent3
end


SceneObject = function(pSceneObject)
  if (pSceneObject == nil) then
    return nil
  end

  _localLuaSceneObject:_setObject(pSceneObject)

  return _localLuaSceneObject
end

SceneObject1 = function(pSceneObject)
  if (pSceneObject == nil) then
    return nil
  end

  _localLuaSceneObject1:_setObject(pSceneObject)

  return _localLuaSceneObject1
end

SceneObject2 = function(pSceneObject)
  if (pSceneObject == nil) then
    return nil
  end

  _localLuaSceneObject2:_setObject(pSceneObject)

  return _localLuaSceneObject2
end

SceneObject3 = function(pSceneObject)
  if (pSceneObject == nil) then
    return nil
  end

  _localLuaSceneObject3:_setObject(pSceneObject)

  return _localLuaSceneObject3
end

TangibleObject = function(pTangibleObject)
  if (pTangibleObject == nil) then
    return nil
  end

  _localLuaTangibleObject:_setObject(pTangibleObject)

  return _localLuaTangibleObject
end

TangibleObject1 = function(pTangibleObject)
  if (pTangibleObject == nil) then
    return nil
  end

  _localLuaTangibleObject1:_setObject(pTangibleObject)

  return _localLuaTangibleObject1
end

TangibleObject2 = function(pTangibleObject)
  if (pTangibleObject == nil) then
    return nil
  end

  _localLuaTangibleObject2:_setObject(pTangibleObject)

  return _localLuaTangibleObject2
end

TangibleObject3 = function(pTangibleObject)
  if (pTangibleObject == nil) then
    return nil
  end

  _localLuaTangibleObject3:_setObject(pTangibleObject)

  return _localLuaTangibleObject3
end

CreatureObject = function(pCreatureObject)
  if (pCreatureObject == nil) then
    return nil
  end

  _localLuaCreatureObject:_setObject(pCreatureObject)

  return _localLuaCreatureObject
end

CreatureObject1 = function(pCreatureObject)
  if (pCreatureObject == nil) then
    return nil
  end

  _localLuaCreatureObject1:_setObject(pCreatureObject)

  return _localLuaCreatureObject1
end

CreatureObject2 = function(pCreatureObject)
  if (pCreatureObject == nil) then
    return nil
  end

  _localLuaCreatureObject2:_setObject(pCreatureObject)

  return _localLuaCreatureObject2
end

CreatureObject3 = function(pCreatureObject)
  if (pCreatureObject == nil) then
    return nil
  end

  _localLuaCreatureObject3:_setObject(pCreatureObject)

  return _localLuaCreatureObject3
end

PlayerObject = function(pPlayerObject)
  if (pPlayerObject == nil) then
    return nil
  end

  _localLuaPlayerObject:_setObject(pPlayerObject)

  return _localLuaPlayerObject
end

BuildingObject = function(pBuildingObject)
  if (pBuildingObject == nil) then
    return nil
  end

  _localLuaBuildingObject:_setObject(pBuildingObject)

  return _localLuaBuildingObject
end

CityRegion = function(pCityRegion)
  if (pCityRegion == nil) then
    return nil
  end

  _localLuaCityRegion:_setObject(pCityRegion)

  return _localLuaCityRegion
end

ActiveArea = function(pActiveArea)
  if (pActiveArea == nil) then
    return nil
  end

  _localLuaActiveArea:_setObject(pActiveArea)

  return _localLuaActiveArea
end

local ObjectManager = Object:new {}

-- Perform the supplied function with an ai agent created from the pointer.
-- @param pCreatureObject a pointer to a creature object that is an AiAgent.
-- @param performThisFunction a function that takes an ai agent as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil.
function ObjectManager.withCreatureAiAgent(pCreatureObject, performThisFunction)
	if pCreatureObject == nil then
		return nil
	end

	local previousPointer = _localLuaAiAgent:_getObject()

	local ret = performThisFunction(AiAgent(pCreatureObject))

	_localLuaAiAgent:_setObject(previousPointer)

	return ret
end

-- Perform the supplied function with a scene object created from the pointer.
-- @param pSceneObject a pointer to a scene object.
-- @param performThisFunction a function that takes a scene object as its argument.
-- @return whatever performThisFunction returns or nil if the pSceneObject pointer is nil.
function ObjectManager.withSceneObject(pSceneObject, performThisFunction)
	if pSceneObject == nil then
		return nil
	end

	local previousPointer = _localLuaSceneObject:_getObject()

	local ret = performThisFunction(SceneObject(pSceneObject))

	_localLuaSceneObject:_setObject(previousPointer)

	return ret
end

-- Perform the supplied function with a tangible object created from the pointer.
-- @param pTangibleObject a pointer to a scene object.
-- @param performThisFunction a function that takes a tangible object as its argument.
-- @return whatever performThisFunction returns or nil if the pTangibleObject pointer is nil.
function ObjectManager.withTangibleObject(pTangibleObject, performThisFunction)
	if pTangibleObject == nil then
		return nil
	end

	local previousPointer = _localLuaTangibleObject:_getObject()

	local ret = performThisFunction(TangibleObject(pTangibleObject))

	_localLuaTangibleObject:_setObject(previousPointer)

	return ret
end

-- Perform the supplied function with a creature object created from the pointer.
-- @param pCreatureObject a pointer to a creature object.
-- @param performThisFunction a function that takes a creature object as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil.
function ObjectManager.withCreatureObject(pCreatureObject, performThisFunction)
	if pCreatureObject == nil then
		return nil
	end

	local previousPointer = _localLuaCreatureObject:_getObject()

	local ret = performThisFunction(CreatureObject(pCreatureObject))

	_localLuaCreatureObject:_setObject(previousPointer)

	return ret
end

-- Perform the supplied function with a player object created from the pointer.
-- @param pPlayerObject a pointer to a player object.
-- @param performThisFunction a function that takes a player object as its argument.
-- @return whatever performThisFunction returns or nil if the pPlayerObject pointer is nil.
function ObjectManager.withPlayerObject(pPlayerObject, performThisFunction)
	if pPlayerObject == nil then
		return nil
	end

  	local previousPointer = _localLuaPlayerObject:_getObject()

	local ret = performThisFunction(PlayerObject(pPlayerObject))

	_localLuaPlayerObject:_setObject(previousPointer)

	return ret
end

-- Perform the supplied function with a building object created from the pointer.
-- @param pBuildingObject a pointer to a building object.
-- @param performThisFunction a function that takes a building object as its argument.
-- @return whatever performThisFunction returns or nil if the pBuildingObject pointer is nil.
function ObjectManager.withBuildingObject(pBuildingObject, performThisFunction)
	if pBuildingObject == nil then
		return nil
	end

  local previousPointer = _localLuaBuildingObject:_getObject()

  local ret = performThisFunction(BuildingObject(pBuildingObject))

  _localLuaBuildingObject:_setObject(previousPointer)

  return ret
end

-- Perform the supplied function with a city region created from the pointer.
-- @param pCityRegion a pointer to a city region.
-- @param performThisFunction a function that takes a city region as its argument.
-- @return whatever performThisFunction returns or nil if the pCityRegion pointer is nil.
function ObjectManager.withCityRegion(pCityRegion, performThisFunction)
	if pCityRegion == nil then
		return nil
	end

  	local previousPointer = _localLuaCityRegion:_getObject()

	local ret = performThisFunction(CityRegion(pCityRegion))

	_localLuaCityRegion:_setObject(previousPointer)

	return ret
end

-- Perform the supplied function with a player object fetched from the creature object pointer.
-- @param pCreatureObject a pointer to a creature object.
-- @param performThisFunction a function that takes a player object as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil or does not have a player object.
function ObjectManager.withCreaturePlayerObject(pCreatureObject, performThisFunction)
	return ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return ObjectManager.withPlayerObject(creatureObject:getPlayerObject(), performThisFunction)
	end)
end

-- Perform the supplied function with a creature object and a player object fetched from the creature object pointer.
-- @param pCreatureObject a pointer to a creature object.
-- @param performThisFunction a function that takes a creature object and a player object as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil or does not have a player object.
function ObjectManager.withCreatureAndPlayerObject(pCreatureObject, performThisFunction)
	return ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return ObjectManager.withPlayerObject(creatureObject:getPlayerObject(), function(playerObject)
			return performThisFunction(creatureObject, playerObject)
		end)
	end)
end

-- Perform the supplied function with the inventory pointer from the pointer to the creature object.
-- @param pCreatureObject a pointer to a creature object.
-- @param performThisFunction a function that takes a pointer to an inventory as its argument.
-- @return whatever performThisFunction returns or nil if the pCreatureObject pointer is nil or does not have an inventory.
function ObjectManager.withInventoryPointer(pCreatureObject, performThisFunction)
	return ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		local pInventory = creatureObject:getSlottedObject("inventory")

		if pInventory ~= nil then
			return performThisFunction(pInventory)
		else
			return nil
		end
	end)
end

-- Perform the supplied function with a scene object with the supplied object id.
-- @param objectId the object id of the scene object to send to the function.
-- @param performThisFunction a function that takes a scene object as argument.
-- @return whatever performThisFunction returns or nil if no object with the specified id can be found.
function ObjectManager.withSceneObjectFromId(objectId, performThisFunction)
	return ObjectManager.withSceneObject(getSceneObject(objectId), performThisFunction)
end

-- Perform the supplied function with an active area.
-- @param pActiveArea pointer to the active area.
-- @param performThisFunction a function that takes an active area as argument.
-- @return whatever performThisFunction returns or nil if the pActiveArea is nil.
function ObjectManager.withActiveArea(pActiveArea, performThisFunction)
	if pActiveArea == nil then
		return nil
	end

  	local previousPointer = _localLuaActiveArea:_getObject()

	local ret = performThisFunction(ActiveArea(pActiveArea))

	_localLuaActiveArea:_setObject(previousPointer)

	return ret
end

return ObjectManager
