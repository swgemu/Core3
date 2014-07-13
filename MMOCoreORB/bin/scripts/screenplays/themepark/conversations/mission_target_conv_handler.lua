mission_target_conv_handler = Object:new {
	themePark = nil
}

function mission_target_conv_handler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function mission_target_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption)
	local creature = LuaCreatureObject(pConversingPlayer)
	local convosession = creature:getConversationSession()

	local lastConversationScreen = nil

	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end

	local conversation = LuaConversationTemplate(pConversationTemplate)

	local nextConversationScreen

	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)

		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)

		nextConversationScreen = conversation:getScreen(optionLink)

		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
		else
			nextConversationScreen = conversation:getScreen("missiontype")
		end
	else
		nextConversationScreen = conversation:getScreen("missiontype")
	end
	return nextConversationScreen
end

function mission_target_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)

	local screenID = screen:getScreenID()

	if screenID == "missiontype" then
		pConversationScreen = self:handleScreenMissionType(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "inv_full" then
		pConversationScreen = self:handleScreenInvFull(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_smuggle_n" then
		pConversationScreen = self:handleScreenSmuggle(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
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

	local npcNumber = self.themePark:getActiveNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":notit_" .. missionNumber)

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenSmuggle(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	if (pConversingNpc == nil) then
		return nil
	end
	local npc = LuaCreatureObject(pConversingNpc)

	local npcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_smuggle_" .. missionNumber)

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenTakeMe(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	if (pConversingNpc == nil) then
		return nil
	end
	local npc = LuaCreatureObject(pConversingNpc)

	local npcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_takeme_" .. missionNumber)

	return pConversationScreen
end

function mission_target_conv_handler:handleScreenMissionType(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	if (pConversingNpc == nil) then
		return nil
	end
	local npc = LuaCreatureObject(pConversingNpc)
	local creature = LuaCreatureObject(pConversingPlayer)
	local activeMission = readData(creature:getObjectID() .. ":activeMission")
	local npcID = readData(creature:getObjectID() .. ":missionSpawn:no1")
	local correctNpc = true
	if npcID ~= npc:getObjectID() then
		correctNpc = false
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	local npcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local mission = self.themePark:getMission(npcNumber, missionNumber)

	local worldPosition = self.themePark:getNpcWorldPosition(npcNumber)

	local npcData = self.themePark:getNpcData(npcNumber)

	local nextScreenID
	if mission.missionType == "deliver" then
		if correctNpc == true then
			if self.themePark:hasRequiredItem(pConversingPlayer) == true then
				self.themePark:removeDeliverItem(pConversingPlayer)
				self.themePark:completeMission(pConversingPlayer)
				nextScreenID = "npc_smuggle_n"
			else
				if activeMission == 2 then
					nextScreenID = "npc_smuggle_n"
				else
					nextScreenID = "notit_n"
				end
			end
		else
			nextScreenID = "dontknowyou_n"
		end
	elseif mission.missionType == "escort" then
		if correctNpc == true then
			self.themePark:createEscortReturnArea(pConversingNpc, pConversingPlayer)
			self.themePark:followPlayer(pConversingNpc, pConversingPlayer)
			self.themePark:updateWaypoint(pConversingPlayer, npcData.spawnData.planetName, worldPosition.x, worldPosition.y, "return")
			nextScreenID = "npc_takeme_n"
		else
			nextScreenID = "otherescort_n"
		end
	elseif mission.missionType == "retrieve" then
		if correctNpc == true then
			if activeMission ~= 2 and self.themePark:hasFullInventory(pConversingPlayer) == false then
				self.themePark:giveMissionItems(mission, pConversingPlayer)
				self.themePark:updateWaypoint(pConversingPlayer, npcData.spawnData.planetName, worldPosition.x, worldPosition.y, "return")
				nextScreenID = "npc_smuggle_n"
			elseif activeMission ~= 2 and self.themePark:hasFullInventory(pConversingPlayer) == true then
				nextScreenID = "inv_full"
			else
				nextScreenID = "npc_smuggle_n"
			end
		else
			nextScreenID = "dontknowyou_n"
		end
	end

	return self:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, conversationTemplate:getScreen(nextScreenID))
end
