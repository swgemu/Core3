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
_localLuaWaypointObject = LuaWaypointObject(nil)

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

WaypointObject = function(pWaypoint)
  if (pWaypoint == nil) then
    return nil
  end

  _localLuaWaypointObject:_setObject(pWaypoint)

  return _localLuaWaypointObject
end
