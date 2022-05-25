CoA3DestroyFacilityTerminal = { }

function CoA3DestroyFacilityTerminal:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	local terminalID = SceneObject(pSceneObject):getObjectID()
	local playerID = SceneObject(pPlayer):getObjectID()
	local coa3TermID = readData(playerID .. ":CoA3:finalTerminal:")

	if (terminalID ~= coa3TermID) then
		return
	end

	local response = LuaObjectMenuResponse(pMenuResponse)

	response:addRadialMenuItem(227, 3, "@self_destruct:self_destruct")
	response:addRadialMenuItemToRadialID(227, 128, 3, "@self_destruct:fifteen")
	response:addRadialMenuItemToRadialID(227, 129, 3, "@self_destruct:thirty")
end

function CoA3DestroyFacilityTerminal:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end

	local terminalID = SceneObject(pSceneObject):getObjectID()

	if (selectedID == 128) then
		CreatureObject(pPlayer):sendSystemMessage("@self_destruct:fifteen_seconds")

		createEvent(15000, "Coa3Screenplay", "destroyFacility", pPlayer, "")
	elseif (selectedID == 129) then
		CreatureObject(pPlayer):sendSystemMessage("@self_destruct:thirty_seconds")

		createEvent(30000, "Coa3Screenplay", "destroyFacility", pPlayer, "")
	end

	return 0
end