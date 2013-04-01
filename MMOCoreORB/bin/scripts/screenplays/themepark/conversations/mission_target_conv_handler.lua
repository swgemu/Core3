mission_target_conv_handler = Object:new {  
	themePark = nil
}

function mission_target_conv_handler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end
 
function mission_target_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption)
	local creature = LuaCreatureObject(pConversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
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
			nextConversationScreen = conversation:getScreen("npc_breech_n")
		end
	else
		nextConversationScreen = conversation:getScreen("npc_breech_n")
	end
	return nextConversationScreen
end

function mission_target_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	
	local screenID = screen:getScreenID()
	
	if screenID == "npc_breech_n" then
		pConversationScreen = self:handleScreenBreech(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "missiontype" then
		pConversationScreen = self:handleScreenMissionType(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_smuggle_n" then
		pConversationScreen = self:handleScreenSmuggle(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_takeme_n" then
		pConversationScreen = self:handleScreenTakeMe(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	end
	return pConversationScreen
end

function mission_target_conv_handler:handleScreenBreech(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
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
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_breech_" .. missionNumber)
	
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
	
	local npcID = readData(creature:getObjectID() .. ":missionSpawn:no1")
	local correctNpc = true
	if npcID ~= npc:getObjectID() then
		correctNpc = false
	end
	
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	
	local npcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local mission = self.themePark:getMission(npcNumber, missionNumber)

	local npcSpawnData = nil
	local npcWorldPosition = nil
	for i = 1, # self.themePark.npcMap do
		local npcSpawnNumber = self.themePark.npcMap[i].npcNumber
		if npcNumber == npcSpawnNumber then
			npcSpawnData = self.themePark.npcMap[i].spawnData
			if npcSpawnData.cellID ~= 0 then
				npcWorldPosition = self.themePark.npcMap[i].worldPosition
			end
		end
	end

	local npcX = 0
	local npcY = 0

	if npcWorldPosition == nil then
		npcX = npcSpawnData.x
		npcY = npcSpawnData.y
	else
		npcX = npcWorldPosition.x
		npcY = npcWorldPosition.y
	end

	local nextScreenID
	if mission.missionType == "deliver" then
		if correctNpc == true then
			if self.themePark:hasRequiredItem(pConversingPlayer) == true then
			 	self.themePark:removeDeliverItem(pConversingPlayer)
				self.themePark:completeMission(pConversingPlayer)
				
				nextScreenID = "npc_smuggle_n"
			else
				nextScreenID = "notit_n"
			end
		else
			nextScreenID = "dontknowyou_n"
		end
	elseif mission.missionType == "escort" then
		if correctNpc == true then
			self.themePark:followPlayer(pConversingNpc, pConversingPlayer)
			self.themePark:updateWaypoint(pConversingPlayer, npcSpawnData.planetName, npcX, npcY, 1)
			nextScreenID = "npc_takeme_n"
		else
			nextScreenID = "otherescort_n"
		end
	elseif mission.missionType == "retrieve" then
		if correctNpc == true then
			self.themePark:giveMissionItems(mission, pConversingPlayer)
			self.themePark:updateWaypoint(pConversingPlayer, npcSpawnData.planetName, npcX, npcY, 1)
			nextScreenID = "npc_smuggle_n"
		else
			nextScreenID = "dontknowyou_n"
		end
	end

	return self:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, conversationTemplate:getScreen(nextScreenID))
end
