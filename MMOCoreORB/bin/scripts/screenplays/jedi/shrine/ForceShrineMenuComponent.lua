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
		-- Crafting Trial
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

	if (CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02")) then
		menuResponse:addRadialMenuItem(121, 3, "@force_rank:recover_jedi_items") -- Recover Jedi Items
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
	elseif (selectedID == 121) then
		self:recoverRobe(pPlayer)
	end

	return 0

end

function ForceShrineMenuComponent:doMeditate(pObject, pPlayer)
	local rand = getRandomNumber(1, 15)
	local genericMessage = "@jedi_trials:force_shrine_wisdom_" .. rand
	local isJediPadawan = CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02")
	local isJediKnight = CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_03")
	local currentTrial = tonumber(readScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial"))
	local knightAvailable = CreatureObject(pPlayer):villageKnightPrereqsMet("")

	if (not isJediPadawan) then
		-- Unlock Padawan
		if (CreatureObject(pPlayer):hasScreenPlayState(64, "VillageJediProgression")) then
		-- TODO: Change to generic message after padawan trials complete if not qualified for Knight trials.
		elseif (CreatureObject(pPlayer):hasScreenPlayState(32, "VillageJediProgression")) then
			if (currentTrial == nil) then
				self:startJediPadawanTrials(pObject, pPlayer)
			elseif (currentTrial == 0) then
				self:startNextJediPadawanTrial(pObject, pPlayer)
			else
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
	sui.setOkButtonText("@jedi_trials:button_yes") -- Yes
	sui.setCancelButtonText("@jedi_trials:button_no") -- No
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

	local rand = getRandomNumber(1, #self.PadawanTrialQuests) -- 16 Jedi Padawan Trials
	local pScreenPlay = self:getScreenPlayFromTable(rand)

	pScreenPlay:startTrial(pPlayer)
	writeScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial", rand)
	writeScreenPlayData(pPlayer, "JediPadawanTrial", "StartedTrials", 1)
	writeScreenPlayData(pPlayer, "JediPadawanTrial", "numOfTrialsCompleted", 0)
end

function ForceShrineMenuComponent:showCurrentPadawanTrial(pObject, pPlayer, currentTrial)
	local pScreenPlay = self:getScreenPlayFromTable(currentTrial)
	pScreenPlay:showInfo(pPlayer, pObject)
end

function ForceShrineMenuComponent:startNextJediPadawanTrial(pObject, pPlayer)
	if (pPlayer == nil) then
		return
	end

	local trialsCompleted = tonumber(readScreenPlayData(pPlayer, "JediPadawanTrial", "numOfTrialsCompleted"))

	if (trialsCompleted == 8) then
	-- TODO: Crafting Trial, after implemented uncomment below lines.
	-- JediPadawanTrialCraftLightsaberScreenPlay:startTrial(pPlayer)
	else
		local uncompletedTrials = {}
		for i=1, #self.PadawanTrialQuests, 1 do
			if not (CreatureObject(pPlayer):hasScreenPlayState(8, self.PadawanTrialQuests[i][1])) then
				table.insert(uncompletedTrials, self.PadawanTrialQuests[i][1])
			end
		end
		if (#uncompletedTrials <= 0) then -- Finished all trials.
			-- TODO: Uncomment below after Trials work finished.
			-- self:unlockJediPadawan(pPlayer)
			-- CreatureObject(pPlayer):setScreenPlayState(64, "VillageJediProgression")
			-- Temporary message:
			CreatureObject(pPlayer):sendSystemMessage("You have completed all of the current Padawan Trials, but you are not a jedi yet...")
		else -- Still more.
			local rand = getRandomNumber(1, #uncompletedTrials)
			local screenPlayState = uncompletedTrials[rand]
			local screenPlay = self:getScreenplayFromGlobalTable(self.PadawanTrialQuests, screenPlayState)
			screenPlay:startTrial(pPlayer)
			local currentTrial = self:getCorrespondingTrialNumber(screenPlayState)
			writeScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial", currentTrial)
		end
	end

end

function ForceShrineMenuComponent:unlockJediPadawan(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local sui = SuiMessageBox.new("ForceShrineMenuComponent", "emptyCallback") -- No callback
	sui.setTitle("@jedi_trials:padawan_trials_title")
	sui.setPrompt("@jedi_trials:padawan_trials_completed")
	sui.sendTo(pPlayer)

	awardSkill(pPlayer, "force_title_jedi_rank_02")

	CreatureObject(pPlayer):playEffect("clienteffect/trap_electric_01.cef", "")
	CreatureObject(pPlayer):playMusicMessage("sound/music_become_jedi.snd")

	PlayerObject(pGhost):setJediState(2)


	if not (self:hasFullInventory(pPlayer)) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		local pItem = giveItem(pInventory, self.jediPadawanRobe, -1)
	else
		CreatureObject(pPlayer):sendSystemMessage("@jedi_spam:inventory_full_jedi_robe")
	end

	-- Find Trainer.
	PlayerObject(pGhost):findJediTrainer(pPlayer)
end

function ForceShrineMenuComponent:recoverRobe(pPlayer)
	if not (self:hasFullInventory(pPlayer)) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		local pItem = giveItem(pInventory, self.jediPadawanRobe, -1)
		CreatureObject(pPlayer):sendSystemMessage("@force_rank:items_recovered")
	else
		CreatureObject(pPlayer):sendSystemMessage("@jedi_spam:inventory_full_jedi_robe")
	end
end

function ForceShrineMenuComponent:hasFullInventory(pPlayer)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return true
	end

	return SceneObject(pInventory):isContainerFullRecursive()
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

-- Get a specific screenplay from the table.
function ForceShrineMenuComponent:getScreenPlayFromTable(number)
	return self.PadawanTrialQuests[number][2]
end

-- Get which number the trial is in the table.
function ForceShrineMenuComponent:getCorrespondingTrialNumber(screenPlayState)
	for i = 1, #self.PadawanTrialQuests do
		if (string.find(screenPlayState, self.PadawanTrialQuests[i][1]) ~= nil) then
			return i
		end
	end
end
