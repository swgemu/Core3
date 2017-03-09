local ObjectManager = require("managers.object.object_manager")

PadawanTrials = ScreenPlay:new {}

function PadawanTrials:doPadawanTrialsSetup(pPlayer)
	local sui = SuiMessageBox.new("JediTrials", "emptyCallback")

	if (not JediTrials:isEligibleForPadawanTrials(pPlayer)) then
		sui.setTitle("@jedi_trials:padawan_trials_title")
		sui.setPrompt("@jedi_trials:padawan_trials_started_not_eligible")
	else
		JediTrials:createClosestShrineWaypoint(pPlayer)
		sui.setTitle("@jedi_trials:force_shrine_title")
		sui.setPrompt("@jedi_trials:padawan_trials_intro_msg")
	end

	sui.sendTo(pPlayer)
end

function PadawanTrials:startPadawanTrials(pObject, pPlayer)
	if (not JediTrials:isEligibleForPadawanTrials(pPlayer)) then
		local sui = SuiMessageBox.new("JediTrials", "emptyCallback")
		sui.setTitle("@jedi_trials:padawan_trials_title")
		sui.setPrompt("@jedi_trials:padawan_trials_started_not_eligible")
		sui.sendTo(pPlayer)
		return
	end

	local sui = SuiMessageBox.new("PadawanTrials", "jediPadawanTrialsStartCallback")
	sui.setTargetNetworkId(SceneObject(pObject):getObjectID())
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_start_query")
	sui.setOkButtonText("@jedi_trials:button_yes") -- Yes
	sui.setCancelButtonText("@jedi_trials:button_no") -- No
	sui.sendTo(pPlayer)
end

function PadawanTrials:jediPadawanTrialsStartCallback(pPlayer, pSui, eventIndex, args)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	if (not JediTrials:isEligibleForPadawanTrials(pPlayer)) then
		local sui = SuiMessageBox.new("JediTrials", "emptyCallback")
		sui.setTitle("@jedi_trials:padawan_trials_title")
		sui.setPrompt("@jedi_trials:padawan_trials_started_not_eligible")
		sui.sendTo(pPlayer)
		return
	end

	local rand = getRandomNumber(1, #padawanTrialQuests) -- 16 Jedi Padawan Trials

	while padawanTrialQuests[rand].trialType == TRIAL_LIGHTSABER do
		rand = getRandomNumber(1, #padawanTrialQuests)
	end

	JediTrials:setStartedTrials(pPlayer)
	JediTrials:setTrialsCompleted(pPlayer, 0)
	self:startTrial(pPlayer, rand)
end

function PadawanTrials:restartCurrentPadawanTrial(pPlayer)
	local sui = SuiMessageBox.new("PadawanTrials", "jediPadawanTrialsRestartCallback")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_restart_confirmation")
	sui.sendTo(pPlayer)
end

function PadawanTrials:jediPadawanTrialsRestartCallback(pPlayer, pSui, eventIndex, args)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_trial_restarted")
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialName = JediTrials:getTrialStateName(pPlayer, trialNumber)

	self:startTrial(pPlayer, trialNumber)
end

function PadawanTrials:quitPadawanTrials(pPlayer)
	local sui = SuiMessageBox.new("PadawanTrials", "jediPadawanTrialsAbortCallback")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_abort_confirmation")
	sui.sendTo(pPlayer)
end

function PadawanTrials:jediPadawanTrialsAbortCallback(pPlayer, pSui, eventIndex, args)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_aborted")
	self:resetAllPadawanTrials(pPlayer)
end

function PadawanTrials:startNextPadawanTrial(pObject, pPlayer)
	if (pPlayer == nil) then
		return
	end

	local trialsCompleted = JediTrials:getTrialsCompleted(pPlayer)

	if (trialsCompleted == 7) then
		local trialNum = self:getSaberCraftingTrialNumber()
		self:startTrial(pPlayer, trialNum)
	else
		local incompleteTrials = {}
		for i = 1, #padawanTrialQuests, 1 do
			local trialState = JediTrials:getTrialStateName(pPlayer, i)
			if not CreatureObject(pPlayer):hasScreenPlayState(1, trialState) then
				table.insert(incompleteTrials, i)
			end
		end

		local rand = getRandomNumber(1, #incompleteTrials)
		local randTrial = incompleteTrials[rand]
		self:startTrial(pPlayer, randTrial)
	end
end

function PadawanTrials:getSaberCraftingTrialNumber()
	for i = 1, #padawanTrialQuests, 1 do
		if padawanTrialQuests[i].trialType == TRIAL_LIGHTSABER then
			return i
		end
	end

	return -1
end

function PadawanTrials:resetAllPadawanTrials(pPlayer)
	--Remove All States.
	for i = 1, #padawanTrialQuests, 1 do
		local trialState = JediTrials:getTrialStateName(pPlayer, i)
		CreatureObject(pPlayer):removeScreenPlayState(1, trialState)

		if padawanTrialQuests[i].trialType == TRIAL_LIGHTSABER then
			CreatureObject(pPlayer):removeScreenPlayState(2, trialState)
			CreatureObject(pPlayer):removeScreenPlayState(4, trialState)
		end
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_01")) then
		CreatureObject(pPlayer):surrenderSkill("force_title_jedi_rank_01")
	end

	JediTrials:resetTrialData(pPlayer, "padawan")
	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
end

function PadawanTrials:startTrial(pPlayer, trialNum)
	JediTrials:setCurrentTrial(pPlayer, trialNum)
	local trialData = padawanTrialQuests[trialNum]

	if (trialData.trialType == TRIAL_LIGHTSABER) then
		if (not CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_01")) then
			awardSkill(pPlayer, "force_title_jedi_rank_01")
		end

		dropObserver(PROTOTYPECREATED, "PadawanTrials", "notifyCraftedTrainingSaber", pPlayer)
		createObserver(PROTOTYPECREATED, "PadawanTrials", "notifyCraftedTrainingSaber", pPlayer)
		self:sendSuiNotification(pPlayer)
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. ":JediTrials:acceptedTask")
	deleteData(playerID .. ":JediTrials:killedTarget")
	deleteData(playerID .. ":JediTrials:spokeToTarget")

	local planetName = trialsCivilizedPlanets[getRandomNumber(1, #trialsCivilizedPlanets)]

	while (not isZoneEnabled(planetName)) do
		planetName = trialsCivilizedPlanets[getRandomNumber(1, #trialsCivilizedPlanets)]
	end

	if (self.trialName == "artist") then
		planetName = "naboo"
	end

	local randomCityTable = trialsCivilizedPlanetCities[planetName]
	local randomCity = randomCityTable[getRandomNumber(1, #randomCityTable)]

	if (randomCity == nil) then
		printLuaError("PadawanTrials:startTrial, unable to get random city for planet " .. planetName .. ".")
		return
	end

	JediTrials:setTrialPlanetAndCity(pPlayer, planetName, randomCity)

	local randomLocTable = trialsCivilizedNpcSpawnPoints[planetName][randomCity]
	local randomLoc = randomLocTable[getRandomNumber(1, #randomLocTable)]

	if (randomLoc == nil) then
		printLuaError("PadawanTrials:startTrial, unable to get random location for " .. randomCity .. " on  " .. planetName .. ".")
		return
	end

	local spawnPoint = getSpawnPointInArea(planetName, randomLoc[1], randomLoc[2], randomLoc[3])

	-- Execute the function again to pick a new random location
	if (spawnPoint == nil) then
		local pointAttempts = readData(playerID .. ":JediTrials:spawnPointAttempts")

		if (pointAttempts <= 5) then
			self:startTrial(pPlayer, trialNum)
			writeData(playerID .. ":JediTrials:spawnPointAttempts", pointAttempts + 1)
		else
			printLuaError("PadawanTrials:startTrial, unable to find start point for player " .. CreatureObject(pPlayer):getCustomObjectName() .. " on trial number " .. trialNum .. " after 5 attempts.")
			deleteData(playerID .. ":JediTrials:spawnPointAttempts")
		end

		return
	end

	deleteData(playerID .. ":JediTrials:spawnPointAttempts")

	JediTrials:setTrialLocation(pPlayer, spawnPoint[1], spawnPoint[2], spawnPoint[3], planetName)

	self:sendSuiNotification(pPlayer)
	self:createFirstLocation(pPlayer)
end

function PadawanTrials:notifyCraftedTrainingSaber(pPlayer, pItem)
	if (pPlayer == nil or pItem == nil) then
		return 0
	end

	if (not JediTrials:isEligibleForPadawanTrials(pPlayer)) then
		return 1
	end

	local trialNum = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNum]

	if (trialData.trialType ~= TRIAL_LIGHTSABER) then
		return 1
	end

	local trialState = JediTrials:getTrialStateName(pPlayer, trialNum)

	if (CreatureObject(pPlayer):hasScreenPlayState(2, trialState)) then -- Already crafted a saber
		return 1
	end

	if (not string.find(SceneObject(pItem):getTemplateObjectPath(), "object/weapon/melee/sword/crafted_saber")) then
		return 0
	end

	CreatureObject(pPlayer):setScreenPlayState(2, trialState)
	dropObserver(TUNEDCRYSTAL, "PadawanTrials", "notifyTunedLightsaberCrystal", pPlayer)
	createObserver(TUNEDCRYSTAL, "PadawanTrials", "notifyTunedLightsaberCrystal", pPlayer)
	self:sendSuiNotification(pPlayer)

	return 1
end

function PadawanTrials:notifyTunedLightsaberCrystal(pPlayer, pItem)
	if (pPlayer == nil or pItem == nil) then
		return 0
	end

	if (not JediTrials:isEligibleForPadawanTrials(pPlayer)) then
		return 1
	end

	local trialNum = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNum]

	if (trialData.trialType ~= TRIAL_LIGHTSABER) then
		return 1
	end

	local trialState = JediTrials:getTrialStateName(pPlayer, trialNum)

	if (CreatureObject(pPlayer):hasScreenPlayState(4, trialState)) then -- Already crafted a saber
		return 1
	end

	CreatureObject(pPlayer):setScreenPlayState(4, trialState)
	self:passTrial(pPlayer)
	return 1
end

function PadawanTrials:setupHuntTrial(pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)

	if (trialNumber <= 1) then
		return
	end

	local trialData = padawanTrialQuests[trialNumber]

	if (trialData.trialType ~= TRIAL_HUNT) then
		return
	end

	writeScreenPlayData(pPlayer, "JediTrials", "huntTarget", trialData.huntTarget)
	writeScreenPlayData(pPlayer, "JediTrials", "huntTargetCount", 0)
	writeScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal", trialData.huntGoal)
	dropObserver(KILLEDCREATURE, "PadawanTrials", "notifyKilledHuntTarget", pPlayer)
	createObserver(KILLEDCREATURE, "PadawanTrials", "notifyKilledHuntTarget", pPlayer)
end

function PadawanTrials:hasCompletedHunt(pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)

	if (trialNumber <= 1) then
		return false
	end

	local trialData = padawanTrialQuests[trialNumber]

	if (trialData.trialType ~= TRIAL_HUNT) then
		return false
	end

	local targetCount = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetCount"))
	local targetGoal = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal"))

	return targetCount >= targetGoal
end


function PadawanTrials:notifyKilledHuntTarget(pPlayer, pVictim)
	if (pVictim == nil or pPlayer == nil) then
		return 0
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)

	if (trialNumber <= 1) then
		return 1
	end

	local trialData = padawanTrialQuests[trialNumber]

	if (trialData.trialType ~= TRIAL_HUNT) then
		return 1
	end

	local huntTarget = readScreenPlayData(pPlayer, "JediTrials", "huntTarget")
	local targetCount = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetCount"))
	local targetGoal = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal"))

	if (SceneObject(pVictim):getObjectName() == huntTarget) then
		CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_progress")
		targetCount = targetCount + 1
		writeScreenPlayData(pPlayer, "JediTrials", "huntTargetCount", targetCount)

		if (targetCount >= targetGoal) then
			CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_return_to_npc")
			self:createFirstLocation(pPlayer)
			return 1
		end
	end

	return 0
end

function PadawanTrials:createFirstLocation(pPlayer)
	local firstLocData = JediTrials:getTrialPlanetAndCity(pPlayer)
	local planetName = firstLocData[1]
	local spawnLoc = JediTrials:getTrialLocation(pPlayer)

	local pActiveArea = spawnActiveArea(planetName, "object/active_area.iff", spawnLoc[1], spawnLoc[2], spawnLoc[3], 64, 0)
	local playerID = SceneObject(pPlayer):getObjectID()

	if pActiveArea == nil then
		printLuaError("PadawanTrials:createFirstLocation, failed to create active area.")
		return
	end

	local areaID = SceneObject(pActiveArea):getObjectID()
	writeData(playerID .. ":firstLocSpawnAreaID", areaID)
	writeData(areaID .. ":ownerID", playerID)
	createObserver(ENTEREDAREA, "PadawanTrials", "notifyEnteredFirstLocSpawnArea", pActiveArea)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):addWaypoint(planetName, "Speak to this person", "", spawnLoc[1], spawnLoc[3], WAYPOINTBLUE, true, true, WAYPOINTQUESTTASK)
	end
end

function PadawanTrials:sendSuiNotification(pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNumber]
	local msgFinal

	if (trialData.trialType == TRIAL_LIGHTSABER) then
		local trialState = JediTrials:getTrialStateName(pPlayer, trialNumber)
		if (CreatureObject(pPlayer):hasScreenPlayState(2, trialState)) then
			msgFinal = "@jedi_trials:craft_lightsaber_02"
		else
			msgFinal = "@jedi_trials:craft_lightsaber_01"
		end
	else
		local planetData = JediTrials:getTrialPlanetAndCity(pPlayer)
		local cityName = planetData[2]
		cityName = string.gsub(cityName, "_", " ")
		cityName = string.gsub(" "..cityName, "%W%l", string.upper):sub(2)

		local msgPrefix =  "@jedi_trials:" .. trialData.trialName .. "_01 " .. "@jedi_trials:" .. planetData[1]
		local msgPostfix =  "@jedi_trials:" .. trialData.trialName .. "_02 " .. cityName .. "."
		msgFinal = msgPrefix .. " " .. msgPostfix
	end

	local sui = SuiMessageBox.new("JediTrials", "emptyCallback")
	sui.hideCancelButton()
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(msgFinal)
	sui.sendTo(pPlayer)

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_tell_about_restart")
end

function PadawanTrials:notifyEnteredFirstLocSpawnArea(pArea, pPlayer)
	if (pArea == nil or pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local ownerID = readData(SceneObject(pArea):getObjectID() .. ":ownerID")

	if (playerID ~= ownerID) then
		return 0
	end

	local pActiveArea = spawnActiveArea(SceneObject(pPlayer):getZoneName(), "object/active_area.iff", SceneObject(pArea):getWorldPositionX(), SceneObject(pArea):getWorldPositionZ(), SceneObject(pArea):getWorldPositionY(), 32, 0)

	if pActiveArea == nil then
		printLuaError("PadawanTrials:notifyEnteredFirstLocSpawnArea, failed to create npc destroy active area.")
		CreatureObject(pPlayer):sendSystemMessage("Failed to spawn quest area, please submit a bug report.")
		self:failTrial(pPlayer)
		return 1
	end

	createObserver(EXITEDAREA, "PadawanTrials", "notifyExitedLocDestroyArea", pActiveArea)
	local areaID = SceneObject(pActiveArea):getObjectID()
	writeData(areaID .. ":ownerID", playerID)
	writeData(playerID .. ":destroyAreaID", areaID)

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNumber]
	local spawnLoc = JediTrials:getTrialLocation(pPlayer)
	local planetData = JediTrials:getTrialPlanetAndCity(pPlayer)

	local pNpc = spawnMobile(planetData[1], trialData.trialNpc, 0, spawnLoc[1], spawnLoc[2], spawnLoc[3], getRandomNumber(180) - 180, 0)

	if (pNpc == nil) then
		printLuaError("PadawanTrials:notifyEnteredTrialTargetArea, failed to spawn quest mobile.")
		CreatureObject(pPlayer):sendSystemMessage("Failed to spawn quest mobile, please submit a bug report.")
		self:failTrial(pPlayer)
		return 1
	end

	local npcID = SceneObject(pNpc):getObjectID()
	CreatureObject(pNpc):setPvpStatusBitmask(0) -- Prevent attacking.
	CreatureObject(pNpc):setOptionsBitmask(136)
	CreatureObject(pNpc):setCustomObjectName(trialData.trialNpcName)
	writeData(areaID .. ":npcID", npcID)
	writeData(npcID .. ":ownerID", playerID)
	AiAgent(pNpc):setConvoTemplate("padawan_" .. trialData.trialName .. "_01_convo_template")

	deleteData(playerID .. ":firstLocSpawnAreaID")
	deleteData(SceneObject(pArea):getObjectID() .. ":ownerID")
	SceneObject(pArea):destroyObjectFromWorld()

	return 1
end

function PadawanTrials:notifyExitedLocDestroyArea(pArea, pPlayer)
	if (pArea == nil or pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local ownerID = readData(SceneObject(pArea):getObjectID() .. ":ownerID")

	if (playerID ~= ownerID) then
		return 0
	end

	local areaID = SceneObject(pArea):getObjectID()
	local npcID = readData(areaID .. ":npcID")
	local pNpc = getSceneObject(npcID)

	if (pNpc == nil) then
		deleteData(npcID .. ":ownerID")
		deleteData(npcID .. ":JediTrials:objectSearched")
		deleteData(areaID .. ":ownerID")
		deleteData(areaID .. ":npcID")
		return 1
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)

	if (trialNumber == nil or not JediTrials:isOnPadawanTrials(pPlayer)) then
		self:removeNpcDestroyActiveArea(pPlayer)
		deleteData(npcID .. ":ownerID")
		deleteData(npcID .. ":JediTrials:objectSearched")
		deleteData(npcID .. ":destroyNpcOnExit")
		SceneObject(pNpc):destroyObjectFromWorld()
		return 1
	end

	local trialState = JediTrials:getTrialStateName(pPlayer, trialNumber)

	if (trialState == nil or CreatureObject(pPlayer):hasScreenPlayState(1, trialState) or readData(npcID .. ":destroyNpcOnExit") == 1) then
		self:removeNpcDestroyActiveArea(pPlayer)
		deleteData(npcID .. ":ownerID")
		deleteData(npcID .. ":JediTrials:objectSearched")
		deleteData(npcID .. ":destroyNpcOnExit")
		SceneObject(pNpc):destroyObjectFromWorld()
		return 1
	end

	return 0
end

function PadawanTrials:removeNpcDestroyActiveArea(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local areaID = readData(playerID .. ":destroyAreaID")

	local pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	deleteData(areaID .. ":npcID")
	deleteData(areaID .. ":ownerID")
	deleteData(playerID .. ":destroyAreaID")
end

function PadawanTrials:createSecondLocation(pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialName = padawanTrialQuests[trialNumber].trialName
	local zoneName = SceneObject(pPlayer):getZoneName()

	local secondaryLoc = getSpawnPoint(zoneName, SceneObject(pPlayer):getWorldPositionX(), SceneObject(pPlayer):getWorldPositionY(), 900, 1800, true)

	if (secondaryLoc == nil) then
		printLuaError("Unable to find spawn point in PadawanTrials:createSecondLocation.")
		CreatureObject(pPlayer):sendSystemMessage("Failed to get a good spawn location, please submit a bug report.")
		self:failTrial(pPlayer)
		return
	end

	local pActiveArea = spawnActiveArea(zoneName, "object/active_area.iff", secondaryLoc[1], secondaryLoc[2], secondaryLoc[3], 100, 0)
	local playerID = SceneObject(pPlayer):getObjectID()

	if pActiveArea == nil then
		printLuaError("PadawanTrials:createSecondLocation, failed to create active area.")
		CreatureObject(pPlayer):sendSystemMessage("Failed to spawn quest area, please submit a bug report.")
		self:failTrial(pPlayer)
		return
	end

	local areaID = SceneObject(pActiveArea):getObjectID()
	writeData(areaID .. ":ownerID", playerID)
	writeData(playerID .. ":secondLocSpawnAreaID", areaID)
	createObserver(ENTEREDAREA, "PadawanTrials", "notifyEnteredSecondLocSpawnArea", pActiveArea)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):addWaypoint(zoneName, "Padawan Trial waypoint", "", secondaryLoc[1], secondaryLoc[3], WAYPOINTBLUE, true, true, WAYPOINTQUESTTASK)
	end
end

function PadawanTrials:notifyEnteredSecondLocSpawnArea(pArea, pPlayer)
	if (pArea == nil or pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local ownerID = readData(SceneObject(pArea):getObjectID() .. ":ownerID")

	if (playerID ~= ownerID) then
		return 0
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNumber]

	local planetName = SceneObject(pPlayer):getZoneName()
	local locX = SceneObject(pArea):getWorldPositionX()
	local locZ = SceneObject(pArea):getWorldPositionZ()
	local locY = SceneObject(pArea):getWorldPositionY()

	local pNpc

	if (string.find(trialData.targetNpc, ".iff")) then
		pNpc = spawnSceneObject(planetName, trialData.targetNpc, locX, locZ, locY, 0, getRandomNumber(180) - 180)
	else
		pNpc = spawnMobile(planetName, trialData.targetNpc, 0, locX, locZ, locY, getRandomNumber(180) - 180, 0)
	end

	if (pNpc == nil) then
		printLuaError("PadawanTrials:notifyEnteredSecondLocSpawnArea, failed to spawn quest mobile.")
		CreatureObject(pPlayer):sendSystemMessage("Failed to spawn quest mobile, please submit a bug report.")
		self:failTrial(pPlayer)
		return 1
	end

	local npcID = SceneObject(pNpc):getObjectID()
	writeData(npcID .. ":ownerID", playerID)

	if (trialData.targetNpcName ~= nil) then
		SceneObject(pNpc):setCustomObjectName(trialData.targetNpcName)
	end

	if (not string.find(trialData.targetNpc, ".iff")) then
		if (not trialData.targetKillable) then
			CreatureObject(pNpc):setPvpStatusBitmask(0)
		else
			createObserver(OBJECTDESTRUCTION, "PadawanTrials", "notifyQuestTargetDead", pNpc)
		end
	end

	if (trialData.trialType == TRIAL_TALK and not string.find(trialData.targetNpc, ".iff")) then
		CreatureObject(pNpc):setOptionsBitmask(136)
		AiAgent(pNpc):setConvoTemplate("padawan_" .. trialData.trialName .. "_02_convo_template")
	end

	deleteData(playerID .. ":secondLocSpawnAreaID")
	deleteData(SceneObject(pArea):getObjectID() .. ":ownerID")
	SceneObject(pArea):destroyObjectFromWorld()

	local pActiveArea = spawnActiveArea(planetName, "object/active_area.iff", locX, locZ, locY, 32, 0)

	if pActiveArea == nil then
		printLuaError("PadawanTrials:notifyEnteredSecondLocSpawnArea, failed to create npc destroy active area.")
		CreatureObject(pPlayer):sendSystemMessage("Failed to spawn quest area, please submit a bug report.")
		self:failTrial(pPlayer)
		return 1
	end

	local areaID = SceneObject(pActiveArea):getObjectID()
	writeData(areaID .. ":ownerID", playerID)
	writeData(areaID .. ":npcID", npcID)
	createObserver(EXITEDAREA, "PadawanTrials", "notifyExitedLocDestroyArea", pActiveArea)

	return 1
end

function PadawanTrials:notifyQuestTargetDead(pVictim, pAttacker)
	if (pVictim == nil or pAttacker == nil) then
		return 1
	end

	local ownerID = readData(SceneObject(pVictim):getObjectID() .. ":ownerID")
	local pOwner = getSceneObject(ownerID)

	if (pOwner == nil) then
		return 1
	end

	local npcID = SceneObject(pVictim):getObjectID()

	if (readData(npcID .. ":destroyNpcOnExit") ~= 1) then
		CreatureObject(pOwner):sendSystemMessage("@jedi_trials:padawan_trials_return_to_npc")
		writeData(ownerID .. ":JediTrials:killedTarget", 1)
		self:createFirstLocation(pOwner)
	end

	deleteData(npcID .. ":destroyNpcOnExit")
	deleteData(npcID .. ":ownerID")

	return 1
end

function PadawanTrials:removeAllAreas(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local areaID = readData(playerID .. ":firstLocSpawnAreaID")
	local pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	deleteData(areaID .. ":ownerID")
	deleteData(playerID .. ":firstLocSpawnAreaID")

	areaID = readData(playerID .. ":destroyAreaID")
	pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	local npcID = readData(areaID .. ":npcID")

	deleteData(npcID .. ":JediTrials:objectSearched")

	local pMobile = getSceneObject(npcID)

	if (pMobile ~= nil) then
		createEvent(5000, "HelperFuncs", "despawnMobileTask", pMobile, "")
	end

	deleteData(areaID .. ":npcID")
	deleteData(areaID .. ":ownerID")
	deleteData(playerID .. ":destroyAreaID")

	areaID = readData(playerID .. ":secondLocSpawnAreaID")
	pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	deleteData(areaID .. ":ownerID")
	deleteData(playerID .. ":secondLocSpawnAreaID")
end

function PadawanTrials:failTrial(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	self:removeAllAreas(pPlayer)
	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
	JediTrials:setCurrentTrial(pPlayer, 0)
	deleteData(playerID .. ":JediTrials:acceptedTask")
	deleteData(playerID .. ":JediTrials:killedTarget")
	deleteData(playerID .. ":JediTrials:spokeToTarget")

	deleteScreenPlayData(pPlayer, "JediTrials", "huntTarget")
	deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetCount")
	deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal")

	local failAmount = JediTrials:getTrialFailureCount(pPlayer)
	local failAmountMsg = nil

	if (failAmount == nil or failAmount == 0) then
		JediTrials:setTrialFailureCount(pPlayer, 1)
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_first"
	elseif (failAmount == 1) then
		JediTrials:setTrialFailureCount(pPlayer, 2)
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_second"
	elseif (failAmount == 2) then
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_final"
		self:resetAllPadawanTrials(pPlayer)
	end

	local sui = SuiMessageBox.new("JediTrials", "emptyCallback")
	sui.hideCancelButton()
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(failAmountMsg)
	sui.sendTo(pPlayer)
end

function PadawanTrials:passTrial(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (not JediTrials:isEligibleForPadawanTrials(pPlayer)) then
		local sui = SuiMessageBox.new("JediTrials", "emptyCallback")
		sui.setTitle("@jedi_trials:padawan_trials_title")

		if (CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_01")) then
			sui.setPrompt("@jedi_trials:padawan_trials_being_removed_revoked")
		else
			sui.setPrompt("@jedi_trials:padawan_trials_being_removed")
		end

		sui.setOkButtonText("@jedi_trials:button_close")
		sui.sendTo(pPlayer)

		self:resetAllPadawanTrials(pPlayer)
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialState = JediTrials:getTrialStateName(pPlayer, trialNumber)

	local trialsCompleted = JediTrials:getTrialsCompleted(pPlayer) + 1

	deleteScreenPlayData(pPlayer, "JediTrials", "huntTarget")
	deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetCount")
	deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal")

	deleteData(playerID .. ":JediTrials:acceptedTask")
	deleteData(playerID .. ":JediTrials:killedTarget")
	deleteData(playerID .. ":JediTrials:spokeToTarget")

	CreatureObject(pPlayer):setScreenPlayState(1, trialState) -- Complete Trial.
	JediTrials:setCurrentTrial(pPlayer, 0)
	JediTrials:setTrialsCompleted(pPlayer, trialsCompleted)
	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
	
	if (trialsCompleted < #padawanTrialQuests) then
		CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_next_trial") -- You have done well and successfully completed the trial you faced. To undertake your next trial, simply meditate at any Force shrine.
	else
		--TODO: Uncomment when all trials are implemented
		--JediTrials:unlockJediPadawan(pPlayer)
	end
end


function PadawanTrials:showCurrentTrial(pShrine, pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNumber]

	local sui = SuiMessageBox.new("PadawanTrials", "handleShowInfoChoice")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setTargetNetworkId(SceneObject(pShrine):getObjectID())
	sui.setCancelButtonText("@jedi_trials:button_abort_padawan") -- Quit Padawan Trials
	sui.setOtherButtonText("@jedi_trials:button_restart") -- Restart Current Trial
	sui.setOkButtonText("@jedi_trials:button_close") -- Close
	-- Other Button setup subscribe
	sui.setProperty("btnRevert", "OnPress", "RevertWasPressed=1\r\nparent.btnOk.press=t")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "btnRevert", "RevertWasPressed")

	if (trialData.trialType == TRIAL_LIGHTSABER) then
		local trialState = JediTrials:getTrialStateName(pPlayer, trialNumber)
		if (CreatureObject(pPlayer):hasScreenPlayState(2, trialState)) then
			sui.setPrompt("@jedi_trials:" .. trialData.trialName .. "_02")
		else
			sui.setPrompt("@jedi_trials:" .. trialData.trialName .. "_01")
		end
	else
		sui.setPrompt("@jedi_trials:" .. trialData.trialName .. "_03")
	end

	sui.sendTo(pPlayer)
end

function PadawanTrials:handleShowInfoChoice(pPlayer, pSui, eventIndex, ...)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local args = {...}
	local restart = args[1]

	if (cancelPressed) then
		self:quitPadawanTrials(pPlayer)
	elseif (restart ~= nil) then
		self:restartCurrentPadawanTrial(pPlayer)
	else
		return
	end
end

function PadawanTrials:onPlayerLoggedIn(pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)

	if (trialNumber >= 1) then
		local trialData = padawanTrialQuests[trialNumber]
		local trialState = JediTrials:getTrialStateName(pPlayer, trialNumber)

		if (trialData.trialType == TRIAL_HUNT) then
			dropObserver(KILLEDCREATURE, "PadawanTrials", "notifyKilledHuntTarget", pPlayer)
			createObserver(KILLEDCREATURE, "PadawanTrials", "notifyKilledHuntTarget", pPlayer)
		elseif (trialData.trialType == TRIAL_LIGHTSABER and not CreatureObject(pPlayer):hasScreenPlayState(4, trialState)) then
			if (CreatureObject(pPlayer):hasScreenPlayState(2, trialState)) then
				dropObserver(TUNEDCRYSTAL, "PadawanTrials", "notifyTunedLightsaberCrystal", pPlayer)
				createObserver(TUNEDCRYSTAL, "PadawanTrials", "notifyTunedLightsaberCrystal", pPlayer)
			else
				dropObserver(PROTOTYPECREATED, "PadawanTrials", "notifyCraftedTrainingSaber", pPlayer)
				createObserver(PROTOTYPECREATED, "PadawanTrials", "notifyCraftedTrainingSaber", pPlayer)
			end
		end
	end
end
