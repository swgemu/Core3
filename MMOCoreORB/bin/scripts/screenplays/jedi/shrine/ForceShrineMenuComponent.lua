local ObjectManager = require("managers.object.object_manager")
local jediPadawanRobe = "object/tangible/wearables/robe/robe_jedi_padawan.iff"
local JediPadawanTrialArchitechScreenPlay = require("screenplays.jedi.padawan.trials.trial_architect")
local JediPadawanTrialArtistScreenPlay = require("screenplays.jedi.padawan.trials.trial_artist")

-- How many trials are enabled.
local maxTrials = 2

ForceShrineMenuComponent = {
JediPadawanTrialArchitechScreenPlay,
JediPadawanTrialArtistScreenPlay
--[[ *DISABLED UNTIL IMPLEMENTED*
JediPadawanTrialBadCatScreenPlay,
JediPadawanTrialChefScreenPlay,
JediPadawanTrialOldMusicianScreenPlay,
JediPadawanTrialPannaqaScreenPlay,
JediPadawanTrialPeoplesSoldierScreenPlay,
JediPadawanTrialSobStoryScreenPlay,
JediPadawanTrialSpiceMomScreenPlay,
JediPadawanTrialSurveyorScreenPlay,
JediPadawanTrialPoliticianScreenPlay,
JediPadawanTrialTheRingScreenPlay,
JediPadawanTrialBazNitchScreenPlay,
JediPadawanTrialSludgePantherScreenPlay,
JediPadawanTrialFalumpasetScreenPlay,
JediPadawanTrialCraftLightsaberScreenPlay
]] }

-- State: JediPadawanTrials
-- 0 (Not started)
-- 1 (Started)

-- State: JediPadawanTrial
-- (number of trials table index)

function ForceShrineMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	if (CreatureObject(pPlayer):hasSkill("force_title_jedi_novice")) then
		menuResponse:addRadialMenuItem(120, 3, "@jedi_trials:meditate") -- Meditate

		if (CreatureObject(pPlayer):hasScreenPlayState("JediPadawanTrials", 1)) then
			menuResponse:addRadialMenuItem(121, 3, "@jedi_trials:button_restart") -- Restart Current Trial
			menuResponse:addRadialMenuItem(122, 3, "@jedi_trials:button_abort_padawan") -- Quit Padawan Trials
		end
	end

end

function ForceShrineMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	if (selectedID == 120) then
		if (CreatureObject(pPlayer):getPosture() ~= CROUCHED) then
			CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:show_respect") -- Must respect
			return 0
		else
			ForceShrineMenuComponent:doMeditate(pObject, pPlayer)
		end
	elseif (selectedID == 121) then
		ForceShrineMenuComponent:restartCurrentPadawanTrial(pObject, pPlayer)
	elseif (selectedID == 122) then
		ForceShrineMenuComponent:quitPadawanTrials(pObject, pPlayer)
	end

end

function ForceShrineMenuComponent:doMeditate(pObject, pPlayer)
	local rand = getRandomNumber(14) + 1
	local genericMessage = "@jedi_trials:force_shrine_wisdom_" .. rand
	local theVillageJediProgression = CreatureObject(pPlayer):getScreenPlayState("VillageJediProgression")
	local isJediPadawan = CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02")
	local isJediKnight = CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_03")
	local isPadawanTrialsStarted = CreatureObject(pPlayer):hasScreenPlayState("JediPadawanTrials", 1)

	if (not isJediPadawan) then
		-- Unlock Padawan
		if (theVillageJediProgression == 64) then
			ForceShrineMenuComponent:unlockJediPadawan(pPlayer)
		elseif (theVillageJediProgression == 32) then
			if (not isPadawanTrialsStarted) then
				ForceShrineMenuComponent:startJediPadawanTrials(pObject, pPlayer)
			else
				ForceShrineMenuComponent:startNextJediPadawanTrial(pObject, pPlayer)
			end
			--[[elseif (isJediPadawan and not isJediKnight) then
		ForceShrineMenuComponent:startJediKnightTrials(pObject, pPlayer)
		]]
		else
			CreatureObject(pPlayer):sendSystemMessage(genericMessage)
		end
	end
end

function ForceShrineMenuComponent:startJediPadawanTrials(pObject, pPlayer)
	local sui = SuiMessageBox.new("ForceShrineMenuComponent", "jediPadawanTrialsStartCallback")
	sui.setTargetNetworkId(SceneObject(pObject):getObjectID())
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_start_query")
	sui.sendTo(pPlayer)
end

function ForceShrineMenuComponent:restartCurrentPadawanTrial(pObject, pPlayer)
	local sui = SuiMessageBox.new("ForceShrineMenuComponent", "jediPadawanTrialsRestartCallback")
	sui.setTargetNetworkId(SceneObject(pObject):getObjectID())
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_restart_confirmation")
	sui.sendTo(pPlayer)
end

function ForceShrineMenuComponent:quitPadawanTrials(pObject, pPlayer)
	local sui = SuiMessageBox.new("ForceShrineMenuComponent", "jediPadawanTrialsAbortCallback")
	sui.setTargetNetworkId(SceneObject(pObject):getObjectID())
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_abort_confirmation")
	sui.sendTo(pPlayer)
end

function ForceShrineMenuComponent:jediPadawanTrialsStartCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local rand = getRandomNumber(1, maxTrials) -- 16 Jedi Padawan Trials, excluding the guaranteed 9th one.
	local TrialScreenPlay = self[rand]
	
	TrialScreenPlay:start(pPlayer)
	CreatureObject(pPlayer):setScreenPlayState("JediPadawanTrials", rand)
	CreatureObject(pPlayer):setScreenPlayState("JediPadawanTrial", 1)
end

function ForceShrineMenuComponent:jediPadawanTrialsRestartCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_trial_restarted")
	local trialNumber = CreatureObject(pPlayer):getScreenPlayState("JediPadawanTrial")
	local pScreenPlay = self[trialNumber]
	pScreenPlay:start(pPlayer)

end

function ForceShrineMenuComponent:jediPadawanTrialsAbortCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_aborted")
	CreatureObject(pPlayer):setScreenPlayState("JediPadawanTrial", 0)
	CreatureObject(pPlayer):setScreenPlayState("JediPadawanTrials", 0)

end

function ForceShrineMenuComponent:startNextJediPadawanTrial(pObject, pPlayer)
	if (pPlayer == nil) then
		return
	end

	-- 16 Jedi Padawan Trials, excluding the guaranteed 9th one.
	local TrialScreenPlay = nil
	for i = 1, maxTrials, 1 do
		local rand = getRandomNumber(i, maxTrials)
		if not (CreatureObject(pPlayer):hasScreenPlayState(tostring(trials[rand]), 8)) then
			TrialScreenPlay = self[rand]
			CreatureObject(pPlayer):setScreenPlayState("JediPadawanTrial", rand)
			break
		end
	end

	if (TrialScreenPlay ~= nil) then
		TrialScreenPlay:start(pPlayer)
	end

end

function ForceShrineMenuComponent:unlockJediPadawan(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local ghost = CreatureObject(pPlayer):getPlayerObject()

	if (ghost == nil) then
		return
	end

	local sui = SuiMessageBox.new("", "") -- No callback
	sui.setTitle("@jedi_trials:padawan_trials_title")
	sui.setPrompt("@jedi_trials:padawan_trials_completed")
	sui.sendTo(pPlayer)

	awardSkill(pPlayer, "force_title_jedi_rank_02")

	CreatureObject(pPlayer):playEffect("clienteffect/trap_electric_01.cef", "")
	CreatureObject(pPlayer):playMusicMessage("sound/music_become_jedi.snd")

	PlayerObject(ghost):setJediState(2)

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	local pItem = giveItem(pInventory, jediPadawanRobe, -1)
	if pItem ~= nil then
		SceneObject(pItem):sendTo(pPlayer)
	end

	-- Find Trainer.
	--findJediTrainer(pPlayer)
end
