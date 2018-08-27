GeoLabChemicalStorageComponent = {}

function GeoLabChemicalStorageComponent:canAddObject(pContainer, pObj, slot)
	return -1
end

function GeoLabChemicalStorageComponent:transferObject(pContainer, pObj, slot)
	if (pContainer == nil or pObj == nil) then
		return 0
	end

	local pPlayer = GeonosianLab:getObjOwner(pObj)

	if (pPlayer == nil) then
		return 0
	end

	local trapIndex = readData(SceneObject(pContainer):getObjectID() .. ":trapIndex")

	local trapID = readData("geoLab:trapIndex" .. trapIndex)
	local pTrap = getSceneObject(trapID)

	if (pTrap == nil) then
		return 0
	end

	local trapEnabled = readData("geoLab:trapEnabled:" .. trapIndex)

	if (trapEnabled == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/geonosian_madbio:clean") -- The chemicals are already clean.

		return 0
	end

	if (SceneObject(pObj):getTemplateObjectPath() ~= "object/tangible/dungeon/poison_stabilizer.iff") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/geonosian_madbio:too_big") -- That won't fit...

		return 0
	end

	local trapEffectID = readData("geoLab:trapEffect:" .. trapIndex)
	local pTrapEffect = getSceneObject(trapEffectID)

	if (pTrapEffect ~= nil) then
		SceneObject(pTrapEffect):destroyObjectFromWorld()
	end

	CreatureObject(pPlayer):sendSystemMessage("@dungeon/geonosian_madbio:stabilizer") -- The stabilizer mixes with the chemicals, removing the poison, but it looks like it will only be temporary...

	local	pTrapEffect = spawnSceneObject("yavin4", "object/static/particle/pt_miasma_of_fog_gray.iff", SceneObject(pTrap):getPositionX(), SceneObject(pTrap):getPositionZ(), SceneObject(pTrap):getPositionY(), SceneObject(pTrap):getParentID(), 0)

	if pTrapEffect == nil then
		printLuaError("Error spawning GeoLab disabled trap effect for trap index " .. i)
	else
		writeData("geoLab:trapEffect:" .. trapIndex, SceneObject(pTrapEffect):getObjectID())
	end

	deleteData("geoLab:trapEnabled:" .. trapIndex)
	SceneObject(pObj):destroyObjectFromWorld()
	SceneObject(pObj):destroyObjectFromDatabase()

	createEvent(20000, "GeonosianLab", "turnOnTrap", pTrap, "")

	return 1
end
