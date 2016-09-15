local ObjectManager = require("managers.object.object_manager")

mission_target_conv_handler = Object:new {
	themePark = nil
}

function mission_target_conv_handler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function mission_target_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption, pConversingNpc)
	local convosession = CreatureObject(pConversingPlayer):getConversationSession()

	local lastConversationScreen = nil

	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end

	local conversation = LuaConversationTemplate(pConversationTemplate)

	local nextConversationScreen = nil

	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)

		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)

		nextConversationScreen = conversation:getScreen(optionLink)

		if nextConversationScreen == nil then
			nextConversationScreen = self:getInitialScreen(pConversingPlayer, pConversingNpc, pConversationTemplate)
		end
	else
		nextConversationScreen = self:getInitialScreen(pConversingPlayer, pConversingNpc, pConversationTemplate)
	end

	return nextConversationScreen
end

function mission_target_conv_handler:getInitialScreen(pConversingPlayer, pConversingNpc, pConversationTemplate)
	local playerID = SceneObject(pConversingPlayer):getObjectID()
	local activeMission = readData(playerID .. ":activeMission")
	local npcID = readData(playerID .. ":missionSpawn:no1")
	local correctNpc = true

	if npcID ~= SceneObject(pConversingNpc):getObjectID() then
		correctNpc = false
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	local ownerID = readData(SceneObject(pConversingNpc):getObjectID() .. ":missionOwnerID")
	local pOwner = getCreatureObject(ownerID)
	
	if pOwner == nil then
		return conversationTemplate:getScreen("dontknowyou_n")
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pOwner)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pOwner)
	local mission = self.themePark:getMission(npcNumber, missionNumber)
	local npcData = self.themePark:getNpcData(npcNumber)


	if mission == nil or npcData == nil then
		return conversationTemplate:getScreen("dontknowyou_n")
	end

	local nextScreenID = "dontknowyou_n"

	if mission.missionType == "deliver" then
		if correctNpc == true then
			if self.themePark:hasRequiredItem(pConversingPlayer) == true then
				nextScreenID = "npc_smuggle_n"
			elseif activeMission == 2 then
				nextScreenID = "npc_smuggle_n"
			else
				nextScreenID = "notit_n"
			end
		else
			nextScreenID = "dontknowyou_n"
		end
	elseif mission.missionType == "escort" then
		if correctNpc == true then
			nextScreenID = "npc_takeme_n"
		else
			nextScreenID = "otherescort_n"
		end
	elseif mission.missionType == "retrieve" then
		if correctNpc == true then
			if activeMission ~= 2 and self.themePark:hasFullInventory(pConversingPlayer) == true then
				nextScreenID = "inv_full"
			else
				nextScreenID = "npc_smuggle_n"
			end
		else
			nextScreenID = "dontknowyou_n"
		end
	end

	return conversationTemplate:getScreen(nextScreenID)
end

function mission_target_conv_handler:getReturnWaypointLoc(playerID, npcNumber)
	local location = {}

	if (self.themePark.genericGiver) then
		local giverId = readData(playerID ..":genericGiverID")
		local pGiver = getSceneObject(giverId)
		if (pGiver == nil) then
			printf("Error in mission_target_conv_handler:getReturnWaypointLoc(), unable to find generic quest giver.")
			return location
		end
		location[1] = SceneObject(pGiver):getZoneName()
		location[2] = SceneObject(pGiver):getWorldPositionX()
		location[3] = SceneObject(pGiver):getWorldPositionY()
	else
		local worldPosition = self.themePark:getNpcWorldPosition(npcNumber)
		location[1] = self.themePark.planetName
		location[2] = worldPosition.x
		location[3] = worldPosition.y

		local npcData = self.themePark:getNpcData(npcNumber)

		if (npcData.spawnData.planetName ~= nil and npcData.spawnData.planetName ~= "") then
			location[1] = npcData.spawnData.planetName
		end

		if (location[1] == nil or location[1] == "") then
			printf("ERROR: Unable to create return waypoint for mission number " .. missionNumber .. " in screenplay " .. self.themePark.className .. ", planetName invalid.\n")
			return {}
		end
	end

	return location
end

function mission_target_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)

	local screenID = screen:getScreenID()

	if screenID == "inv_full" then
		pConversationScreen = self:handleScreenInvFull(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "otherescort_n" then
		pConversationScreen = self:handleScreenOtherEscort(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "dontknowyou_n" then
		pConversationScreen = self:handleScreenDontKnowYou(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_smuggle_n" then
		pConversationScreen = self:handleScreenSmuggle(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_more_1_n" then
		pConversationScreen = self:handleScreenNpcMoreOne(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_more_2_n" then
		pConversationScreen = self:handleScreenNpcMoreTwo(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_more_3_n" then
		pConversationScreen = self:handleScreenNpcMoreThree(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_takeme_n" then
		pConversationScreen = self:handleScreenTakeMe(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "notit_n" then
		pConversationScreen = self:handleScreenNotIt(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	end

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenInvFull(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	clonedScreen:setDialogTextStringId("@conversation/crafting_contractor:s_82c3e20a") -- It looks like your inventory is full. Talk to me again when you free up some space.

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenNotIt(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local npcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	if self.themePark:isValidConvoString(stfFile, ":notit_" .. missionNumber) then
		clonedScreen:setDialogTextStringId(stfFile .. ":notit_" .. missionNumber)
	elseif self.themePark:isValidConvoString(stfFile, ":notit") then
		clonedScreen:setDialogTextStringId(stfFile .. ":notit")
	else
		clonedScreen:setDialogTextStringId(stfFile .. ":not_it")
	end

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenSmuggle(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	if (pConversingNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_smuggle_" .. missionNumber)

	if self.themePark:isValidConvoString(stfFile, ":player_more_1_" .. missionNumber) then
		clonedScreen:addOption(stfFile .. ":player_more_1_" .. missionNumber, "npc_more_1_n")
		clonedScreen:setStopConversation(false)
		return pConversationScreen
	end

	local mission = self.themePark:getMission(npcNumber, missionNumber)

	if mission.missionType == "deliver" then
		if self.themePark:hasRequiredItem(pConversingPlayer) == true then
			self.themePark:removeDeliverItem(pConversingPlayer)
			self.themePark:completeMission(pConversingPlayer)
		end
	elseif mission.missionType == "retrieve" then
		local playerID = SceneObject(pConversingPlayer):getObjectID()
		local activeMission = readData(playerID .. ":activeMission")

		if activeMission ~= 2 then
			local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)
			self.themePark:giveMissionItems(mission, pConversingPlayer)
			self.themePark:updateWaypoint(pConversingPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
		end
	end

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenNpcMoreOne(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	if (pConversingNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_more_1_" .. missionNumber)

	if self.themePark:isValidConvoString(stfFile, ":player_more_2_" .. missionNumber) then
		clonedScreen:addOption(stfFile .. ":player_more_2_" .. missionNumber, "npc_more_2_n")
		clonedScreen:setStopConversation(false)
		return pConversationScreen
	end

	local mission = self.themePark:getMission(npcNumber, missionNumber)
	local playerID = SceneObject(pConversingPlayer):getObjectID()

	if mission.missionType == "deliver" then
		if self.themePark:hasRequiredItem(pConversingPlayer) == true then
			self.themePark:removeDeliverItem(pConversingPlayer)
			self.themePark:completeMission(pConversingPlayer)
		end
	elseif mission.missionType == "retrieve" then

		local activeMission = readData(playerID .. ":activeMission")

		if activeMission ~= 2 then
			local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)
			self.themePark:giveMissionItems(mission, pConversingPlayer)
			self.themePark:updateWaypoint(pConversingPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
		end
	elseif mission.missionType == "escort" then
		local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)

		self.themePark:createEscortReturnArea(pConversingNpc, pConversingPlayer)
		self.themePark:followPlayer(pConversingNpc, pConversingPlayer)
		self.themePark:updateWaypoint(pConversingPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
	end

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenNpcMoreTwo(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	if (pConversingNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_more_2_" .. missionNumber)

	if self.themePark:isValidConvoString(stfFile, ":player_more_3_" .. missionNumber) then
		clonedScreen:addOption(stfFile .. ":player_more_3_" .. missionNumber, "npc_more_3_n")
		clonedScreen:setStopConversation(false)
		return pConversationScreen
	end

	local mission = self.themePark:getMission(npcNumber, missionNumber)
	local playerID = SceneObject(pConversingPlayer):getObjectID()

	if mission.missionType == "deliver" then
		if self.themePark:hasRequiredItem(pConversingPlayer) == true then
			self.themePark:removeDeliverItem(pConversingPlayer)
			self.themePark:completeMission(pConversingPlayer)
		end
	elseif mission.missionType == "retrieve" then
		local activeMission = readData(playerID .. ":activeMission")

		if activeMission ~= 2 then
			local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)
			self.themePark:giveMissionItems(mission, pConversingPlayer)
			self.themePark:updateWaypoint(pConversingPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
		end
	elseif mission.missionType == "escort" then
		local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)

		self.themePark:createEscortReturnArea(pConversingNpc, pConversingPlayer)
		self.themePark:followPlayer(pConversingNpc, pConversingPlayer)
		self.themePark:updateWaypoint(pConversingPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
	end

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenNpcMoreThree(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	if (pConversingNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_more_3_" .. missionNumber)

	local mission = self.themePark:getMission(npcNumber, missionNumber)
	local playerID = SceneObject(pConversingPlayer):getObjectID()

	if mission.missionType == "deliver" then
		if self.themePark:hasRequiredItem(pConversingPlayer) == true then
			self.themePark:removeDeliverItem(pConversingPlayer)
			self.themePark:completeMission(pConversingPlayer)
		end
	elseif mission.missionType == "retrieve" then
		local activeMission = readData(playerID .. ":activeMission")

		if activeMission ~= 2 then
			local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)
			self.themePark:giveMissionItems(mission, pConversingPlayer)
			self.themePark:updateWaypoint(pConversingPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
		end
	elseif mission.missionType == "escort" then
		local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)

		self.themePark:createEscortReturnArea(pConversingNpc, pConversingPlayer)
		self.themePark:followPlayer(pConversingNpc, pConversingPlayer)
		self.themePark:updateWaypoint(pConversingPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
	end

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenTakeMe(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	if (pConversingNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_takeme_" .. missionNumber)

	if self.themePark:isValidConvoString(stfFile, ":player_more_1_" .. missionNumber) then
		clonedScreen:addOption(stfFile .. ":player_more_1_" .. missionNumber, "npc_more_1_n")
		clonedScreen:setStopConversation(false)
		return pConversationScreen
	end

	local playerID = SceneObject(pConversingPlayer):getObjectID()
	local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)

	self.themePark:createEscortReturnArea(pConversingNpc, pConversingPlayer)
	self.themePark:followPlayer(pConversingNpc, pConversingPlayer)
	self.themePark:updateWaypoint(pConversingPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenOtherEscort(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	if (pConversingNpc == nil) then
		return nil
	end

	local ownerID = readData(CreatureObject(pConversingNpc):getObjectID() .. ":missionOwnerID")
	local pOwner = getCreatureObject(ownerID)

	if pOwner == nil then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pOwner)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pOwner)
	local stfFile = self.themePark:getStfFile(npcNumber)

	if self.themePark:isValidConvoString(stfFile, ":otherescort_" .. missionNumber) then
		clonedScreen:setDialogTextStringId(stfFile .. ":otherescort_" .. missionNumber)
	elseif self.themePark:isValidConvoString(stfFile, ":otherescort") then
		clonedScreen:setDialogTextStringId(stfFile .. ":otherescort")
	elseif self.themePark:isValidConvoString(stfFile, ":escortother") then
		clonedScreen:setDialogTextStringId(stfFile .. ":escortother")
	else
		clonedScreen:setDialogTextStringId(stfFile .. ":dontknowyou_" .. missionNumber)
	end

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenDontKnowYou(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	if (pConversingNpc == nil) then
		return nil
	end

	local ownerID = readData(CreatureObject(pConversingNpc):getObjectID() .. ":missionOwnerID")
	local pOwner = getCreatureObject(ownerID)

	if pOwner == nil then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pOwner)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pOwner)
	local stfFile = self.themePark:getStfFile(npcNumber)

	if self.themePark:isValidConvoString(stfFile, ":dontknowyou_" .. missionNumber) then
		clonedScreen:setDialogTextStringId(stfFile .. ":dontknowyou_" .. missionNumber)
	else
		clonedScreen:setDialogTextStringId(stfFile .. ":dontknowyou")
	end

	return pConversationScreen
end
