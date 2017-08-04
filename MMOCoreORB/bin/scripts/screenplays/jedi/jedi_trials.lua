JediTrials = ScreenPlay:new {
	padawanTrialsEnabled = true,
	knightTrialsEnabled = true,

	-- Object ID's of the various force shrines.
	forceShrineIds = {
		corellia = { 7345554, 7345568, 7345533, 7345540, 7345561 },
		dantooine = { 6045480, 6045501, 6045522, 6045494, 6045508 },
		dathomir = { 7325403, 7325410, 7325417, 7325424, 7325438 },
		endor = { 7255422, 7255429, 7255436, 7255443, 7255457 },
		lok = { 6625591, 6625598, 6625605, 6625619, 6625626 },
		naboo = { 7525395, 7525400, 7525447, 7525454 },
		rori = { 6885431, 6885438, 6885445, 6885452, 6885459 },
		talus = { 6535834, 6535841, 6535869, 6535891 },
		tatooine = { 5996497, 5996504, 5996539, 5996546, 5996560 },
		yavin4 = { 6845418, 6845425, 7665623, 7665630 }
	},

	shrinePlanets = { "corellia", "dantooine", "dathomir", "endor", "lok", "naboo", "rori", "talus", "tatooine", "yavin4" },

	COUNCIL_LIGHT = 1,
	COUNCIL_DARK = 2,
}

function JediTrials:isEligibleForPadawanTrials(pPlayer)
	if (pPlayer == nil or not self.padawanTrialsEnabled) then
		return false
	end

	local learnedBranches = VillageJediManagerCommon.getLearnedForceSensitiveBranches(pPlayer)

	return CreatureObject(pPlayer):hasScreenPlayState(32, "VillageJediProgression") and not CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02") and learnedBranches >= 6 and tonumber(readScreenPlayData(pPlayer, "PadawanTrials", "completedTrials")) ~= 1
end

function JediTrials:isOnPadawanTrials(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return tonumber(readScreenPlayData(pPlayer, "PadawanTrials", "startedTrials")) == 1 and tonumber(readScreenPlayData(pPlayer, "PadawanTrials", "completedTrials")) ~= 1
end

function JediTrials:isEligibleForKnightTrials(pPlayer)
	if (pPlayer == nil or not self.knightTrialsEnabled) then
		return false
	end

	if (CreatureObject(pPlayer):hasSkill("force_rank_light_novice") or CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) or tonumber(readScreenPlayData(pPlayer, "KnightTrials", "completedTrials")) == 1 then
		return false
	end

	return CreatureObject(pPlayer):villageKnightPrereqsMet("")
end

function JediTrials:isOnKnightTrials(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return tonumber(readScreenPlayData(pPlayer, "KnightTrials", "startedTrials")) == 1 and tonumber(readScreenPlayData(pPlayer, "KnightTrials", "completedTrials")) ~= 1
end

function JediTrials:onPlayerLoggedIn(pPlayer)
	if (CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02") and tonumber(readScreenPlayData(pPlayer, "PadawanTrials", "completedTrials")) ~= 1) then
		writeScreenPlayData(pPlayer, "PadawanTrials", "completedTrials", 1)
	end

	if (CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_03") and tonumber(readScreenPlayData(pPlayer, "KnightTrials", "completedTrials")) ~= 1) then
		writeScreenPlayData(pPlayer, "KnightTrials", "completedTrials", 1)
	end

	if (self:isOnPadawanTrials(pPlayer) or self:isOnKnightTrials(pPlayer)) then
		dropObserver(SKILLREMOVED, "JediTrials", "droppedSkillDuringTrials", pPlayer)
		createObserver(SKILLREMOVED, "JediTrials", "droppedSkillDuringTrials", pPlayer)
	end

	if (self:isOnPadawanTrials(pPlayer)) then
		PadawanTrials:onPlayerLoggedIn(pPlayer)
	end

	KnightTrials:onPlayerLoggedIn(pPlayer)
end

function JediTrials:droppedSkillDuringTrials(pPlayer, pSkill)
	if (pPlayer == nil) then
		return 1
	end

	if (pSkill == nil) then
		return 0
	end

	local droppedSkill = LuaSkill(pSkill)
	local skillName = droppedSkill:getName()

	if (self:isOnPadawanTrials(pPlayer) and string.find(skillName, "force_sensitive_") and not self:isEligibleForPadawanTrials(pPlayer)) then
		local sui = SuiMessageBox.new("JediTrials", "emptyCallback")
		sui.setTitle("@jedi_trials:padawan_trials_title")
		sui.setPrompt("@jedi_trials:padawan_trials_no_longer_eligible")
		sui.setOkButtonText("@jedi_trials:button_close")
		sui.sendTo(pPlayer)
	elseif (self:isOnKnightTrials(pPlayer) and not self:isEligibleForKnightTrials(pPlayer)) then
		local sui = SuiMessageBox.new("JediTrials", "emptyCallback")
		sui.setTitle("@jedi_trials:knight_trials_title")
		sui.setPrompt("@jedi_trials:knight_trials_no_longer_eligible")
		sui.setOkButtonText("@jedi_trials:button_close")
		sui.sendTo(pPlayer)
	end

	return 0
end

function JediTrials:unlockJediPadawan(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local sui = SuiMessageBox.new("JediTrials", "emptyCallback") -- No callback
	sui.setTitle("@jedi_trials:padawan_trials_title")
	sui.setPrompt("@jedi_trials:padawan_trials_completed")
	sui.sendTo(pPlayer)

	if (not CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_01")) then
		awardSkill(pPlayer, "force_title_jedi_rank_01")
	end

	awardSkill(pPlayer, "force_title_jedi_rank_02")
	writeScreenPlayData(pPlayer, "PadawanTrials", "completedTrials", 1)

	CreatureObject(pPlayer):playEffect("clienteffect/trap_electric_01.cef", "")
	CreatureObject(pPlayer):playMusicMessage("sound/music_become_jedi.snd")

	PlayerObject(pGhost):setJediState(2)

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
		CreatureObject(pPlayer):sendSystemMessage("@jedi_spam:inventory_full_jedi_robe")
	else
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		local pItem = giveItem(pInventory, "object/tangible/wearables/robe/robe_jedi_padawan.iff", -1)
	end

	sendMail("system", "@jedi_spam:welcome_subject", "@jedi_spam:welcome_body", CreatureObject(pPlayer):getFirstName())
end

function JediTrials:unlockJediKnight(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local knightRobe, unlockMusic, unlockString, enclaveLoc, enclaveName, jediState, setFactionVal, skillForceRank
	local councilType = self:getJediCouncil(pPlayer)

	if (councilType == self.COUNCIL_LIGHT) then
		knightRobe = "object/tangible/wearables/robe/robe_jedi_light_s01.iff"
		unlockMusic = "sound/music_become_light_jedi.snd"
		unlockString = "@jedi_trials:knight_trials_completed_light"
		enclaveLoc = { -5575, 4905, "yavin4" }
		enclaveName = "Light Jedi Enclave"
		jediState = 4
		setFactionVal = FACTIONREBEL
	elseif (councilType == self.COUNCIL_DARK) then
		knightRobe = 'object/tangible/wearables/robe/robe_jedi_dark_s01.iff'
		unlockMusic = "sound/music_become_dark_jedi.snd"
		unlockString = "@jedi_trials:knight_trials_completed_dark"
		enclaveLoc = { 5079, 305, "yavin4" }
		enclaveName = "Dark Jedi Enclave"
		jediState = 8
		setFactionVal = FACTIONIMPERIAL
	else
		printLuaError("Invalid council type in JediTrials:unlockJediKnight")
		return
	end

	awardSkill(pPlayer, "force_title_jedi_rank_03")
	writeScreenPlayData(pPlayer, "KnightTrials", "completedTrials", 1)
	CreatureObject(pPlayer):playMusicMessage(unlockMusic)
	playClientEffectLoc(CreatureObject(pPlayer):getObjectID(), "clienteffect/trap_electric_01.cef", CreatureObject(pPlayer):getZoneName(), CreatureObject(pPlayer):getPositionX(), CreatureObject(pPlayer):getPositionZ(), CreatureObject(pPlayer):getPositionY(), CreatureObject(pPlayer):getParentID())

	PlayerObject(pGhost):addWaypoint(enclaveLoc[3], enclaveName, "", enclaveLoc[1], enclaveLoc[2], WAYPOINTYELLOW, true, true, 0)
	PlayerObject(pGhost):setJediState(jediState)
	PlayerObject(pGhost):setFrsCouncil(councilType)
	PlayerObject(pGhost):setFrsRank(0)
	CreatureObject(pPlayer):setFactionStatus(2) -- Overt
	CreatureObject(pPlayer):setFaction(setFactionVal)

	local sui = SuiMessageBox.new("JediTrials", "emptyCallback") -- No callback
	sui.setTitle("@jedi_trials:knight_trials_title")
	sui.setPrompt(unlockString)
	sui.sendTo(pPlayer)

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
		CreatureObject(pPlayer):sendSystemMessage("@jedi_spam:inventory_full_jedi_robe")
	else
		giveItem(pInventory, knightRobe, -1)
	end

end

function JediTrials:emptyCallback(pPlayer)
-- Do nothing.
end

function JediTrials:createClosestShrineWaypoint(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local shrineID = readData(playerID .. ":jediShrineWaypointID")

	local pShrine = getSceneObject(shrineID)

	if (pShrine ~= nil) then
		SceneObject(pShrine):destroyObjectFromWorld()
	end

	deleteData(playerID .. ":jediShrineWaypointID")

	pShrine = self:getNearestForceShrine(pPlayer)

	if (pShrine == nil) then
		return
	end

	self:createShrineWaypoint(pPlayer, pShrine)
end

function JediTrials:createShrineWaypoint(pPlayer, pShrine)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		local zoneName = SceneObject(pShrine):getZoneName()
		local waypointID = PlayerObject(pGhost):addWaypoint(zoneName, zoneName:gsub("^%l", string.upper) .. " Force Shrine", "", SceneObject(pShrine):getWorldPositionX(), SceneObject(pShrine):getWorldPositionY(), WAYPOINTYELLOW, true, true, 0)
		writeData(SceneObject(pPlayer):getObjectID() .. ":jediShrineWaypointID", waypointID)
	end
end

function JediTrials:getRandomDifferentShrinePlanet(pPlayer)
	local shrinePlanet = self.shrinePlanets[getRandomNumber(1, #self.shrinePlanets)]
	local playerPlanet = SceneObject(pPlayer):getZoneName()
	local attempts = 0

	while (shrinePlanet == playerPlanet or not isZoneEnabled(shrinePlanet)) and attempts <= 50 do
		shrinePlanet = self.shrinePlanets[getRandomNumber(1, #self.shrinePlanets)]
		attempts = attempts + 1
	end

	if (attempts >= 50) then
		printLuaError("JediTrials:getRandomDifferentShrinePlanet failed to grab random shrine planet after 50 attempts.")
		return nil
	end

	return shrinePlanet
end

function JediTrials:getRandomShrineOnPlanet(planet)
	local shrineList = self.forceShrineIds[planet]
	local shrineID = shrineList[getRandomNumber(1, #shrineList)]
	local pShrine = getSceneObject(shrineID)
	local attempts = 0

	while pShrine == nil and attempts <= 50 do
		shrineID = shrineList[getRandomNumber(1, #shrineList)]
		pShrine = getSceneObject(shrineID)
		attempts = attempts + 1
	end

	if (attempts >= 50) then
		printLuaError("JediTrials:getRandomShrineOnPlanet failed to grab random shrine after 50 attempts.")
		return nil
	end

	return pShrine
end

function JediTrials:getNearestForceShrine(pPlayer)
	if (pPlayer == nil) then
		return nil
	end

	local planet = SceneObject(pPlayer):getZoneName()
	local pClosestShrine = nil
	local lastDist = 128000 -- Initialize as anything higher than a SWG zone.

	for i = 1, #self.forceShrineIds[planet], 1 do
		local shrineID = self.forceShrineIds[planet][i]
		local pShrine = getSceneObject(shrineID)

		if (pShrine ~= nil) then
			local curDist = SceneObject(pPlayer):getDistanceTo(pShrine)

			if (lastDist > curDist) then
				lastDist = curDist
				pClosestShrine = pShrine
			end
		end
	end

	return pClosestShrine
end

function JediTrials:setStartedTrials(pPlayer)
	if (self:isEligibleForPadawanTrials(pPlayer)) then
		writeScreenPlayData(pPlayer, "PadawanTrials", "startedTrials", 1)
	elseif (self:isEligibleForKnightTrials(pPlayer)) then
		writeScreenPlayData(pPlayer, "KnightTrials", "startedTrials", 1)
	end
end

function JediTrials:getTrialStateName(pPlayer, number)
	if (number == 0) then
		return nil
	elseif (self:isOnPadawanTrials(pPlayer)) then
		return "JediTrial:" .. padawanTrialQuests[number].trialName
	elseif (self:isOnKnightTrials(pPlayer)) then
		return "JediTrial:" .. knightTrialQuests[number].trialName
	else
		printLuaError("JediTrials:getTrialStateName, player " .. SceneObject(pPlayer):getCustomObjectName() .. " is not currently on padawan or knight trials (trial " .. number .. " sent)")
		return nil
	end
end

function JediTrials:setTrialPlanetAndCity(pPlayer, planet, city)
	writeScreenPlayData(pPlayer, "JediTrials", "trialLocPlanet", planet)
	writeScreenPlayData(pPlayer, "JediTrials", "trialLocCity", city)
end

function JediTrials:getTrialPlanetAndCity(pPlayer)
	local planet = readScreenPlayData(pPlayer, "JediTrials", "trialLocPlanet")
	local city = readScreenPlayData(pPlayer, "JediTrials", "trialLocCity")

	return { planet, city }
end

function JediTrials:setTrialLocation(pPlayer, x, z, y)
	writeScreenPlayData(pPlayer, "JediTrials", "trialLocX", x)
	writeScreenPlayData(pPlayer, "JediTrials", "trialLocZ", z)
	writeScreenPlayData(pPlayer, "JediTrials", "trialLocY", y)
end

function JediTrials:getTrialLocation(pPlayer)
	local locX = tonumber(readScreenPlayData(pPlayer, "JediTrials", "trialLocX"))
	local locZ = tonumber(readScreenPlayData(pPlayer, "JediTrials", "trialLocZ"))
	local locY = tonumber(readScreenPlayData(pPlayer, "JediTrials", "trialLocY"))

	if (locX == nil or locX == 0 or locY == nil or locY == 0) then
		return nil
	end

	return { locX, locZ, locY }
end

function JediTrials:hasTrialArea(pPlayer)
	local locData = self:getTrialLocation(pPlayer)

	if (locData == nil) then
		return false
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local areaID = readData(playerID .. ":mainLocSpawnAreaID")
	local pArea = getSceneObject(areaID)

	if (pArea == nil) then
		areaID = readData(playerID .. ":destroyAreaID")
		pArea = getSceneObject(areaID)
	end

	if (pArea == nil) then
		areaID = readData(playerID .. ":targetLocSpawnAreaID")
		pArea = getSceneObject(areaID)
	end

	return pArea ~= nil
end

function JediTrials:setCurrentTrial(pPlayer, num)
	writeScreenPlayData(pPlayer, "JediTrials", "currentTrial", num)
end

function JediTrials:getCurrentTrial(pPlayer)
	return tonumber(readScreenPlayData(pPlayer, "JediTrials", "currentTrial"))
end

function JediTrials:setJediCouncil(pPlayer, num)
	writeScreenPlayData(pPlayer, "JediTrials", "JediCouncil", num)
end

function JediTrials:getJediCouncil(pPlayer)
	return tonumber(readScreenPlayData(pPlayer, "JediTrials", "JediCouncil"))
end

function JediTrials:setTrialFailureCount(pPlayer, num)
	writeScreenPlayData(pPlayer, "JediTrials", "failureCount", num)
end

function JediTrials:getTrialsCompleted(pPlayer)
	if (self:isOnPadawanTrials(pPlayer)) then
		local completed = tonumber(readScreenPlayData(pPlayer, "PadawanTrials", "trialsCompleted"))

		if (completed == nil) then
			writeScreenPlayData(pPlayer, "PadawanTrials", "trialsCompleted", 0)
			return 0
		else
			return completed
		end
	elseif (self:isOnKnightTrials(pPlayer)) then
		local completed = tonumber(readScreenPlayData(pPlayer, "KnightTrials", "trialsCompleted"))

		if (completed == nil) then
			writeScreenPlayData(pPlayer, "KnightTrials", "trialsCompleted", 0)
			return 0
		else
			return completed
		end
	else
		return 0
	end
end

function JediTrials:setTrialsCompleted(pPlayer, num)
	if (self:isOnPadawanTrials(pPlayer)) then
		writeScreenPlayData(pPlayer, "PadawanTrials", "trialsCompleted", num)
	elseif (self:isOnKnightTrials(pPlayer)) then
		writeScreenPlayData(pPlayer, "KnightTrials", "trialsCompleted", num)
	end
end

function JediTrials:resetTrialData(pPlayer, trialType)
	if (trialType == "padawan") then
		deleteScreenPlayData(pPlayer, "PadawanTrials", "trialsCompleted")
		deleteScreenPlayData(pPlayer, "PadawanTrials", "startedTrials")
	elseif (trialType == "knight") then
		deleteScreenPlayData(pPlayer, "KnightTrials", "trialsCompleted")
		deleteScreenPlayData(pPlayer, "KnightTrials", "startedTrials")
	end

	deleteScreenPlayData(pPlayer, "JediTrials", "currentTrial")
	deleteScreenPlayData(pPlayer, "JediTrials", "failureCount")
end

function JediTrials:getTrialFailureCount(pPlayer)
	return tonumber(readScreenPlayData(pPlayer, "JediTrials", "failureCount"))
end

function JediTrials:getTrialNumByName(pPlayer, name)
	local trialTable

	if (self:isOnPadawanTrials(pPlayer)) then
		trialTable = padawanTrialQuests
	elseif (self:isOnKnightTrials(pPlayer)) then
		trialTable = knightTrialQuests
	else
		return -1
	end

	for i = 1, #trialTable, 1 do
		if trialTable[i].trialName == name then
			return i
		end
	end

	return -1
end
