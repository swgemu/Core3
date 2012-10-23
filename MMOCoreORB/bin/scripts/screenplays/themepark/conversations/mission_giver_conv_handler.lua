mission_giver_conv_handler = Object:new {  
	themePark = nil
}

function mission_giver_conv_handler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end
 
function mission_giver_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption)
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
			nextConversationScreen = conversation:getScreen("init")
		end
	else
		nextConversationScreen = conversation:getScreen("init")
	end
	return nextConversationScreen
end

function mission_giver_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	
	local screenID = screen:getScreenID()

	if screenID == "init" then
		pConversationScreen = self:handleScreenInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "accept" then
		pConversationScreen = self:handleScreenAccept(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_1_n" then
		pConversationScreen = self:handleScreenNpc1(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_2_n" then
		pConversationScreen = self:handleScreenNpc2(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_3_n" then
		pConversationScreen = self:handleScreenNpc3(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_4_n" then
		pConversationScreen = self:handleScreenNpc4(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_work_n" then
		pConversationScreen = self:handleScreenWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_reward_n" then
		pConversationScreen = self:handleScreenReward(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_reset_n" then
		pConversationScreen = self:handleScreenReset(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_backtowork_n" then	
		pConversationScreen = self:handleScreenBackToWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "next" then	
		pConversationScreen = self:handleScreenNext(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "notyet" then	
		pConversationScreen = self:handleScreenNotYet(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_backtowork_n" then	
		pConversationScreen = self:handleScreenBackToWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	end
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	local nextScreenName
	if 1 == 1 then -- TODO: check if player can run this theme park. I.e. no other theme park is active.
		local thisNpcNumber = self.themePark:getNpcNumber(pConversingNpc)
		local activeNpcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
		local npcCompare = thisNpcNumber - activeNpcNumber
		
		if npcCompare == 0 then
			if self.themePark:missionStatus(pConversingPlayer) == 1 then
				if self.themePark:getMissionType(activeNpcNumber, pConversingPlayer) == "escort" and self.themePark:escortedNpcCloseEnough(pConversingPlayer) == true then
					nextScreenName = "npc_reward_n"
				elseif self.themePark:getMissionType(activeNpcNumber, pConversingPlayer) == "retrieve" and self.themePark:hasRequiredItem(pConversingPlayer) == true then
			 		self.themePark:removeDeliverItem(pConversingPlayer)
					nextScreenName = "npc_reward_n"
				else
					nextScreenName = "npc_work_n"
				end
			elseif self.themePark:missionStatus(pConversingPlayer) == 2 then
				if self.themePark:getMissionType(activeNpcNumber, pConversingPlayer) == "assassinate" and not self.themePark:hasLootedRequiredItem(activeNpcNumber, pConversingPlayer) == true then
					nextScreenName = "npc_work_n"
				else
					nextScreenName = "npc_reward_n"
				end			
			else
				nextScreenName = "npc_1_n"
			end
		elseif npcCompare < 0 then
			nextScreenName = "next"
		else
			nextScreenName = "notyet"
		end
	else
		nextScreenName = "cantwork"
	end

	return self:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, conversationTemplate:getScreen(nextScreenName))
end

function mission_giver_conv_handler:handleScreenAccept(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	-- TODO verify that mission items can be spawned, spawn them, update screen play state etc.
	--Test
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	
	local nextScreenName = "npc_noloc_n"
	if self.themePark:handleMissionAccept(npcNumber, missionNumber, pConversingPlayer) == true then
		nextScreenName = "npc_2_n"
	end
	
	return self:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, conversationTemplate:getScreen(nextScreenName))
end

function mission_giver_conv_handler:handleScreenNpc1(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_1_" .. missionNumber)
	
	clonedScreen:removeAllOptions()
	
	clonedScreen:addOption(stfFile .. ":player_1_" .. missionNumber, "accept")
	clonedScreen:addOption(stfFile .. ":player_2_" .. missionNumber, "npc_3_n")
	clonedScreen:addOption(stfFile .. ":player_3_" .. missionNumber, "npc_4_n")
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenNpc2(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_2_" .. missionNumber)
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenNpc3(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_3_" .. missionNumber)
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenNpc4(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_4_" .. missionNumber)
	
	clonedScreen:removeAllOptions()
	
	clonedScreen:addOption(stfFile .. ":player_1_" .. missionNumber, "accept")
	clonedScreen:addOption(stfFile .. ":player_2_" .. missionNumber, "npc_3_n")
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_work_" .. missionNumber)
	
	clonedScreen:removeAllOptions()
	
	clonedScreen:addOption(stfFile .. ":player_reset_" .. missionNumber, "npc_reset_n")
	clonedScreen:addOption(stfFile .. ":player_sorry_" .. missionNumber, "npc_backtowork_n")
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenReward(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_reward_" .. missionNumber)

	self.themePark:handleMissionReward(pConversingPlayer)
	self.themePark:cleanUpMission(pConversingPlayer)
	self.themePark:goToNextMission(pConversingPlayer)
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenReset(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_reset_" .. missionNumber)

	self.themePark:resetCurrentMission(pConversingPlayer)
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenBackToWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_backtowork_" .. missionNumber)
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenNext(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":next")
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenNoLoc(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_noloc_" .. missionNumber)
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenNotYet(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":notyet")
	
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenBackToWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)
	
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_backtowork_" .. missionNumber)
	
	return pConversationScreen
end
