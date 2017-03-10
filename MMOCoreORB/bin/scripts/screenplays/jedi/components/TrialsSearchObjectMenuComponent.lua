TrialsSearchObjectMenuComponent = {}

function TrialsSearchObjectMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	local trialOwnerID = readData(SceneObject(pSceneObject):getObjectID() .. ":ownerID")
	local playerID = SceneObject(pPlayer):getObjectID()

	if (trialOwnerID == playerID) then
		menuResponse:addRadialMenuItem(120, 3, "@bestine:search_item") -- Search
	end
end

function TrialsSearchObjectMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	local trialOwnerID = readData(SceneObject(pObject):getObjectID() .. ":ownerID")
	local playerID = SceneObject(pPlayer):getObjectID()
	local objectID = SceneObject(pObject):getObjectID()

	if (trialOwnerID ~= playerID or selectedID ~= 120) then
		return 0
	end
	
	if (readData(objectID .. ":JediTrials:objectSearched") == 1) then
		CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:already_searched")
		return 0
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:successful_search_msg")
	writeData(objectID .. ":JediTrials:objectSearched", 1)
	writeData(playerID .. ":JediTrials:spokeToTarget01", 1)
	PadawanTrials:createMainLocation(pPlayer)

	return 0
end
