local ObjectManager = require("managers.object.object_manager")

mission_target_conv_handler = conv_handler:new {
	themePark = nil
}

function mission_target_conv_handler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function mission_target_conv_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local playerID = SceneObject(pPlayer):getObjectID()
	local activeMission = readData(playerID .. ":activeMission")
	local npcID = readData(playerID .. ":missionSpawn:no1")
	local correctNpc = true

	if npcID ~= SceneObject(pNpc):getObjectID() then
		correctNpc = false
	end

	local conversationTemplate = LuaConversationTemplate(pConvTemplate)

	local ownerID = readData(SceneObject(pNpc):getObjectID() .. ":missionOwnerID")
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
			if self.themePark:hasRequiredItem(pPlayer) == true then
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
			if activeMission ~= 2 and self.themePark:hasFullInventory(pPlayer) == true then
				nextScreenID = "inv_full"
			else
				nextScreenID = "npc_smuggle_n"
			end
		else
			nextScreenID = "dontknowyou_n"
		end
	elseif correctNpc == true then
		nextScreenID = "npc_breech_n"
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

function mission_target_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if screenID == "inv_full" then
		pConvScreen = self:handleScreenInvFull(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "otherescort_n" then
		pConvScreen = self:handleScreenOtherEscort(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "dontknowyou_n" then
		pConvScreen = self:handleScreenDontKnowYou(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_breech_n" then
		pConvScreen = self:handleScreenBreech(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_smuggle_n" then
		pConvScreen = self:handleScreenSmuggle(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_more_1_n" then
		pConvScreen = self:handleScreenNpcMoreOne(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_more_2_n" then
		pConvScreen = self:handleScreenNpcMoreTwo(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_more_3_n" then
		pConvScreen = self:handleScreenNpcMoreThree(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_takeme_n" then
		pConvScreen = self:handleScreenTakeMe(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "notit_n" then
		pConvScreen = self:handleScreenNotIt(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	end

	return pConvScreen
end

function mission_target_conv_handler:handleScreenInvFull(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	clonedScreen:setDialogTextStringId("@conversation/crafting_contractor:s_82c3e20a") -- It looks like your inventory is full. Talk to me again when you free up some space.

	return pConvScreen
end

function mission_target_conv_handler:handleScreenNotIt(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getActiveNpcNumber(pPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	if self.themePark:isValidConvoString(stfFile, ":notit_" .. missionNumber) then
		clonedScreen:setDialogTextStringId(stfFile .. ":notit_" .. missionNumber)
	elseif self.themePark:isValidConvoString(stfFile, ":notit") then
		clonedScreen:setDialogTextStringId(stfFile .. ":notit")
	elseif self.themePark:isValidConvoString(stfFile, ":not_it") then
		clonedScreen:setDialogTextStringId(stfFile .. ":not_it")
	else
		clonedScreen:setDialogTextStringId("@npc_mission/static_quest:not_it") -- No, sorry, that's not the item I was looking for...
	end

	return pConvScreen
end

function mission_target_conv_handler:handleScreenBreech(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if (pNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_breech_" .. missionNumber)

	if self.themePark:isValidConvoString(stfFile, ":player_more_1_" .. missionNumber) then
		clonedScreen:addOption(stfFile .. ":player_more_1_" .. missionNumber, "npc_more_1_n")
		clonedScreen:setStopConversation(false)
	end

	return pConvScreen
end

function mission_target_conv_handler:handleScreenSmuggle(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if (pNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_smuggle_" .. missionNumber)

	if self.themePark:isValidConvoString(stfFile, ":player_more_1_" .. missionNumber) then
		clonedScreen:addOption(stfFile .. ":player_more_1_" .. missionNumber, "npc_more_1_n")
		clonedScreen:setStopConversation(false)
		return pConvScreen
	end

	local mission = self.themePark:getMission(npcNumber, missionNumber)

	if mission.missionType == "deliver" then
		if self.themePark:hasRequiredItem(pPlayer) == true then
			self.themePark:removeDeliverItem(pPlayer)
			self.themePark:completeMission(pPlayer)
		end
	elseif mission.missionType == "retrieve" then
		local playerID = SceneObject(pPlayer):getObjectID()
		local activeMission = readData(playerID .. ":activeMission")

		if activeMission ~= 2 then
			local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)
			self.themePark:giveMissionItems(mission, pPlayer)
			self.themePark:updateWaypoint(pPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
		end
	end

	return pConvScreen
end

function mission_target_conv_handler:handleScreenNpcMoreOne(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if (pNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_more_1_" .. missionNumber)

	if self.themePark:isValidConvoString(stfFile, ":player_more_2_" .. missionNumber) then
		clonedScreen:addOption(stfFile .. ":player_more_2_" .. missionNumber, "npc_more_2_n")
		clonedScreen:setStopConversation(false)
		return pConvScreen
	end

	local mission = self.themePark:getMission(npcNumber, missionNumber)
	local playerID = SceneObject(pPlayer):getObjectID()

	if mission.missionType == "deliver" then
		if self.themePark:hasRequiredItem(pPlayer) == true then
			self.themePark:removeDeliverItem(pPlayer)
			self.themePark:completeMission(pPlayer)
		end
	elseif mission.missionType == "retrieve" then

		local activeMission = readData(playerID .. ":activeMission")

		if activeMission ~= 2 then
			local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)
			self.themePark:giveMissionItems(mission, pPlayer)
			self.themePark:updateWaypoint(pPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
		end
	elseif mission.missionType == "escort" then
		local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)

		self.themePark:createEscortReturnArea(pNpc, pPlayer)
		self.themePark:followPlayer(pNpc, pPlayer)
		self.themePark:updateWaypoint(pPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
	elseif mission.missionType == "confiscate" or mission.missionType == "assassinate" then
		writeData(playerID .. ":breechTriggered", 1)
		self.themePark:setNpcDefender(pPlayer, true)
	end

	return pConvScreen
end

function mission_target_conv_handler:handleScreenNpcMoreTwo(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if (pNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_more_2_" .. missionNumber)

	if self.themePark:isValidConvoString(stfFile, ":player_more_3_" .. missionNumber) then
		clonedScreen:addOption(stfFile .. ":player_more_3_" .. missionNumber, "npc_more_3_n")
		clonedScreen:setStopConversation(false)
		return pConvScreen
	end

	local mission = self.themePark:getMission(npcNumber, missionNumber)
	local playerID = SceneObject(pPlayer):getObjectID()

	if mission.missionType == "deliver" then
		if self.themePark:hasRequiredItem(pPlayer) == true then
			self.themePark:removeDeliverItem(pPlayer)
			self.themePark:completeMission(pPlayer)
		end
	elseif mission.missionType == "retrieve" then
		local activeMission = readData(playerID .. ":activeMission")

		if activeMission ~= 2 then
			local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)
			self.themePark:giveMissionItems(mission, pPlayer)
			self.themePark:updateWaypoint(pPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
		end
	elseif mission.missionType == "escort" then
		local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)

		self.themePark:createEscortReturnArea(pNpc, pPlayer)
		self.themePark:followPlayer(pNpc, pPlayer)
		self.themePark:updateWaypoint(pPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
	elseif mission.missionType == "confiscate" or mission.missionType == "assassinate" then
		writeData(playerID .. ":breechTriggered", 1)
		self.themePark:setNpcDefender(pPlayer, true)
	end

	return pConvScreen
end

function mission_target_conv_handler:handleScreenNpcMoreThree(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if (pNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_more_3_" .. missionNumber)

	local mission = self.themePark:getMission(npcNumber, missionNumber)
	local playerID = SceneObject(pPlayer):getObjectID()

	if mission.missionType == "deliver" then
		if self.themePark:hasRequiredItem(pPlayer) == true then
			self.themePark:removeDeliverItem(pPlayer)
			self.themePark:completeMission(pPlayer)
		end
	elseif mission.missionType == "retrieve" then
		local activeMission = readData(playerID .. ":activeMission")

		if activeMission ~= 2 then
			local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)
			self.themePark:giveMissionItems(mission, pPlayer)
			self.themePark:updateWaypoint(pPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
		end
	elseif mission.missionType == "escort" then
		local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)

		self.themePark:createEscortReturnArea(pNpc, pPlayer)
		self.themePark:followPlayer(pNpc, pPlayer)
		self.themePark:updateWaypoint(pPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")
	elseif mission.missionType == "confiscate" or mission.missionType == "assassinate" then
		writeData(playerID .. ":breechTriggered", 1)
		self.themePark:setNpcDefender(pPlayer, true)
	end

	return pConvScreen
end

function mission_target_conv_handler:handleScreenTakeMe(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if (pNpc == nil) then
		return nil
	end

	local npcNumber = self.themePark:getActiveNpcNumber(pPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_takeme_" .. missionNumber)

	if self.themePark:isValidConvoString(stfFile, ":player_more_1_" .. missionNumber) then
		clonedScreen:addOption(stfFile .. ":player_more_1_" .. missionNumber, "npc_more_1_n")
		clonedScreen:setStopConversation(false)
		return pConvScreen
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local returnLoc = self:getReturnWaypointLoc(playerID, npcNumber)

	self.themePark:createEscortReturnArea(pNpc, pPlayer)
	self.themePark:followPlayer(pNpc, pPlayer)
	self.themePark:updateWaypoint(pPlayer, returnLoc[1], returnLoc[2], returnLoc[3], "return")

	return pConvScreen
end

function mission_target_conv_handler:handleScreenOtherEscort(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if (pNpc == nil) then
		return nil
	end

	local ownerID = readData(CreatureObject(pNpc):getObjectID() .. ":missionOwnerID")
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

	return pConvScreen
end

function mission_target_conv_handler:handleScreenDontKnowYou(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if (pNpc == nil) then
		return nil
	end

	local ownerID = readData(CreatureObject(pNpc):getObjectID() .. ":missionOwnerID")
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

	return pConvScreen
end
