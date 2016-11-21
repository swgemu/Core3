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
		else
			self:doMeditate(pObject, pPlayer)
		end
	end

	return 0

end

function ForceShrineMenuComponent:doMeditate(pObject, pPlayer)
	local rand = getRandomNumber(1, 15)
	local genericMessage = "@jedi_trials:force_shrine_wisdom_" .. rand
	local isJediPadawan = CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02")
	local isJediKnight = CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_03")
	local currentTrial = readScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial")
	local knightAvailable = CreatureObject(pPlayer):villageKnightPrereqsMet("")

	if (not isJediPadawan) then
		-- Unlock Padawan
		if (CreatureObject(pPlayer):hasScreenPlayState(64, "VillageJediProgression")) then
			self:unlockJediPadawan(pPlayer)
		elseif (CreatureObject(pPlayer):hasScreenPlayState(32, "VillageJediProgression")) then
			if (currentTrial == nil) then
				self:startJediPadawanTrials(pObject, pPlayer)
			elseif (currentTrial == 0)then
				self:startNextJediPadawanTrial(pObject, pPlayer)
			elseif (currentTrial ~= 0 and currentTrial ~= nil) then
				self:showCurrentPadawanTrial(pObject, pPlayer, currentTrial)
			end
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
	writeScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial", rand)
	writeScreenPlayData(pPlayer, "JediPadawanTrial", "StartedTrials", 1)
end

function ForceShrineMenuComponent:showCurrentPadawanTrial(pObject, pPlayer)
	local trialQuest = getQuestStatus(SceneObject(pPlayer):getObjectID() .. ":padawan:trial")
	local pScreenPlay = self:getScreenplayFromGlobalTable(self.PadawanTrialQuests, trialQuest)
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
				writeScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial", i)
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
	sui.setTitle("@jedi_trials:padawan_trcurrentPadawanTrialials_title")
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
	PlayerObject(ghost):findJediTrainer(pPlayer)
end

function ForceShrineMenuComponent:emptyCallback(pPlayer)
-- Do nothing.
end

-- Generic search function to match the screenplay state with the screenplay.
function ForceShrineMenuComponent:getScreenplayFromGlobalTable(table, element)
	for i = 1, #table do
		if (string.find(element, table[i][1]) ~= nil) then
			return table[i][2]
		end
	end
end
