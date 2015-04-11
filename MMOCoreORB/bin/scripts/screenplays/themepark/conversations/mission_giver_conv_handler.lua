local ObjectManager = require("managers.object.object_manager")

mission_giver_conv_handler = Object:new {
	themePark = nil
}

function mission_giver_conv_handler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function mission_giver_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption)
	local convosession = CreatureObject(pConversingPlayer):getConversationSession()

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
	elseif screenID == "npc_noloc_n" then
		pConversationScreen = self:handleScreenNoLoc(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "failure" then
		pConversationScreen = self:handleScreenFailure(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "too_weak" then
		pConversationScreen = self:handleScreenTooWeak(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "inv_full" then
		pConversationScreen = self:handleScreenInvFull(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
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
	elseif screenID == "notit_n" then
		pConversationScreen = self:handleScreenNotIt(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_reward_n" then
		pConversationScreen = self:handleScreenReward(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_reset_n" or screenID == "npc_reset"  then
		pConversationScreen = self:handleScreenReset(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "npc_backtowork_n" or screenID == "npc_backtowork" then
		pConversationScreen = self:handleScreenBackToWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "next" then
		pConversationScreen = self:handleScreenNext(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "notyet" then
		pConversationScreen = self:handleScreenNotYet(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "cant_work" or screenID == "cantwork" then
		pConversationScreen = self:handleScreenCantWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "no_faction" then
		pConversationScreen = self:handleScreenNoFaction(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	end
	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	local nextScreenName
	local activeScreenPlay = readStringData(CreatureObject(pConversingPlayer):getObjectID() .. ":activeScreenPlay")

	if activeScreenPlay == self.themePark.className or activeScreenPlay == "" then
		local activeNpcNumber = self.themePark:getActiveNpcNumber(pConversingPlayer)
		local thisNpcNumber = self.themePark:getNpcNumber(pConversingNpc)
		local stfFile = self.themePark:getStfFile(thisNpcNumber)
		local npcCompare = thisNpcNumber - activeNpcNumber
		local globalFaction = self.themePark:getGlobalFaction()
		local currentMissionNumber = self.themePark:getCurrentMissionNumber(activeNpcNumber, pConversingPlayer)
		local missionFaction = 0

		if currentMissionNumber > 0 and thisNpcNumber == activeNpcNumber then
			missionFaction = self.themePark:getMissionFaction(activeNpcNumber, currentMissionNumber)
		elseif thisNpcNumber ~= activeNpcNumber then
			missionFaction = self.themePark:getNpcFaction(thisNpcNumber)
		end

		if (self.themePark:missionStatus(pConversingPlayer) == -1) then
			nextScreenName = "failure"

		elseif missionFaction ~= 0 and self.themePark:isInFaction(missionFaction, pConversingPlayer) ~= true then
			if self.themePark:isValidConvoString(stfFile, ":notyet") then
				nextScreenName = "notyet"
			else
				nextScreenName = "no_faction"
			end

		elseif globalFaction ~= 0 and self.themePark:isInFaction(globalFaction, pConversingPlayer) ~= true then
			if self.themePark:isValidConvoString(stfFile, ":notyet") and table.getn(self.themePark.npcMap) == 1  then
				nextScreenName = "notyet"
			else
				nextScreenName = "no_faction"
			end

		elseif self.themePark:requiresEliteCombatProfession() == true and self.themePark:hasEliteCombatProfession(pConversingPlayer) == false then
			nextScreenName = "too_weak"

		elseif missionFaction ~= 0 and self.themePark:isInFaction(missionFaction, pConversingPlayer) and self.themePark:isOnLeave(pConversingPlayer) then
			if self.themePark:isValidConvoString(stfFile, ":notyet") then
				nextScreenName = "notyet"
			else
				nextScreenName = "no_faction"
			end
		elseif globalFaction ~= 0 and self.themePark:isInFaction(globalFaction, pConversingPlayer) and self.themePark:isOnLeave(pConversingPlayer) then
			if self.themePark:isValidConvoString(stfFile, ":notyet") and table.getn(self.themePark.npcMap) == 1 then
				nextScreenName = "notyet"
			else
				nextScreenName = "no_faction"
			end
		elseif npcCompare == 0 then
			if self.themePark:missionStatus(pConversingPlayer) == 1 then
				if self.themePark:getMissionType(activeNpcNumber, pConversingPlayer) == "escort" and self.themePark:escortedNpcCloseEnough(pConversingPlayer) == true then
					nextScreenName = "npc_reward_n"
				else
					nextScreenName = "npc_work_n"
				end
			elseif self.themePark:missionStatus(pConversingPlayer) == 2 then
				if self.themePark:getMissionType(activeNpcNumber, pConversingPlayer) == "confiscate" and not self.themePark:hasLootedRequiredItem(activeNpcNumber, pConversingPlayer) == true then
					nextScreenName = "npc_work_n"
				elseif self.themePark:getMissionType(activeNpcNumber, pConversingPlayer) == "retrieve" and self.themePark:hasRequiredItem(pConversingPlayer) == true then
					self.themePark:removeDeliverItem(pConversingPlayer)
					nextScreenName = "npc_reward_n"
				elseif self.themePark:getMissionType(activeNpcNumber, pConversingPlayer) == "retrieve" and self.themePark:hasRequiredItem(pConversingPlayer) == false then
					nextScreenName = "npc_work_n"
				else
					nextScreenName = "npc_reward_n"
				end
			else
				if self.themePark:getMissionPreReq(pConversingPlayer) ~= 0 then
					local missionPreReq = self.themePark:getMissionPreReq(pConversingPlayer)
					if missionPreReq.type == "item" and (readData(CreatureObject(pConversingPlayer):getObjectID() .. ":hasPreReqItem") == 1 or self.themePark:doPreReqItemCheck(pConversingPlayer, missionPreReq) == true) then
						nextScreenName = "npc_1_n"
					elseif missionPreReq.type == "state" and CreatureObject(pConversingPlayer):hasScreenPlayState(missionPreReq.state, missionPreReq.screenPlayState) then
						nextScreenName = "npc_1_n"
					else
						nextScreenName = "notyet"
					end
				else
					nextScreenName = "npc_1_n"
				end
			end
		elseif npcCompare < 0 then
			nextScreenName = "next"
		else
			nextScreenName = "notyet"
		end
	else
		nextScreenName = "cant_work"
	end
	
	if (self.themePark.genericGiver) then
		local giverId = readData(CreatureObject(pConversingPlayer):getObjectID() ..":genericGiverID")
		if (giverId ~= 0 and giverId ~= SceneObject(pConversingNpc):getObjectID()) then
			nextScreenName = "cantwork"
		end
	end
	
	return self:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, conversationTemplate:getScreen(nextScreenName))
end

function mission_giver_conv_handler:handleScreenTooWeak(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	clonedScreen:setDialogTextStringId("@static_npc/default_dialog:too_weak") -- The task I have seems beyond your capabilities. Come back when you're a bit stronger.

	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenFailure(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_failure_" .. missionNumber)
	self.themePark:resetCurrentMission(pConversingPlayer)

	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenInvFull(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	clonedScreen:setDialogTextStringId("@conversation/crafting_contractor:s_82c3e20a") -- It looks like your inventory is full. Talk to me again when you free up some space.

	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenAccept(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)

	local nextScreenName = "npc_noloc_n"
	if self.themePark:getMissionType(npcNumber, pConversingPlayer) == "deliver" and self.themePark:hasFullInventory(pConversingPlayer) == true then
		nextScreenName = "inv_full"
	elseif self.themePark:handleMissionAccept(npcNumber, missionNumber, pConversingPlayer) == true then
		if (self.themePark.genericGiver) then
			writeData(CreatureObject(pConversingPlayer):getObjectID() ..":genericGiverID", SceneObject(pConversingNpc):getObjectID())
		end
		nextScreenName = "npc_2_n"
	end

	return self:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, conversationTemplate:getScreen(nextScreenName))
end

function mission_giver_conv_handler:handleScreenNpc1(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)

	if (self.themePark.genericGiver) then
		local npcData = self.themePark:getNpcData(npcNumber)

		if npcData == nil then
			return nil
		end

		writeData(CreatureObject(pConversingPlayer):getObjectID() .. ":generic_mission_number", getRandomNumber(1, table.getn(npcData.missions)))
	end

	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_1_" .. missionNumber)

	clonedScreen:removeAllOptions()

	clonedScreen:addOption(stfFile .. ":player_1_" .. missionNumber, "accept")
	clonedScreen:addOption(stfFile .. ":player_2_" .. missionNumber, "npc_3_n")

	if (self.themePark:isValidConvoString(stfFile, ":player_3_" .. missionNumber)) then
		clonedScreen:addOption(stfFile .. ":player_3_" .. missionNumber, "npc_4_n")
	end

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

	if (self.themePark:isValidConvoString(stfFile, ":npc_work_" .. missionNumber)) then
		clonedScreen:setDialogTextStringId(stfFile .. ":npc_work_" .. missionNumber)
	elseif (self.themePark:isValidConvoString(stfFile, ":gotowork")) then
		clonedScreen:setDialogTextStringId(stfFile .. ":gotowork")
	else
		clonedScreen:setDialogTextStringId("@npc_mission/static_quest:gotowork")
	end

	clonedScreen:removeAllOptions()
	if (self.themePark:isValidConvoString(stfFile, ":player_reset_" .. missionNumber)) then
		if (self.themePark:isValidConvoString(stfFile, ":npc_reset_" .. missionNumber)) then
			clonedScreen:addOption(stfFile .. ":player_reset_" .. missionNumber, "npc_reset_n")
		else
			clonedScreen:addOption(stfFile .. ":player_reset_" .. missionNumber, "npc_reset")
		end
	else
		if (self.themePark:isValidConvoString(stfFile, ":npc_reset_" .. missionNumber)) then
			clonedScreen:addOption(stfFile .. ":player_reset", "npc_reset_n")
		else
			clonedScreen:addOption(stfFile .. ":player_reset", "npc_reset")
		end
	end

	if (self.themePark:isValidConvoString(stfFile, ":player_sorry_" .. missionNumber)) then
		if (self.themePark:isValidConvoString(stfFile, ":npc_backtowork_" .. missionNumber)) then
			clonedScreen:addOption(stfFile .. ":player_sorry_" .. missionNumber, "npc_backtowork_n")
		else
			clonedScreen:addOption(stfFile .. ":player_sorry_" .. missionNumber, "npc_backtowork")
		end
	else
		if (self.themePark:isValidConvoString(stfFile, ":npc_backtowork_" .. missionNumber)) then
			clonedScreen:addOption(stfFile .. ":player_sorry", "npc_backtowork_n")
		else
			clonedScreen:addOption(stfFile .. ":player_sorry", "npc_backtowork")
		end
	end

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
	if (self.themePark.genericGiver) then
		self.themePark:resetCurrentMission(pConversingPlayer)
	else
		self.themePark:cleanUpMission(pConversingPlayer)
		self.themePark:goToNextMission(pConversingPlayer)
	end

	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenReset(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	if (self.themePark:isValidConvoString(stfFile, ":npc_reset_" .. missionNumber)) then
		clonedScreen:setDialogTextStringId(stfFile .. ":npc_reset_" .. missionNumber)
	else
		clonedScreen:setDialogTextStringId(stfFile .. ":npc_reset")
	end

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

	if (self.themePark:isValidConvoString(stfFile, ":npc_backtowork_" .. missionNumber)) then
		clonedScreen:setDialogTextStringId(stfFile .. ":npc_backtowork_" .. missionNumber)
	else
		clonedScreen:setDialogTextStringId(stfFile .. ":npc_backtowork")
	end

	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenNext(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
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

	self.themePark:resetCurrentMission(pConversingPlayer)
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

function mission_giver_conv_handler:handleScreenNotIt(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":notit_" .. missionNumber)

	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenCantWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local npcNumber = self.themePark:getNpcNumber(pConversingNpc)
	local stfFile = self.themePark:getStfFile(npcNumber)

	if (self.themePark:isValidConvoString(stfFile, ":cant_work")) then
		clonedScreen:setDialogTextStringId(stfFile .. ":cant_work")
	elseif (self.themePark:isValidConvoString(stfFile, ":cantwork")) then
		clonedScreen:setDialogTextStringId(stfFile .. ":cantwork")
	else
		clonedScreen:setDialogTextStringId("@npc_mission/static_quest:cantwork")
	end

	return pConversationScreen
end

function mission_giver_conv_handler:handleScreenNoFaction(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	clonedScreen:setDialogTextStringId("@theme_park/messages:no_faction")

	return pConversationScreen
end
