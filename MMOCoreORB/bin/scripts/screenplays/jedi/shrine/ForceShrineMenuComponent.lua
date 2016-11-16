ForceShrineMenuComponent = {
	-- Enabled Quests.
	PadawanTrialQuests = {
		{"JediPadawanTrialArchitectScreenPlay", JediPadawanTrialArchitectScreenPlay},
		{"JediPadawanTrialArtistScreenPlay", JediPadawanTrialArtistScreenPlay}
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
		JediPadawanTrialCraftLightsaberScreenPlay... Note this should always be the 'inbetween' trial, e.g. 9 out of 16.
	]]
	},

	jediPadawanRobe = "object/tangible/wearables/robe/robe_jedi_padawan.iff"
}

-- State: JediPadawanTrials
-- 0 (Not started)
-- 1 (Started)

function ForceShrineMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	if (CreatureObject(pPlayer):hasSkill("force_title_jedi_novice")) then
		menuResponse:addRadialMenuItem(120, 3, "@jedi_trials:meditate") -- Meditate
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
	end

end

function ForceShrineMenuComponent:doMeditate(pObject, pPlayer)
	local rand = getRandomNumber(1, 15)
	local genericMessage = "@jedi_trials:force_shrine_wisdom_" .. rand
	local isJediPadawan = CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02")
	local isJediKnight = CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_03")
	local isPadawanTrialsStarted = CreatureObject(pPlayer):hasScreenPlayState(1, "JediPadawanTrials")
	local currentPadawanTrial = getQuestStatus(SceneObject(pPlayer):getObjectID() .. ":padawan:trial")
	local knightAvailable = CreatureObject(pPlayer):villageKnightPrereqsMet("")

	if (not isJediPadawan) then
		-- Unlock Padawan
		if (CreatureObject(pPlayer):getScreenPlayState(64, "VillageJediProgression") == 1) then
			ForceShrineMenuComponent:unlockJediPadawan(pPlayer)
		elseif (CreatureObject(pPlayer):getScreenPlayState(32, "VillageJediProgression") == 1) then
			if (not isPadawanTrialsStarted) then
				ForceShrineMenuComponent:startJediPadawanTrials(pObject, pPlayer)
			elseif (isPadawanTrialsStarted) and (currentPadawanTrial == nil) then
				ForceShrineMenuComponent:startNextJediPadawanTrial(pObject, pPlayer)
			elseif (isPadawanTrialsStarted) and (currentPadawanTrial ~= nil) then
				ForceShrineMenuComponent:showCurrentPadawanTrial(pObject, pPlayer, currentPadawanTrial)
			end
			--[[elseif (isJediPadawan and not isJediKnight and knightAvailable) then
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

function ForceShrineMenuComponent:jediPadawanTrialsStartCallback(pPlayer, pSui, eventIndex, args)
	if (pPlayer == nil) then
		return
	end


	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local rand = getRandomNumber(1,  #self.PadawanTrialQuests) -- 16 Jedi Padawan Trials
	local TrialScreenPlay = self.PadawanTrialQuests[rand][2]

	TrialScreenPlay:start(pPlayer)
	setQuestStatus(SceneObject(pPlayer):getObjectID() .. ":padawan:trial", self.PadawanTrialQuests[rand][1])
	CreatureObject(pPlayer):setScreenPlayState(1, "JediPadawanTrials")
end

function ForceShrineMenuComponent:showCurrentPadawanTrial(pObject, pPlayer)

	local trialQuest = getQuestStatus(SceneObject(pPlayer):getObjectID() .. ":padawan:trial")
	local pScreenPlay = self:getScreenplayStringFromTable(self.PadawanTrialQuests, trialQuest)
	pScreenPlay:showInfo(pPlayer, pObject)
end

function ForceShrineMenuComponent:startNextJediPadawanTrial(pObject, pPlayer)
	if (pPlayer == nil) then
		return
	end


	for i=1, #self.PadawanTrialQuests, 1 do
		if not (CreatureObject(pPlayer):hasScreenPlayState(8, self.PadawanTrialQuests[i][1])) then
			if (i == #self.PadawanTrialQuests / 2) then -- Let's guarantee the 9th (midway trial) is the lightsaber craft.
				break
				-- TODO: Crafting Trial, after implemented uncomment below lines.
				--JediPadawanTrialCraftLightsaberScreenPlay:start(pPlayer)
				--setQuestStatus(SceneObject(pPlayer):getObjectID() .. ":padawan:trial", "JediPadawanTrialCraftLightsaberScreenPlay")
			else
				self.PadawanTrialQuests[i][2]:start(pPlayer)
				setQuestStatus(SceneObject(pPlayer):getObjectID() .. ":padawan:trial", self.PadawanTrialQuests[i][1])
			end
		end
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

	local sui = SuiMessageBox.new("ForceShrineMenuComponent", "emptyCallback") -- No callback
	sui.setTitle("@jedi_trials:padawan_trials_title")
	sui.setPrompt("@jedi_trials:padawan_trials_completed")
	sui.sendTo(pPlayer)

	awardSkill(pPlayer, "force_title_jedi_rank_02")

	CreatureObject(pPlayer):playEffect("clienteffect/trap_electric_01.cef", "")
	CreatureObject(pPlayer):playMusicMessage("sound/music_become_jedi.snd")

	PlayerObject(ghost):setJediState(2)

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	local pItem = giveItem(pInventory, self.jediPadawanRobe, -1)
	if pItem ~= nil then
		SceneObject(pItem):sendTo(pPlayer)
	end

	-- Find Trainer.
	findJediTrainer(pPlayer)
end

function ForceShrineMenuComponent:emptyCallback(pPlayer)
-- Do nothing.
end

-- Generic search function to match the screenplay state with the screenplay.
function ForceShrineMenuComponent:getScreenplayStringFromTable(table, element)
	for i = 1, #table do
		if (string.find(element, table[i][1]) ~= nil) then
			return table[i][2]
		end
	end
end
