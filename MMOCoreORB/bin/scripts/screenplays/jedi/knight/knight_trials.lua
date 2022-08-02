local ObjectManager = require("managers.object.object_manager")

KnightTrials = ScreenPlay:new {}

function KnightTrials:startKnightTrials(pPlayer)
	local randomShrinePlanet = JediTrials:getRandomDifferentShrinePlanet(pPlayer)
	local pRandShrine = JediTrials:getRandomShrineOnPlanet(randomShrinePlanet)

	if (pRandShrine == nil) then
		return
	end

	JediTrials:setStartedTrials(pPlayer)
	JediTrials:setTrialsCompleted(pPlayer, 0)
	JediTrials:setCurrentTrial(pPlayer, 0)
	self:setTrialShrine(pPlayer, pRandShrine)

	local suiPrompt = getStringId("@jedi_trials:knight_trials_intro_msg") .. " " .. getStringId("@jedi_trials:" .. randomShrinePlanet) .. " " .. getStringId("@jedi_trials:knight_trials_intro_msg_end")

	local sui = SuiMessageBox.new("KnightTrials", "noCallback")
	sui.setTitle("@jedi_trials:knight_trials_title")
	sui.setPrompt(suiPrompt)
	sui.setOkButtonText("@jedi_trials:button_close")
	sui.hideCancelButton()
	sui.sendTo(pPlayer)
end

function KnightTrials:noCallback(pPlayer, pSui, eventIndex, ...)
end

function KnightTrials:startNextKnightTrial(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerCouncil = JediTrials:getJediCouncil(pPlayer)

	if ((playerFaction == FACTIONIMPERIAL and playerCouncil == JediTrials.COUNCIL_LIGHT) or (playerFaction == FACTIONREBEL and playerCouncil == JediTrials.COUNCIL_DARK)) then
		self:giveWrongFactionWarning(pPlayer, playerCouncil)
		return
	end

	local trialsCompleted = JediTrials:getTrialsCompleted(pPlayer)

	if (trialsCompleted >= #knightTrialQuests) then
		dropObserver(KILLEDCREATURE, "KnightTrials", "notifyKilledHuntTarget", pPlayer)
		deleteScreenPlayData(pPlayer, "JediTrials", "huntTarget")
		deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetCount")
		deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal")
		JediTrials:unlockJediKnight(pPlayer)
		return
	end

	local shrinePrompt = ""

	if (trialsCompleted > 0) then
		shrinePrompt = getStringId("@jedi_trials:knight_trials_current_trial_complete") .. " "
	else
		self:unsetTrialShrine(pPlayer)
	end

	local currentTrial = trialsCompleted + 1
	JediTrials:setCurrentTrial(pPlayer, currentTrial)

	local trialData = knightTrialQuests[currentTrial]

	if (trialData.trialType == TRIAL_COUNCIL) then
		self:sendCouncilChoiceSui(pPlayer)
		return
	end

	local trialString = "@jedi_trials:" .. trialData.trialName

	if (trialData.trialType == TRIAL_HUNT_FACTION) then
		local councilChoice = JediTrials:getJediCouncil(pPlayer)

		if (councilChoice == JediTrials.COUNCIL_LIGHT) then
			trialString = trialString .. "_light"
		else
			trialString = trialString .. "_dark"
		end
	end

	trialString = getStringId(trialString)

	shrinePrompt = shrinePrompt .. trialString

	if (trialData.huntGoal ~= nil and trialData.huntGoal > 1) then
		shrinePrompt = shrinePrompt .. " 0 of " .. trialData.huntGoal
	end

	local sui = SuiMessageBox.new("KnightTrials", "noCallback")
	sui.setTitle("@jedi_trials:knight_trials_title")
	sui.setPrompt(shrinePrompt)
	sui.setOkButtonText("@jedi_trials:button_close")
	sui.hideCancelButton()
	sui.sendTo(pPlayer)

	dropObserver(KILLEDCREATURE, "KnightTrials", "notifyKilledHuntTarget", pPlayer)
	deleteScreenPlayData(pPlayer, "JediTrials", "huntTarget")
	deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal")
	writeScreenPlayData(pPlayer, "JediTrials", "huntTargetCount", 0)

	if (trialData.trialType == TRIAL_HUNT or trialData.trialType == TRIAL_HUNT_FACTION) then
		if (trialData.trialType == TRIAL_HUNT) then
			writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.huntTarget)
		else
			local councilChoice = JediTrials:getJediCouncil(pPlayer)

			if (councilChoice == JediTrials.COUNCIL_LIGHT) then
				writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.rebelTarget)
			else
				writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.imperialTarget)
			end
		end

		writeScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal", trialData.huntGoal)
		createObserver(KILLEDCREATURE, "KnightTrials", "notifyKilledHuntTarget", pPlayer)
	end
end

function KnightTrials:sendCouncilChoiceSui(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local sui = SuiMessageBox.new("KnightTrials", "handleCouncilChoice")
	sui.setPrompt("@jedi_trials:council_choice_msg")
	sui.setTitle("@jedi_trials:knight_trials_title")
	sui.setCancelButtonText("@jedi_trials:button_cancel") -- Cancel
	sui.setOtherButtonText("@jedi_trials:button_lightside") -- 	Light Jedi Council
	sui.setOkButtonText("@jedi_trials:button_darkside") -- Dark Jedi Council
	-- Other Button setup subscribe
	sui.setProperty("btnRevert", "OnPress", "RevertWasPressed=1\r\nparent.btnOk.press=t")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "btnRevert", "RevertWasPressed")

	sui.sendTo(pPlayer)
end

function KnightTrials:handleCouncilChoice(pPlayer, pSui, eventIndex, ...)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local args = {...}
	local lightSide = args[1]

	if (cancelPressed) then
		CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:council_choice_delayed")
		return
	elseif (lightSide ~= nil) then -- Chose Light Side
		KnightTrials:doCouncilDecision(pPlayer, JediTrials.COUNCIL_LIGHT)
	elseif (eventIndex == 0) then -- Chose Dark Side
		KnightTrials:doCouncilDecision(pPlayer, JediTrials.COUNCIL_DARK)
	end
end

function KnightTrials:doCouncilDecision(pPlayer, choice)
	if (pPlayer == nil) then
		return
	end

	if (not JediTrials:isEligibleForKnightTrials(pPlayer)) then
		self:failTrialsIneligible(pPlayer)
		return
	end

	local playerFaction = CreatureObject(pPlayer):getFaction()
	local musicFile
	local successMsg

	if (choice == JediTrials.COUNCIL_LIGHT) then
		if (playerFaction == FACTIONIMPERIAL) then
			local sui = SuiMessageBox.new("KnightTrials", "noCallback")
			sui.setTitle("@jedi_trials:knight_trials_title")
			sui.setPrompt("@jedi_trials:faction_wrong_choice_light")
			sui.setOkButtonText("@jedi_trials:button_close")
			sui.hideCancelButton()
			sui.sendTo(pPlayer)
			return
		end

		musicFile = "sound/music_themequest_victory_rebel.snd"
		successMsg = "@jedi_trials:council_chosen_light"
	elseif (choice == JediTrials.COUNCIL_DARK) then
		if (playerFaction == FACTIONREBEL) then
			local sui = SuiMessageBox.new("KnightTrials", "noCallback")
			sui.setTitle("@jedi_trials:knight_trials_title")
			sui.setPrompt("@jedi_trials:faction_wrong_choice_dark")
			sui.setOkButtonText("@jedi_trials:button_close")
			sui.hideCancelButton()
			sui.sendTo(pPlayer)
			return
		end

		musicFile = "sound/music_themequest_victory_imperial.snd"
		successMsg = "@jedi_trials:council_chosen_dark"
	end

	JediTrials:setJediCouncil(pPlayer, choice)
	CreatureObject(pPlayer):playMusicMessage(musicFile)
	CreatureObject(pPlayer):sendSystemMessage(successMsg)
	local trialsCompleted = JediTrials:getTrialsCompleted(pPlayer) + 1
	JediTrials:setTrialsCompleted(pPlayer, trialsCompleted)
	self:startNextKnightTrial(pPlayer)
end

function KnightTrials:notifyKilledHuntTarget(pPlayer, pVictim)
	if (pVictim == nil or pPlayer == nil) then
		return 0
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)

	if (trialNumber <= 0) then
		printLuaError("KnightTrials:notifyKilledHuntTarget, invalid trial for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber)
		return 1
	end

	local trialData = knightTrialQuests[trialNumber]

	if (trialData.trialType ~= TRIAL_HUNT and trialData.trialType ~= TRIAL_HUNT_FACTION) then
		return 1
	end

	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerCouncil = JediTrials:getJediCouncil(pPlayer)

	if ((playerFaction == FACTIONIMPERIAL and playerCouncil == JediTrials.COUNCIL_LIGHT) or (playerFaction == FACTIONREBEL and playerCouncil == JediTrials.COUNCIL_DARK)) then
		self:giveWrongFactionWarning(pPlayer, playerCouncil)
		return 0
	end

	local huntTarget = readScreenPlayData(pPlayer, "JediTrials", "huntTarget")
	local targetCount = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetCount"))
	local targetGoal = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal"))

	if (targetCount == nil) then
		printLuaError("KnightTrials:notifyKilledHuntTarget, nil targetCount for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber .. " (player killed target: " .. SceneObject(pVictim):getObjectName() .. "). Setting to 0.")
		writeScreenPlayData(pPlayer, "JediTrials", "huntTargetCount", 0)
		targetCount = 0
	end

	if (targetGoal == nil) then
		printLuaError("KnightTrials:notifyKilledHuntTarget, nil targetGoal for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber .. " (player killed target: " .. SceneObject(pVictim):getObjectName() .. "). Setting to " .. trialData.huntGoal .. ".")
		writeScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal", trialData.huntGoal)
		targetGoal = trialData.huntGoal
	end

	if (huntTarget == nil or huntTarget == "") then
		local newTarget = ""
		if (trialData.trialType == TRIAL_HUNT) then
			writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.huntTarget)
			newTarget = trialData.huntTarget
		else
			local councilChoice = JediTrials:getJediCouncil(pPlayer)

			if (councilChoice == JediTrials.COUNCIL_LIGHT) then
				writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.rebelTarget)
				newTarget = trialData.rebelTarget
			else
				writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.imperialTarget)
				newTarget = trialData.imperialTarget
			end
		end

		printLuaError("KnightTrials:notifyKilledHuntTarget, nil huntTarget for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber .. " (player killed target: " .. SceneObject(pVictim):getObjectName() .. "). Setting to " .. newTarget .. ".")
		huntTarget = newTarget
	end

	if (SceneObject(pVictim):getZoneName() ~= SceneObject(pPlayer):getZoneName() or not CreatureObject(pPlayer):isInRangeWithObject(pVictim, 80)) then
		return 0
	end

	local targetList = HelperFuncs:splitString(huntTarget, ";")

	if (huntTarget == SceneObject(pVictim):getObjectName() or HelperFuncs:tableContainsValue(targetList, SceneObject(pVictim):getObjectName())) then
		CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:knight_trials_progress")
		targetCount = targetCount + 1
		writeScreenPlayData(pPlayer, "JediTrials", "huntTargetCount", targetCount)

		if (targetCount >= targetGoal) then
			if (not JediTrials:isEligibleForKnightTrials(pPlayer)) then
				self:failTrialsIneligible(pPlayer)
				return 1
			end
			local trialsCompleted = JediTrials:getTrialsCompleted(pPlayer) + 1
			JediTrials:setTrialsCompleted(pPlayer, trialsCompleted)
			self:startNextKnightTrial(pPlayer)
			return 1
		end
	end

	return 0
end

function KnightTrials:failTrialsIneligible(pPlayer)
	if (pPlayer == nil or JediTrials:isEligibleForKnightTrials(pPlayer)) then
		return
	end

	local sui = SuiMessageBox.new("JediTrials", "emptyCallback")
	sui.setTitle("@jedi_trials:knight_trials_title")
	sui.setPrompt("@jedi_trials:knight_trials_being_removed")
	sui.setOkButtonText("@jedi_trials:button_close")
	sui.sendTo(pPlayer)

	JediTrials:resetTrialData(pPlayer, "knight")
	self:unsetTrialShrine(pPlayer)
end

function KnightTrials:showCurrentTrial(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)

	local trialsCompleted = JediTrials:getTrialsCompleted(pPlayer)

	if (trialsCompleted == trialNumber) then
		return
	end

	local trialData = knightTrialQuests[trialNumber]

	if (trialData.trialType == TRIAL_COUNCIL) then
		self:sendCouncilChoiceSui(pPlayer)
		return
	end

	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerCouncil = JediTrials:getJediCouncil(pPlayer)

	if (trialData.trialType == TRIAL_HUNT or trialData.trialType == TRIAL_HUNT_FACTION) then
		if ((playerFaction == FACTIONIMPERIAL and playerCouncil == JediTrials.COUNCIL_LIGHT) or (playerFaction == FACTIONREBEL and playerCouncil == JediTrials.COUNCIL_DARK)) then
			self:giveWrongFactionWarning(pPlayer, playerCouncil)
			return
		end
	end

	local huntTarget = readScreenPlayData(pPlayer, "JediTrials", "huntTarget")
	local targetCount = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetCount"))
	local targetGoal = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal"))

	if (targetCount == nil) then
		printLuaError("KnightTrials:showCurrentTrial, nil targetCount for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber .. ". Setting to 0.")
		writeScreenPlayData(pPlayer, "JediTrials", "huntTargetCount", 0)
		targetCount = 0
	end

	if (targetGoal == nil) then
		printLuaError("KnightTrials:showCurrentTrial, nil targetGoal for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber .. ". Setting to " .. trialData.huntGoal .. ".")
		writeScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal", trialData.huntGoal)
		targetGoal = trialData.huntGoal
	end

	if (huntTarget == nil or huntTarget == "") then
		local newTarget = ""
		if (trialData.trialType == TRIAL_HUNT) then
			writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.huntTarget)
			newTarget = trialData.huntTarget
		else
			local councilChoice = JediTrials:getJediCouncil(pPlayer)

			if (councilChoice == JediTrials.COUNCIL_LIGHT) then
				writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.rebelTarget)
				newTarget = trialData.rebelTarget
			else
				writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.imperialTarget)
				newTarget = trialData.imperialTarget
			end
		end

		printLuaError("KnightTrials:showCurrentTrial, nil huntTarget for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber .. ". Setting to " .. newTarget .. ".")
		huntTarget = newTarget
	end

	local shrinePrompt = "@jedi_trials:" .. trialData.trialName

	if (trialData.trialType == TRIAL_HUNT_FACTION) then
		local councilChoice = JediTrials:getJediCouncil(pPlayer)

		if (councilChoice == JediTrials.COUNCIL_LIGHT) then
			shrinePrompt = shrinePrompt .. "_light"
		else
			shrinePrompt = shrinePrompt .. "_dark"
		end
	end

	shrinePrompt = getStringId(shrinePrompt)

	if (trialData.huntGoal ~= nil and trialData.huntGoal > 1) then
		shrinePrompt = shrinePrompt .. " " .. targetCount .. " of " .. trialData.huntGoal
	end

	local sui = SuiMessageBox.new("KnightTrials", "noCallback")
	sui.setTitle("@jedi_trials:knight_trials_title")
	sui.setPrompt(shrinePrompt)
	sui.setOkButtonText("@jedi_trials:button_close")
	sui.hideCancelButton()
	sui.sendTo(pPlayer)
end

function KnightTrials:setTrialShrine(pPlayer, pShrine)
	writeScreenPlayData(pPlayer, "JediTrials", "trialShrineID", SceneObject(pShrine):getObjectID())
end

function KnightTrials:unsetTrialShrine(pPlayer, pShrine)
	deleteScreenPlayData(pPlayer, "JediTrials", "trialShrineID")
end

function KnightTrials:getTrialShrine(pPlayer)
	local shrineID = tonumber(readScreenPlayData(pPlayer, "JediTrials", "trialShrineID"))

	if (shrineID == nil or shrineID == 0) then
		return nil
	end

	local pShrine = getSceneObject(shrineID)

	return pShrine
end

function KnightTrials:onPlayerLoggedIn(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (JediTrials:isEligibleForKnightTrials(pPlayer) and not JediTrials:isOnKnightTrials(pPlayer)) then
		KnightTrials:startKnightTrials(pPlayer)
	elseif (JediTrials:isOnKnightTrials(pPlayer)) then
		local trialNumber = JediTrials:getCurrentTrial(pPlayer)

		if (trialNumber <= 0) then
			return
		end

		local trialData = knightTrialQuests[trialNumber]

		if (trialData.trialType == TRIAL_HUNT or trialData.trialType == TRIAL_HUNT_FACTION) then
			dropObserver(KILLEDCREATURE, "KnightTrials", "notifyKilledHuntTarget", pPlayer)
			createObserver(KILLEDCREATURE, "KnightTrials", "notifyKilledHuntTarget", pPlayer)
		end
	end
end

function KnightTrials:giveWrongFactionWarning(pPlayer, councilType)
	if (pPlayer == nil) then
		return
	end

	local sui = SuiMessageBox.new("KnightTrials", "noCallback")
	sui.setTitle("@jedi_trials:knight_trials_title")

	if (councilType == JediTrials.COUNCIL_LIGHT) then
		sui.setPrompt("@jedi_trials:faction_wrong_light") -- To become a Light Jedi, you cannot be a member of the Empire. You must revoke your status as an Imperial in order to continue.
	else
		sui.setPrompt("@jedi_trials:faction_wrong_dark") -- To become a Dark Jedi, you cannot be a member of the Rebel Alliance. You must revoke your status as a Rebel in order to continue.
	end

	sui.setOkButtonText("@jedi_trials:button_close")
	sui.hideCancelButton()
	sui.sendTo(pPlayer)
end

function KnightTrials:resetCompletedTrialsToStart(pPlayer)
	if (pPlayer == nil) then
		return
	end

	JediTrials:resetTrialData(pPlayer, "knight")
	deleteScreenPlayData(pPlayer, "KnightTrials", "completedTrials")

	JediTrials:setStartedTrials(pPlayer)
	JediTrials:setTrialsCompleted(pPlayer, 0)
	JediTrials:setCurrentTrial(pPlayer, 0)
end
