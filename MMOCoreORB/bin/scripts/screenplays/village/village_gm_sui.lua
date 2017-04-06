VillageGmSui = ScreenPlay:new {
	productionServer = false
}

function VillageGmSui:showMainPage(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local curPhase = VillageJediManagerTownship:getCurrentPhase()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local phaseTimeLeft = self:getPhaseDuration(pPlayer)

	local suiPrompt = " \\#pcontrast1 " .. "Current Phase:" .. " \\#pcontrast2 " .. curPhase .. " (id " .. phaseID .. ")\n" .. " \\#pcontrast1 " .. "Time Left: " .. " \\#pcontrast2 " .. phaseTimeLeft

	local pMaster = VillageJediManagerTownship:getMasterObject()

	if (pMaster ~= nil) then
		local playerTable = SceneObject(pMaster):getPlayersInRange(192)
		suiPrompt = suiPrompt .. "\n \\#pcontrast1 " .. "Players in Village: " .. " \\#pcontrast2 " .. #playerTable
	end

	local sui = SuiListBox.new("VillageGmSui", "mainCallback")
	sui.setTitle("Village GM Panel")
	sui.setPrompt(suiPrompt)

	sui.add("List players in village", "listOnlineVillagePlayers")
	sui.add("Lookup player by name", "playerLookupByName")
	sui.add("Lookup player by oid", "playerLookupByOID")

	if (not productionServer) then
		sui.add("Change to next phase", "changePhase")
	end

	sui.sendTo(pPlayer)
end

function VillageGmSui:mainCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)
	local menuOption =  suiPageData:getStoredData(tostring(args))

	local targetID

	if (string.find(menuOption, "%d")) then
		targetID = string.match(menuOption, '%d+')
		menuOption = string.gsub(menuOption, targetID, "")

		local pTarget = getSceneObject(targetID)

		if (pTarget == nil) then
			printLuaError("Unable to find player for VillageGmSui function " .. menuOption .. " using oid " .. targetID)
			return
		end
	end

	if (self[menuOption] == nil) then
		printLuaError("Tried to execute invalid function " .. menuOption .. " in VillageGmSui")
		return
	end


	self[menuOption](pPlayer, targetID)
end

function VillageGmSui.changePhase(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local sui = SuiMessageBox.new("VillageGmSui", "changePhaseCallback")

	sui.setTitle("Village Phase Change")
	sui.setPrompt("Are you sure you want to change the village to the next phase? Doing so will reset the progress of all players in the current phase.")
	sui.setOkButtonText("Yes")
	sui.setCancelButtonText("No")

	sui.sendTo(pPlayer)
end

function VillageGmSui:changePhaseCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		VillageGmSui:showMainPage(pPlayer)
		return
	end

	local curPhase = VillageJediManagerTownship:getCurrentPhase()
	local nextPhase = curPhase + 1

	if nextPhase == 5 then
		nextPhase = 1
	end

	CreatureObject(pPlayer):sendSystemMessage("Changing the Village from phase " .. curPhase .. " to phase " .. nextPhase .. ".")
	VillageJediManagerTownship:switchToNextPhase()
end

function VillageGmSui.playerLookupByName(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local sui = SuiInputBox.new("VillageGmSui", "playerLookupByNameCallback")

	sui.setTitle("Village Player Lookup (Name)")
	sui.setPrompt("Enter the name of the player you are looking for below.")

	sui.sendTo(pPlayer)
end

function VillageGmSui:playerLookupByNameCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		VillageGmSui:showMainPage(pPlayer)
		return
	end

	if (args == nil or args == "") then
		CreatureObject(pPlayer):sendSystemMessage("Invalid string entered, please try again.")
		VillageGmSui.playerLookupByName(pPlayer)
		return
	end

	local pTarget = getPlayerByName(args)

	if (pTarget == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Unable to find player using the string: " .. args .. ".")
		VillageGmSui.playerLookupByName(pPlayer)
		return
	end

	local targetID = SceneObject(pTarget):getObjectID()
	VillageGmSui.playerInfo(pPlayer, targetID)
end

function VillageGmSui.playerLookupByOID(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local sui = SuiInputBox.new("VillageGmSui", "playerLookupByOIDCallback")

	sui.setTitle("Village Player Lookup (Object ID)")
	sui.setPrompt("Enter the object id of the player you are looking for below.")

	sui.sendTo(pPlayer)
end

function VillageGmSui:playerLookupByOIDCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		VillageGmSui:showMainPage(pPlayer)
		return
	end

	if (args == nil or args == "") then
		CreatureObject(pPlayer):sendSystemMessage("Invalid oid entered, please try again.")
		VillageGmSui.playerLookupByOID(pPlayer)
		return
	end

	local pTarget = getSceneObject(args)

	if (pTarget == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Unable to find player using the oid: " .. args .. ".")
		VillageGmSui.playerLookupByOID(pPlayer)
		return
	end

	VillageGmSui.playerInfo(pPlayer, tonumber(args))
end

function VillageGmSui.listOnlineVillagePlayers(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pMaster = VillageJediManagerTownship:getMasterObject()

	if (pMaster == nil) then
		printLuaError("Null village master object in VillageGmSui:listOnlineVillagePlayers")
		return
	end

	local playerTable = SceneObject(pMaster):getPlayersInRange(192)

	local sui = SuiListBox.new("VillageGmSui", "mainCallback")
	sui.setTitle("Village GM Panel")
	sui.setPrompt("These are the online players within 192 meters of the center of the Village:")

	for i = 1, #playerTable, 1 do
		if (playerTable[i] ~= nil) then
			sui.add(SceneObject(playerTable[i]):getCustomObjectName(), "playerInfo" .. SceneObject(playerTable[i]):getObjectID())
		end
	end

	sui.sendTo(pPlayer)
end

function VillageGmSui.playerInfo(pPlayer, targetID)
	local pTarget = getCreatureObject(targetID)

	if (pTarget == nil) then
		return
	end

	local pGhost = CreatureObject(pTarget):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local promptBuf = " \\#pcontrast1 " .. "Player name:" .. " \\#pcontrast2 " .. SceneObject(pTarget):getCustomObjectName() .. "\n"
	promptBuf = promptBuf .. " \\#pcontrast1 " .. "Object ID:" .. " \\#pcontrast2 " .. targetID .. "\n"
	promptBuf = promptBuf .. " \\#pcontrast1 " .. "Jedi State:" .. " \\#pcontrast2 " .. PlayerObject(pGhost):getJediState() .. "\n"
	promptBuf = promptBuf .. " \\#pcontrast1 " .. "Progression:" .. " \\#pcontrast2 "

	if (VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_COMPLETED_PADAWAN_TRIALS)) then
		promptBuf = promptBuf.. "Padawan Trials Completed\n"
	elseif (VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_DEFEATED_MELLIACHAE)) then
		if (JediTrials:isOnPadawanTrials(pPlayer)) then
			promptBuf = promptBuf .. "Padawan Trials (" .. JediTrials:getTrialsCompleted(pPlayer) .. " completed)\n"
		else
			promptBuf = promptBuf .. "Mellichae (Defeated)\n"
		end
	elseif (VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_ACCEPTED_MELLICHAE)) then
		promptBuf = promptBuf .. "Mellichae\n"
	elseif (FsOutro:isOnOutro(pPlayer)) then
		local curStep = FsIntro:getCurrentStep(pPlayer)

		if (curStep == OLDMANWAIT) then
			promptBuf = promptBuf .. "Outro (Waiting for Old Man)\n"
		elseif (curStep == OLDMANMEET) then
			promptBuf = promptBuf .. "Outro (Old Man Visit)\n"
		end
	elseif (VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_HAS_VILLAGE_ACCESS)) then
		promptBuf = promptBuf .. "Village Phase Quests\n"
	elseif (FsIntro:isOnIntro(pPlayer)) then
		local curStep = FsIntro:getCurrentStep(pPlayer)

		if (curStep == OLDMANWAIT) then
			promptBuf = promptBuf .. "Intro (Waiting for Old Man)\n"
		elseif (curStep == OLDMANMEET) then
			promptBuf = promptBuf .. "Intro (Old Man Visit)\n"
		elseif (curStep == SITHWAIT) then
			promptBuf = promptBuf .. "Intro (Waiting for Sith Attack)\n"
		elseif (curStep == SITHATTACK) then
			promptBuf = promptBuf .. "Intro (Sith Attack)\n"
		elseif (curStep == USEDATAPADONE) then
			promptBuf = promptBuf .. "Intro (First Datapad Looted)\n"
		elseif (curStep == SITHTHEATER) then
			promptBuf = promptBuf .. "Intro (Sith Camp)\n"
		elseif (curStep == USEDATAPADTWO) then
			promptBuf = promptBuf .. "Intro (Second Datapad Looted)\n"
		elseif (curStep == VILLAGE) then
			promptBuf = promptBuf .. "Intro (Sent to Village)\n"
		end
	elseif (VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_GLOWING)) then
		promptBuf = promptBuf .. "Glowing\n"
	else
		promptBuf = promptBuf .. "Not Glowing\n"
	end

	if (VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_HAS_VILLAGE_ACCESS) and not VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_ACCEPTED_MELLICHAE)) then
		if (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
			promptBuf = promptBuf .. " \\#pcontrast1 " .. "Has Active Quest This Phase:" .. " \\#pcontrast2 YES\n"
		else
			promptBuf = promptBuf .. " \\#pcontrast1 " .. "Has Active Quest This Phase:" .. " \\#pcontrast2 NO\n"
		end

		if (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
			promptBuf = promptBuf .. " \\#pcontrast1 " .. "Has Completed Quest This Phase:" .. " \\#pcontrast2 YES\n"
		else
			promptBuf = promptBuf .. " \\#pcontrast1 " .. "Has Completed Quest This Phase:" .. " \\#pcontrast2 NO\n"
		end
	end

	promptBuf = promptBuf .. " \\#pcontrast1 " .. "Unlocked Branches:" .. " \\#pcontrast2 " .. VillageJediManagerCommon.getUnlockedBranchCount(pPlayer) .. "\n"

	local sui = SuiListBox.new("VillageGmSui", "mainCallback")
	sui.setTitle("Village GM Panel")
	sui.setPrompt(promptBuf)

	sui.add("FS Branch Management", "branchManagement" .. targetID)

	sui.sendTo(pPlayer)
end

function VillageGmSui.branchManagement(pPlayer, targetID)
	local pTarget = getSceneObject(targetID)

	if (pTarget == nil) then
		return
	end

	local sui = SuiListBox.new("VillageGmSui", "branchManagementCallback")
	sui.setTitle("Village GM Panel")
	sui.setPrompt("The statuses of " .. SceneObject(pTarget):getCustomObjectName() .. "'s force sensitive branches are listed below. Branches can be locked and unlocked from this window.")

	for i = 1, #VillageJediManagerCommon.forceSensitiveBranches, 1 do
		local rowString = getStringId("@quest/force_sensitive/utils:" .. VillageJediManagerCommon.forceSensitiveBranches[i])

		if (VillageJediManagerCommon.hasUnlockedBranch(pPlayer, VillageJediManagerCommon.forceSensitiveBranches[i])) then
			rowString = rowString .. " \\#pcontrast1 (UNLOCKED)"
		else
			rowString = rowString .. " \\#pcontrast2 (Locked)"
		end

		sui.add(rowString, VillageJediManagerCommon.forceSensitiveBranches[i] .. targetID)
	end

	sui.setOkButtonText("Lock/Unlock")
	sui.sendTo(pPlayer)
end

function VillageGmSui:branchManagementCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)
	local menuOption = suiPageData:getStoredData(tostring(args))

	local targetID = string.match(menuOption, '%d+')
	local branchName = string.gsub(menuOption, targetID, "")

	local pTarget = getSceneObject(targetID)

	if (pTarget == nil) then
		printLuaError("Unable to find player in VillageGmSui:branchManagementCallback using oid " .. targetID)
		return
	end

	if (VillageJediManagerCommon.hasUnlockedBranch(pTarget, branchName)) then
		CreatureObject(pPlayer):sendSystemMessage(SceneObject(pTarget):getCustomObjectName() .. "'s " .. getStringId("@quest/force_sensitive/utils:" .. branchName) .. " has been LOCKED.")
		CreatureObject(pTarget):sendSystemMessage("Your unlock of the branch " .. getStringId("@quest/force_sensitive/utils:" .. branchName) .. " has been removed by a GM.")
		CreatureObject(pTarget):removeScreenPlayState(2, "VillageUnlockScreenPlay:" .. branchName)
	else
		CreatureObject(pPlayer):sendSystemMessage(SceneObject(pTarget):getCustomObjectName() .. "'s " .. getStringId("@quest/force_sensitive/utils:" .. branchName) .. " has been UNLOCKED.")
		VillageJediManagerCommon.unlockBranch(pTarget, branchName)
	end

	VillageGmSui.branchManagement(pPlayer, targetID)
end

function VillageGmSui:getPhaseDuration(pPlayer)
	local eventID = getServerEventID("VillagePhaseChange")

	if (eventID == nil) then
		return
	end

	local timeLeft = getServerEventTimeLeft(eventID) / 1000
	local daysLeft = math.floor(timeLeft / (24 * 60 * 60))
	local hoursLeft = math.floor((timeLeft / 3600) % 24)
	local minutesLeft = math.floor((timeLeft / 60) % 60)
	local secondsLeft = math.floor(timeLeft % 60)

	return daysLeft .. "d " .. hoursLeft .. "h " .. minutesLeft .. "m " .. secondsLeft .. "s"
end
