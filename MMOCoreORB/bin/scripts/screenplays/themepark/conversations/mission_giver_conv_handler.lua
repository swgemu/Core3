local ObjectManager = require("managers.object.object_manager")

mission_giver_conv_handler = conv_handler:new {
	themePark = nil,
	useQuitQuest = true
}

function mission_giver_conv_handler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function mission_giver_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if screenID == "init" then
		pConvScreen = self:handleScreenInit(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_noloc_n" then
		pConvScreen = self:handleScreenNoLoc(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "failure" then
		pConvScreen = self:handleScreenFailure(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "too_weak" then
		pConvScreen = self:handleScreenTooWeak(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "inv_full" then
		pConvScreen = self:handleScreenInvFull(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "accept" then
		pConvScreen = self:handleScreenAccept(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_1_n" then
		pConvScreen = self:handleScreenNpc1(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_2_n" then
		pConvScreen = self:handleScreenNpc2(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_3_n" then
		pConvScreen = self:handleScreenNpc3(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_4_n" then
		pConvScreen = self:handleScreenNpc4(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_5_n" then
		pConvScreen = self:handleScreenNpc5(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_6_n" then
		pConvScreen = self:handleScreenNpc6(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_work_n" then
		pConvScreen = self:handleScreenWork(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "notit_n" then
		pConvScreen = self:handleScreenNotIt(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_reward_n" then
		pConvScreen = self:handleScreenReward(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_reset_n" or screenID == "npc_reset"  then
		pConvScreen = self:handleScreenReset(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_backtowork_n" or screenID == "npc_backtowork" then
		pConvScreen = self:handleScreenBackToWork(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "next" then
		pConvScreen = self:handleScreenNext(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "notyet" then
		pConvScreen = self:handleScreenNotYet(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "cant_work" then
		pConvScreen = self:handleScreenCantWork(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "no_faction" then
		pConvScreen = self:handleScreenNoFaction(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "quit_quest" then
		pConvScreen = self:handleScreenQuitQuest(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "npc_quit" then
		self.themePark:resetCurrentMission(pPlayer)
	end

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenInit(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local conversationTemplate = LuaConversationTemplate(pConvTemplate)
	local nextScreenName
	local activeScreenPlay = readStringData(CreatureObject(pPlayer):getObjectID() .. ":activeScreenPlay")

	if activeScreenPlay == self.themePark.className or activeScreenPlay == "" then
		local activeNpcNumber = self.themePark:getActiveNpcNumber(pPlayer)
		local thisNpcNumber = self.themePark:getNpcNumber(pNpc)
		local stfFile = self.themePark:getStfFile(thisNpcNumber)
		local npcCompare = thisNpcNumber - activeNpcNumber
		local globalFaction = self.themePark:getGlobalFaction()
		local currentMissionNumber = self.themePark:getCurrentMissionNumber(activeNpcNumber, pPlayer)
		local missionFaction = 0

		if currentMissionNumber > 0 and thisNpcNumber == activeNpcNumber then
			missionFaction = self.themePark:getMissionFaction(activeNpcNumber, currentMissionNumber)
		elseif thisNpcNumber ~= activeNpcNumber then
			missionFaction = self.themePark:getNpcFaction(thisNpcNumber)
		end

		if (self.themePark:missionStatus(pPlayer) == -1) then
			nextScreenName = "failure"

		elseif npcCompare < 0 then
			nextScreenName = "next"

		elseif currentMissionNumber == 0 and not self.themePark.genericGiver then
			nextScreenName = "notyet"

		elseif missionFaction ~= 0 and self.themePark:isInFaction(missionFaction, pPlayer) ~= true then
			if self.themePark:isValidConvoString(stfFile, ":notyet") then
				nextScreenName = "notyet"
			else
				nextScreenName = "no_faction"
			end

		elseif globalFaction ~= 0 and self.themePark:isInFaction(globalFaction, pPlayer) ~= true then
			if self.themePark:isValidConvoString(stfFile, ":notyet") and #self.themePark.npcMap == 1  then
				nextScreenName = "notyet"
			else
				nextScreenName = "no_faction"
			end

		elseif self.themePark:requiresEliteCombatProfession() == true and self.themePark:hasEliteCombatProfession(pPlayer) == false then
			nextScreenName = "too_weak"

		elseif self.themePark:hasEnoughFaction(pPlayer) == false then
			nextScreenName = "no_faction"

		elseif missionFaction ~= 0 and self.themePark:isInFaction(missionFaction, pPlayer) and self.themePark:isOnLeave(pPlayer) then
			if self.themePark:isValidConvoString(stfFile, ":notyet") then
				nextScreenName = "notyet"
			else
				nextScreenName = "no_faction"
			end
		elseif globalFaction ~= 0 and self.themePark:isInFaction(globalFaction, pPlayer) and self.themePark:isOnLeave(pPlayer) then
			if self.themePark:isValidConvoString(stfFile, ":notyet") and #self.themePark.npcMap == 1 then
				nextScreenName = "notyet"
			else
				nextScreenName = "no_faction"
			end
		elseif npcCompare == 0 then
			if self.themePark:missionStatus(pPlayer) == 1 then
				if self.themePark:getMissionType(activeNpcNumber, pPlayer) == "escort" and self.themePark:escortedNpcCloseEnough(pPlayer) == true then
					nextScreenName = "npc_reward_n"
				else
					nextScreenName = "npc_work_n"
				end
			elseif self.themePark:missionStatus(pPlayer) == 2 then
				if self.themePark:getMissionType(activeNpcNumber, pPlayer) == "confiscate" and not self.themePark:hasLootedRequiredItem(activeNpcNumber, pPlayer) == true then
					nextScreenName = "npc_work_n"
				elseif self.themePark:getMissionType(activeNpcNumber, pPlayer) == "retrieve" and self.themePark:hasRequiredItem(pPlayer) == true then
					self.themePark:removeDeliverItem(pPlayer)
					nextScreenName = "npc_reward_n"
				elseif self.themePark:getMissionType(activeNpcNumber, pPlayer) == "retrieve" and self.themePark:hasRequiredItem(pPlayer) == false then
					nextScreenName = "npc_work_n"
				else
					nextScreenName = "npc_reward_n"
				end
			else
				if self.themePark:getMissionPreReq(pPlayer) ~= 0 then
					local missionPreReq = self.themePark:getMissionPreReq(pPlayer)
					if missionPreReq.type == "item" and (readData(CreatureObject(pPlayer):getObjectID() .. ":hasPreReqItem") == 1 or self.themePark:doPreReqItemCheck(pPlayer, missionPreReq) == true) then
						nextScreenName = "npc_1_n"
					elseif missionPreReq.type == "state" and CreatureObject(pPlayer):hasScreenPlayState(missionPreReq.state, missionPreReq.screenPlayState) then
						nextScreenName = "npc_1_n"
					else
						nextScreenName = "notyet"
					end
				else
					nextScreenName = "npc_1_n"
				end
			end
		else
			nextScreenName = "notyet"
		end
	else
		if self.useQuitQuest then
			nextScreenName = "quit_quest"
		else
			nextScreenName = "cant_work"
		end
	end

	if (self.themePark.genericGiver) then
		local giverId = readData(CreatureObject(pPlayer):getObjectID() ..":genericGiverID")
		if (giverId ~= 0 and giverId ~= SceneObject(pNpc):getObjectID()) then
			if self.useQuitQuest then
				nextScreenName = "quit_quest"
			else
				nextScreenName = "cant_work"
			end
		end
	end

	return self:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, conversationTemplate:getScreen(nextScreenName))
end

function mission_giver_conv_handler:handleScreenTooWeak(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	clonedScreen:setDialogTextStringId("@static_npc/default_dialog:too_weak") -- The task I have seems beyond your capabilities. Come back when you're a bit stronger.

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenFailure(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_failure_" .. missionNumber)
	self.themePark:resetCurrentMission(pPlayer)

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenInvFull(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	clonedScreen:setDialogTextStringId("@conversation/crafting_contractor:s_82c3e20a") -- It looks like your inventory is full. Talk to me again when you free up some space.

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenAccept(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local conversationTemplate = LuaConversationTemplate(pConvTemplate)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)

	local nextScreenName = "npc_noloc_n"
	if self.themePark:getMissionType(npcNumber, pPlayer) == "deliver" and self.themePark:hasFullInventory(pPlayer) == true then
		nextScreenName = "inv_full"
	elseif self.themePark:handleMissionAccept(npcNumber, missionNumber, pPlayer) == true then
		if (self.themePark.genericGiver) then
			writeData(CreatureObject(pPlayer):getObjectID() ..":genericGiverID", SceneObject(pNpc):getObjectID())
		end
		nextScreenName = "npc_2_n"
	end

	return self:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, conversationTemplate:getScreen(nextScreenName))
end

function mission_giver_conv_handler:handleScreenNpc1(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)

	if (self.themePark.genericGiver) then
		local npcData = self.themePark:getNpcData(npcNumber)

		if npcData == nil then
			return nil
		end

		writeData(CreatureObject(pPlayer):getObjectID() .. ":generic_mission_number", getRandomNumber(1, #npcData.missions))
	end

	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_1_" .. missionNumber)

	clonedScreen:removeAllOptions()

	clonedScreen:addOption(stfFile .. ":player_1_" .. missionNumber, "accept")
	clonedScreen:addOption(stfFile .. ":player_2_" .. missionNumber, "npc_3_n")

	if (self.themePark:isValidConvoString(stfFile, ":player_3_" .. missionNumber)) then
		clonedScreen:addOption(stfFile .. ":player_3_" .. missionNumber, "npc_4_n")

		if (self.themePark:isValidConvoString(stfFile, ":player_4_" .. missionNumber)) then
			clonedScreen:addOption(stfFile .. ":player_4_" .. missionNumber, "npc_5_n")

			if (self.themePark:isValidConvoString(stfFile, ":player_5_" .. missionNumber)) then
				clonedScreen:addOption(stfFile .. ":player_5_" .. missionNumber, "npc_6_n")
			end
		end
	end

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenNpc2(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_2_" .. missionNumber)

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenNpc3(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_3_" .. missionNumber)

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenNpc4(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_4_" .. missionNumber)

	clonedScreen:removeAllOptions()

	clonedScreen:addOption(stfFile .. ":player_1_" .. missionNumber, "accept")
	clonedScreen:addOption(stfFile .. ":player_2_" .. missionNumber, "npc_3_n")

	if (self.themePark:isValidConvoString(stfFile, ":player_4_" .. missionNumber)) then
		clonedScreen:addOption(stfFile .. ":player_4_" .. missionNumber, "npc_5_n")

		if (self.themePark:isValidConvoString(stfFile, ":player_5_" .. missionNumber)) then
			clonedScreen:addOption(stfFile .. ":player_5_" .. missionNumber, "npc_6_n")
		end
	end

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenNpc5(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_5_" .. missionNumber)

	clonedScreen:removeAllOptions()

	clonedScreen:addOption(stfFile .. ":player_1_" .. missionNumber, "accept")
	clonedScreen:addOption(stfFile .. ":player_2_" .. missionNumber, "npc_3_n")
	clonedScreen:addOption(stfFile .. ":player_3_" .. missionNumber, "npc_4_n")

	if (self.themePark:isValidConvoString(stfFile, ":player_5_" .. missionNumber)) then
		clonedScreen:addOption(stfFile .. ":player_5_" .. missionNumber, "npc_6_n")
	end

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenNpc6(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_6_" .. missionNumber)

	clonedScreen:removeAllOptions()

	clonedScreen:addOption(stfFile .. ":player_1_" .. missionNumber, "accept")
	clonedScreen:addOption(stfFile .. ":player_2_" .. missionNumber, "npc_3_n")
	clonedScreen:addOption(stfFile .. ":player_3_" .. missionNumber, "npc_4_n")
	clonedScreen:addOption(stfFile .. ":player_4_" .. missionNumber, "npc_5_n")

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenWork(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
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

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenReward(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_reward_" .. missionNumber)

	self.themePark:handleMissionReward(pPlayer)
	if (self.themePark.genericGiver) then
		self.themePark:resetCurrentMission(pPlayer)
	else
		self.themePark:cleanUpMission(pPlayer)
		self.themePark:goToNextMission(pPlayer)
	end

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenReset(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	if (self.themePark:isValidConvoString(stfFile, ":npc_reset_" .. missionNumber)) then
		clonedScreen:setDialogTextStringId(stfFile .. ":npc_reset_" .. missionNumber)
	else
		clonedScreen:setDialogTextStringId(stfFile .. ":npc_reset")
	end

	self.themePark:resetCurrentMission(pPlayer)

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenBackToWork(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	if (self.themePark:isValidConvoString(stfFile, ":npc_backtowork_" .. missionNumber)) then
		clonedScreen:setDialogTextStringId(stfFile .. ":npc_backtowork_" .. missionNumber)
	else
		clonedScreen:setDialogTextStringId(stfFile .. ":npc_backtowork")
	end

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenNext(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":next")

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenNoLoc(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	self.themePark:resetCurrentMission(pPlayer)
	clonedScreen:setDialogTextStringId(stfFile .. ":npc_noloc_" .. missionNumber)

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenNotYet(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local stfFile = self.themePark:getStfFile(npcNumber)

	if (self.themePark:isValidConvoString(stfFile, ":notyet")) then
		clonedScreen:setDialogTextStringId(stfFile .. ":notyet")
	else
		clonedScreen:setDialogTextStringId("@static_npc/naboo/brennis_doore:notyet") -- "I got nothing to say right now."
	end

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenNotIt(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local missionNumber = self.themePark:getCurrentMissionNumber(npcNumber, pPlayer)
	local stfFile = self.themePark:getStfFile(npcNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":notit_" .. missionNumber)

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenCantWork(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local npcNumber = self.themePark:getNpcNumber(pNpc)
	local stfFile = self.themePark:getStfFile(npcNumber)

	if (self.themePark:isValidConvoString(stfFile, ":cant_work")) then
		clonedScreen:setDialogTextStringId(stfFile .. ":cant_work")
	elseif (self.themePark:isValidConvoString(stfFile, ":cantwork")) then
		clonedScreen:setDialogTextStringId(stfFile .. ":cantwork")
	else
		clonedScreen:setDialogTextStringId("@npc_mission/static_quest:cantwork")
	end

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenNoFaction(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	clonedScreen:setDialogTextStringId("@theme_park/messages:no_faction") -- "You don't have the proper standing to deal with me. Perhaps you should be more careful who you associate with."

	return pConvScreen
end

function mission_giver_conv_handler:handleScreenQuitQuest(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	clonedScreen:setDialogTextStringId("@static_npc/default_dialog:quit_quest") -- I can see that you're busy working for someone else at the moment. Would you like to continue to do so, or would you like to work for me instead?

	clonedScreen:removeAllOptions()
	clonedScreen:addOption("@static_npc/default_dialog:player_quit", "npc_quit") -- I think I'd like to work for you.
	clonedScreen:addOption("@static_npc/default_dialog:player_continue", "npc_continue") -- No, I think I'll keep my current job, thanks.

	return pConvScreen
end
