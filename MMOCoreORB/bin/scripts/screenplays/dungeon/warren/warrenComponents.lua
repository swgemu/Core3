WarrenQuestContainerMenuComponent = {}

function WarrenQuestContainerMenuComponent:transferObject(pContainer, pObj, slot)
	return -1
end

function WarrenQuestContainerMenuComponent:canAddObject(pContainer, pObj, slot)
	return -1
end

function WarrenQuestContainerMenuComponent:removeObject(pContainer, pObj, slot)
	if (pContainer ~= nil) then
		createEvent(1800 * 1000, "Warren", "refillContainer", pContainer, "")
	end
	
	return -1
end

WarrenEvidenceMenuComponent = {}

function WarrenEvidenceMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) then
		return
	end

	local evidenceName = ""
	local containerID = SceneObject(pSceneObject):getObjectID()

	for i = 1, #Warren.evidenceContainers, 1 do
		local evidenceData = #Warren.evidenceContainers[i]

		if (evidenceData[1] == containerID) then
			evidenceName = terminalData[2]
		end
	end

	local radialMsg = "@theme_park/warren/warren_system_messages:get_evidence"

	if (evidenceName == "warren_encryption_key") then
		radialMsg = "@theme_park/warren/warren_system_messages:mnu_download"
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3, radialMsg)
end

function WarrenEvidenceMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return 0
	end

	local pDatapad = CreatureObject(pPlayer):getSlottedObject("datapad")

	if (pDatapad == nil) then
		return 0
	end

	local evidenceName = ""
	local containerID = SceneObject(pSceneObject):getObjectID()

	for i = 1, #Warren.evidenceContainers, 1 do
		local evidenceData = #Warren.evidenceContainers[i]

		if (evidenceData[1] == containerID) then
			evidenceName = terminalData[2]
		end
	end

	local evidenceTemplate = "object/intangible/data_item/" .. evidenceName .. ".iff"

	local pEvidence = getContainerObjectByTemplate(pDatapad, evidenceTemplate, false)

	if (pEvidence ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/warren/warren_system_messages:got_evidence") --You have already downloaded evidence from this terminal
		return 0
	end

	local pItem = giveItem(pDatapad, evidenceTemplate, -1)

	if (pItem ~= nil) then
		SceneObject(pItem):setContainerInheritPermissionsFromParent(false)
		SceneObject(pItem):clearContainerDefaultDenyPermission(MOVECONTAINER)
		SceneObject(pItem):setContainerDefaultAllowPermission(MOVECONTAINER)

		local sui = SuiMessageBox.new("Warren", "noCallback")
		sui.setTitle("@sui:swg")
		sui.setPrompt("@theme_park/warren/warren_system_messages:download_complete")
		sui.setTargetNetworkId(SceneObject(pTerminal):getObjectID())
		sui.setForceCloseDistance(5)
		sui.sendTo(pPlayer)
	end

	return 0
end

WarrenElevatorMenuComponent = {}

function WarrenElevatorMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(199, 3, "@elevator_text:down")
end

function WarrenElevatorMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil) then
		return 0
	end

	if (selectedID ~= 199) then
		return 0
	end

	if (CreatureObject(pPlayer):getParent() ~= SceneObject(pSceneObject):getParent() or not CreatureObject(pPlayer):isInRangeWithObject(pSceneObject, 3)) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/warren/warren_system_messages:elev_range") -- You are too far away to use that
		return 0
	end

	local securityActive = false

	for i = 1, 4, 1 do
		local terminalDisabled = readData("warren:mcrTerminalDisabled" .. i)

		if (terminalDisabled == 0) then
			securityActive = true
		end
	end

	if (securityActive) then
		SceneObject(pSceneObject):showFlyText("theme_park/warren/warren_system_messages", "elev_one_secure", 0, 255, 0)
		return 0
	end

	local z = SceneObject(pSceneObject):getPositionZ() - 20
	local x = CreatureObject(pPlayer):getPositionX()
	local y = CreatureObject(pPlayer):getPositionY()

	CreatureObject(pPlayer):playEffect("clienteffect", "elevator_descend.cef")
	CreatureObject(pPlayer):teleport(x, z, y, SceneObject(pSceneObject):getParentID())
	return 0
end

WarrenRoomComponent = {}

function WarrenRoomComponent:transferObject(pContainer, pObj, slot)
	if (pObj == nil or not SceneObject(pObj):isPlayerCreature()) then
		return -1
	end

	local pWarren = Warren:getBuildingObject()

	if (pWarren == nil) then
		return -1
	end

	local cellID = SceneObject(pContianer):getObjectID()
	local cellName = BuildingObject(pWarren):getCellName(cellID)

	if (cellName == "smallroom78") then -- Command center
		local pCell = Warren:getCell("plusroom84")

		if (pCell ~= nil) then
			if (readData("warren:reactorOverride") == 1) then
				Warren:unlockRoom(pCell)
			else
				CreatureObject(pObj):sendSystemMessage("@theme_park/warren/warren_system_messages:core_warning") --WARNING: Reactor Core Overload Imminent. Control Center Lock-Down initiated.
				Warren:lockRoom(pCell)
			end
		end
	elseif (cellName == "smallroom47") then -- Inquisitor room
		local pCell = Warren:getCell("smallroom47")

		if (pCell ~= nil) then
			if (readData("warren:inquisitorUnlocked") == 1) then
				Warren:unlockRoom(pCell)
			else
				Warren:lockRoom(pCell)
			end
		end
	elseif (cellName == "smallroom44") then -- Reactor core
		local pCell = Warren:getCell("smallroom44")

		if (pCell ~= nil) then
			if (readData("warren:reactorUnlocked") == 1) then
				Warren:unlockRoom(pCell)
			else
				Warren:lockRoom(pCell)
			end
		end
	end

	return 0
end

function WarrenRoomComponent:canAddObject(pContainer, pObj, slot)
	return -1
end

function WarrenRoomComponent:removeObject(pContainer, pObj, slot)
	return -1
end
