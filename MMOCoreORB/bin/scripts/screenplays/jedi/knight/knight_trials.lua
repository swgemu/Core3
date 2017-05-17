local ObjectManager = require("managers.object.object_manager")

KnightTrials = ScreenPlay:new {
	COUNCIL_LIGHT = 1,
	COUNCIL_DARK = 2,
}

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

	local trialsCompleted = JediTrials:getTrialsCompleted(pPlayer)

	if (trialsCompleted >= #knightTrialQuests) then
		CreatureObject(pPlayer):sendSystemMessage("You've finished all the currently completed Knight trials, please check back soon.")
		--JediTrials:unlockJediKnight(pPlayer)
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

	local trialString = getStringId("@jedi_trials:" .. trialData.trialName)
	shrinePrompt = shrinePrompt .. trialString

	if (trialData.huntGoal ~= nil and trialData.huntGoal > 0) then
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
	deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetCount")
	deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal")

	if (trialData.trialType == TRIAL_HUNT) then
		writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.huntTarget)
		writeScreenPlayData(pPlayer, "JediTrials", "huntTargetCount", 0)
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
	sui.setTitle("@jedi_trials:force_shrine_title")
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
		KnightTrials:doCouncilDecision(pPlayer, self.COUNCIL_LIGHT)
	elseif (eventIndex == 0) then -- Chose Dark Side
		KnightTrials:doCouncilDecision(pPlayer, self.COUNCIL_DARK)
	end
end

function KnightTrials:doCouncilDecision(pPlayer, choice)
	if (pPlayer == nil) then
		return
	end

	local playerFaction = CreatureObject(pPlayer):getFaction()
	local musicFile
	local successMsg

	if (choice == self.COUNCIL_LIGHT) then
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
	elseif (choice == self.COUNCIL_DARK) then
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

	writeScreenPlayData(pPlayer, "JediTrials", "CouncilChoice", choice)
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
		return 1
	end

	local trialData = knightTrialQuests[trialNumber]

	if (trialData.trialType ~= TRIAL_HUNT) then
		return 1
	end

	local huntTarget = readScreenPlayData(pPlayer, "JediTrials", "huntTarget")
	local targetCount = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetCount"))
	local targetGoal = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal"))

	if (targetCount == nil) then
		printLuaError("KnightTrials:notifyKilledHuntTarget, nil targetCount for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber .. " (player killed target: " .. SceneObject(pVictim):getObjectName() .. ").")
		return 1
	end

	if (targetGoal == nil) then
		printLuaError("KnightTrials:notifyKilledHuntTarget, nil targetGoal for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber .. " (player killed target: " .. SceneObject(pVictim):getObjectName() .. ").")
		return 1
	end

	if (SceneObject(pVictim):getObjectName() == huntTarget) then
		CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:knight_trials_progress")
		targetCount = targetCount + 1
		writeScreenPlayData(pPlayer, "JediTrials", "huntTargetCount", targetCount)

		if (targetCount >= targetGoal) then
			local trialsCompleted = JediTrials:getTrialsCompleted(pPlayer) + 1
			JediTrials:setTrialsCompleted(pPlayer, trialsCompleted)
			self:startNextKnightTrial(pPlayer)
			return 1
		end
	end

	return 0
end

function KnightTrials:showCurrentTrial(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)

	local trialsCompleted = JediTrials:getTrialsCompleted(pPlayer)
	
	if (trialsCompleted == trialNumber) then
		CreatureObject(pPlayer):sendSystemMessage("You've finished all the currently completed Knight trials, please check back soon.")
		return
	end

	local targetCount = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetCount"))
	local trialData = knightTrialQuests[trialNumber]

	if (trialData.trialType == TRIAL_COUNCIL) then
		self:sendCouncilChoiceSui(pPlayer)
		return
	end

	local shrinePrompt = getStringId("@jedi_trials:" .. trialData.trialName)

	if (trialData.huntGoal ~= nil and trialData.huntGoal > 0) then
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

		if (trialData.trialType == TRIAL_HUNT) then
			dropObserver(KILLEDCREATURE, "KnightTrials", "notifyKilledHuntTarget", pPlayer)
			createObserver(KILLEDCREATURE, "KnightTrials", "notifyKilledHuntTarget", pPlayer)
		end
	end
end
