JediTrials = ScreenPlay:new {
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
}

function JediTrials:isEligibleForPadawanTrials(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local learnedBranches = VillageJediManagerCommon.getLearnedForceSensitiveBranches(pPlayer)

	return CreatureObject(pPlayer):hasScreenPlayState(32, "VillageJediProgression") and not CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_02") and learnedBranches >= 6
end

function JediTrials:isOnPadawanTrials(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return tonumber(readScreenPlayData(pPlayer, "PadawanTrials", "startedTrials")) == 1
end

function JediTrials:isEligibleForKnightTrials(pPlayer)
	return false -- Temporary
end

function JediTrials:isOnKnightTrials(pPlayer)
	return false -- Temporary
end

function JediTrials:onPlayerLoggedIn(pPlayer)
	if (self:isOnPadawanTrials(pPlayer) or self:isOnKnightTrials(pPlayer)) then
		dropObserver(SKILLREMOVED, "JediTrials", "droppedSkillDuringTrials", pPlayer)
		createObserver(SKILLREMOVED, "JediTrials", "droppedSkillDuringTrials", pPlayer)
	end

	if (self:isOnPadawanTrials(pPlayer)) then
		PadawanTrials:onLoggedIn(pPlayer)
	elseif (self:isOnKnightTrials(pPlayer)) then
	end
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
	PlayerObject(pGhost):findJediTrainer()
end

function JediTrials:hasFullInventory(pPlayer)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return true
	end

	return SceneObject(pInventory):isContainerFullRecursive()
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

	if (pShrine ~= nil) then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			local zoneName = SceneObject(pPlayer):getZoneName()
			local waypointID = PlayerObject(pGhost):addWaypoint(zoneName, zoneName:gsub("^%l", string.upper) .. " Force Shrine", "", SceneObject(pShrine):getWorldPositionX(), SceneObject(pShrine):getWorldPositionY(), WAYPOINTYELLOW, true, true, 0)
			writeData(playerID .. ":jediShrineWaypointID", waypointID)
		end
	end
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
	local playerID = SceneObject(pPlayer):getObjectID()
	writeStringSharedMemory(playerID .. ":JediTrials:trialLocX", x)
	writeStringSharedMemory(playerID .. ":JediTrials:trialLocZ", z)
	writeStringSharedMemory(playerID .. ":JediTrials:trialLocY", y)
end

function JediTrials:getTrialLocation(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local locX = tonumber(readStringSharedMemory(playerID .. ":JediTrials:trialLocX"))
	local locZ = tonumber(readStringSharedMemory(playerID .. ":JediTrials:trialLocZ"))
	local locY = tonumber(readStringSharedMemory(playerID .. ":JediTrials:trialLocY"))

	if (locX == 0 or locY == 0) then
		return nil
	end

	return { locX, locZ, locY }
end

function JediTrials:hasTrialLocation(pPlayer)
	local locData = self:getTrialLocation(pPlayer)

	if (locData == nil) then
		return false
	end

	local areaID = readData(SceneObject(pPlayer) .. ":trialActiveArea")
	local pArea = getSceneObject(areaID)

	return pArea ~= nil
end

function JediTrials:setCurrentTrial(pPlayer, num)
	writeScreenPlayData(pPlayer, "JediTrials", "currentTrial", num)
end

function JediTrials:getCurrentTrial(pPlayer)
	return tonumber(readScreenPlayData(pPlayer, "JediTrials", "currentTrial"))
end

function JediTrials:setTrialFailureCount(pPlayer, num)
	writeScreenPlayData(pPlayer, "JediTrials", "failureCount", num)
end

function JediTrials:getTrialsCompleted(pPlayer)
	if (self:isOnPadawanTrials(pPlayer)) then
		return tonumber(readScreenPlayData(pPlayer, "PadawanTrials", "trialsCompleted"))
	elseif (self:isOnKnightTrials(pPlayer)) then
		return  tonumber(readScreenPlayData(pPlayer, "KnightTrials", "trialsCompleted"))
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
