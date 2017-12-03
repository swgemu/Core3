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

	if (trialsCompleted == #padawanTrialQuests) then
		JediTrials:unlockJediPadawan(pPlayer)
		return
	elseif (trialsCompleted == 7) then
		local trialNum = self:getSaberCraftingTrialNumber()
		self:startTrial(pPlayer, trialNum)
	else
		local incompleteTrials = {}
		for i = 1, #padawanTrialQuests, 1 do
			local trialState = JediTrials:getTrialStateName(pPlayer, i)
			if not CreatureObject(pPlayer):hasScreenPlayState(1, trialState) and padawanTrialQuests[i].trialType ~= TRIAL_LIGHTSABER then
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
			CreatureObject(pPlayer):removeScreenPlayState(1, trialState .. "_saber")
			CreatureObject(pPlayer):removeScreenPlayState(1, trialState .. "_crystal")
		end
	end

	self:removeAllAreas(pPlayer)

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

function PadawanTrials:startTrial(pPlayer, trialNum, skipNotification)
	if (skipNotification == nil) then
		skipNotification = false
	end

	dropObserver(KILLEDCREATURE, "PadawanTrials", "notifyKilledHuntTarget", pPlayer)
	dropObserver(PROTOTYPECREATED, "PadawanTrials", "notifyCraftedTrainingSaber", pPlayer)
	dropObserver(TUNEDCRYSTAL, "PadawanTrials", "notifyTunedLightsaberCrystal", pPlayer)

	self:removeAllAreas(pPlayer)

	JediTrials:setCurrentTrial(pPlayer, trialNum)
	local trialData = padawanTrialQuests[trialNum]

	if (trialData == nil) then
		printLuaError("PadawanTrials:startTrial, unable to get trial data for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNum)
		return
	end

	if (trialData.trialType == TRIAL_LIGHTSABER) then
		if (not CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_01")) then
			awardSkill(pPlayer, "force_title_jedi_rank_01")
		end

		local trialState = JediTrials:getTrialStateName(pPlayer, trialNum)

		CreatureObject(pPlayer):removeScreenPlayState(1, trialState .. "_saber")
		CreatureObject(pPlayer):removeScreenPlayState(1, trialState .. "_crystal")

		createObserver(PROTOTYPECREATED, "PadawanTrials", "notifyCraftedTrainingSaber", pPlayer)
		self:sendSuiNotification(pPlayer)
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. ":JediTrials:acceptedTask")
	deleteData(playerID .. ":JediTrials:killedTarget")
	deleteData(playerID .. ":JediTrials:spokeToTarget01")
	deleteData(playerID .. ":JediTrials:spokeToTarget02")

	deleteScreenPlayData(pPlayer, "JediTrials", "huntTarget")
	deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetCount")
	deleteScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal")

	local planetName = trialsCivilizedPlanets[getRandomNumber(1, #trialsCivilizedPlanets)]
	local playerPlanet = SceneObject(pPlayer):getZoneName()

	local retries = 0
	while ((not isZoneEnabled(planetName) or playerPlanet == planetName) and retries < 20) do
		planetName = trialsCivilizedPlanets[getRandomNumber(1, #trialsCivilizedPlanets)]
		retries = retries + 1
	end

	if (trialData.trialName == "artist") then
		planetName = "naboo"
	end

	local randomCityTable = trialsCivilizedPlanetCities[planetName]
	local randomCity = randomCityTable[getRandomNumber(1, #randomCityTable)]

	if (trialData.trialLoc ~= nil) then
		local locData = trialData.trialLoc

		if locData[4] ~= nil then
			planetName = locData[4]
		end

		if locData[5] ~= nil then
			randomCity = locData[5]
		else
			randomCityTable = trialsCivilizedPlanetCities[planetName]
			randomCity = randomCityTable[getRandomNumber(1, #randomCityTable)]
		end
	end

	if (randomCity == nil) then
		printLuaError("PadawanTrials:startTrial, unable to get random city for planet " .. planetName .. ".")
		return
	end

	JediTrials:setTrialPlanetAndCity(pPlayer, planetName, randomCity)

	local spawnPoint

	if (trialData.trialLoc == nil) then
		local randomLocTable = trialsCivilizedNpcSpawnPoints[planetName][randomCity]
		local randomLoc = randomLocTable[getRandomNumber(1, #randomLocTable)]

		if (randomLoc == nil) then
			printLuaError("PadawanTrials:startTrial, unable to get random location for " .. randomCity .. " on  " .. planetName .. ".")
			return
		end

		spawnPoint = getSpawnPointInArea(planetName, randomLoc[1], randomLoc[2], randomLoc[3])

		-- Execute the function again to pick a new random location
		if (spawnPoint == nil) then
			local pointAttempts = readData(playerID .. ":JediTrials:spawnPointAttempts")

			if (pointAttempts <= 5) then
				self:startTrial(pPlayer, trialNum, skipNotification)
				writeData(playerID .. ":JediTrials:spawnPointAttempts", pointAttempts + 1)
			else
				printLuaError("PadawanTrials:startTrial, unable to find start point for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial number " .. trialNum .. " after 5 attempts.")
				deleteData(playerID .. ":JediTrials:spawnPointAttempts")
			end

			return
		end

		deleteData(playerID .. ":JediTrials:spawnPointAttempts")
	else
		spawnPoint = trialData.trialLoc
	end

	JediTrials:setTrialLocation(pPlayer, spawnPoint[1], spawnPoint[2], spawnPoint[3], planetName)

	if (not skipNotification) then
		self:sendSuiNotification(pPlayer)
	end

	self:createMainLocation(pPlayer)
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

	if (trialData == nil) then
		printLuaError("PadawanTrials:notifyCraftedTrainingSaber, unable to get trial data for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNum)
		return 1
	end

	if (trialData.trialType ~= TRIAL_LIGHTSABER) then
		return 1
	end

	local trialState = JediTrials:getTrialStateName(pPlayer, trialNum)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, trialState .. "_saber")) then -- Already crafted a saber
		return 1
	end

	if (not string.find(SceneObject(pItem):getTemplateObjectPath(), "object/weapon/melee/sword/crafted_saber")) then
		return 0
	end

	CreatureObject(pPlayer):setScreenPlayState(1, trialState .. "_saber")
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

	if (trialData == nil) then
		printLuaError("PadawanTrials:notifyTunedLightsaberCrystal, unable to get trial data for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNum)
		return 1
	end

	if (trialData.trialType ~= TRIAL_LIGHTSABER) then
		return 1
	end

	local trialState = JediTrials:getTrialStateName(pPlayer, trialNum)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, trialState .. "_crystal")) then -- Already tuned a crystal
		return 1
	end

	CreatureObject(pPlayer):setScreenPlayState(1, trialState .. "_crystal")
	self:passTrial(pPlayer)
	return 1
end

function PadawanTrials:setupHuntTrial(pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)

	if (trialNumber <= 1) then
		return
	end

	local trialData = padawanTrialQuests[trialNumber]

	if (trialData == nil) then
		printLuaError("PadawanTrials:setupHuntTrial, unable to get trial data for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber)
		return
	end

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

	if (trialData == nil) then
		printLuaError("PadawanTrials:hasCompletedHunt, unable to get trial data for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber)
		return false
	end

	if (trialData.trialType ~= TRIAL_HUNT) then
		return false
	end

	local targetCount = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetCount"))
	local targetGoal = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal"))

	if (targetCount == nil or targetGoal == nil) then
		return false
	end

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

	if (trialData == nil) then
		printLuaError("PadawanTrials:notifyKilledHuntTarget, unable to get trial data for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber)
		return 1
	end

	if (trialData.trialType ~= TRIAL_HUNT) then
		return 1
	end

	local huntTarget = readScreenPlayData(pPlayer, "JediTrials", "huntTarget")
	local targetCount = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetCount"))
	local targetGoal = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal"))

	if (targetCount == nil) then
		printLuaError("PadawanTrials:notifyKilledHuntTarget, nil targetCount for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber .. " (player killed target: " .. SceneObject(pVictim):getObjectName() .. ").")
		return 1
	end

	if (targetGoal == nil) then
		printLuaError("PadawanTrials:notifyKilledHuntTarget, nil targetGoal for player: " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber .. " (player killed target: " .. SceneObject(pVictim):getObjectName() .. ").")
		return 1
	end

	if (SceneObject(pVictim):getZoneName() ~= SceneObject(pPlayer):getZoneName() or not CreatureObject(pPlayer):isInRangeWithObject(pVictim, 80)) then
		return 0
	end

	if (string.find(SceneObject(pVictim):getObjectName(), huntTarget)) then
		CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_progress")
		targetCount = targetCount + 1
		writeScreenPlayData(pPlayer, "JediTrials", "huntTargetCount", targetCount)

		if (targetCount >= targetGoal) then
			CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_return_to_npc")
			self:createMainLocation(pPlayer)
			return 1
		end
	end

	return 0
end

function PadawanTrials:createMainLocation(pPlayer)
	local trialNum = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNum]

	if (trialData == nil) then
		printLuaError("PadawanTrials:createMainLocation, unable to get trial data for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNum)
		return
	end

	local mainLocData = JediTrials:getTrialPlanetAndCity(pPlayer)
	local planetName = mainLocData[1]
	local spawnLoc = JediTrials:getTrialLocation(pPlayer)

	if (trialData.trialLoc == nil) then
		local pActiveArea = spawnActiveArea(planetName, "object/active_area.iff", spawnLoc[1], spawnLoc[2], spawnLoc[3], 64, 0)
		local playerID = SceneObject(pPlayer):getObjectID()

		if pActiveArea == nil then
			printLuaError("PadawanTrials:createMainLocation, failed to create active area.")
			return
		end

		local areaID = SceneObject(pActiveArea):getObjectID()
		writeData(playerID .. ":mainLocSpawnAreaID", areaID)
		writeData(areaID .. ":ownerID", playerID)
		createObserver(ENTEREDAREA, "PadawanTrials", "notifyEnteredMainLocSpawnArea", pActiveArea)
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):addWaypoint(planetName, "Speak to this person", "", spawnLoc[1], spawnLoc[3], WAYPOINTBLUE, true, true, WAYPOINTQUESTTASK)
	end
end

function PadawanTrials:sendSuiNotification(pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNumber]

	if (trialData == nil) then
		printLuaError("PadawanTrials:sendSuiNotification, unable to get trial data for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber)
		return
	end

	local msgFinal

	if (trialData.trialType == TRIAL_LIGHTSABER) then
		local trialState = JediTrials:getTrialStateName(pPlayer, trialNumber)
		if (CreatureObject(pPlayer):hasScreenPlayState(1, trialState .. "_saber")) then
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

function PadawanTrials:notifyEnteredMainLocSpawnArea(pArea, pPlayer)
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
		printLuaError("PadawanTrials:notifyEnteredMainLocSpawnArea, failed to create npc destroy active area.")
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

	if (trialData == nil) then
		printLuaError("PadawanTrials:notifyEnteredMainLocSpawnArea, nil trialData for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial number " .. trialNumber .. "\n.")
		self:failTrial(pPlayer)
		return 1
	end

	local spawnLoc = JediTrials:getTrialLocation(pPlayer)
	local planetData = JediTrials:getTrialPlanetAndCity(pPlayer)

	if (trialData.trialNpc == nil) then
		printLuaError("PadawanTrials:notifyEnteredMainLocSpawnArea, nil trialNpc for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial number " .. trialNumber .. "\n.")
		self:failTrial(pPlayer)
		return 1
	end

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

	deleteData(playerID .. ":mainLocSpawnAreaID")
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

function PadawanTrials:createTargetLocation(pPlayer, isThirdLocation)
	if (isThirdLocation == nil) then
		isThirdLocation = false
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNumber]

	if (trialData == nil) then
		printLuaError("PadawanTrials:createTargetLocation, unable to get trial data for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber)
		return
	end

	local trialName = trialData.trialName
	local zoneName = SceneObject(pPlayer):getZoneName()

	local targetLoc

	if (isThirdLocation and trialData.thirdTargetLoc ~= nil) then
		targetLoc = trialData.thirdTargetLoc
		zoneName = targetLoc[4]
	elseif (trialData.targetLoc ~= nil) then
		targetLoc = trialData.targetLoc
		zoneName = targetLoc[4]
	else
		targetLoc = getSpawnPoint(zoneName, SceneObject(pPlayer):getWorldPositionX(), SceneObject(pPlayer):getWorldPositionY(), 900, 1800, true)
	end

	if (targetLoc == nil) then
		printLuaError("Unable to find spawn point in PadawanTrials:createTargetLocation.")
		CreatureObject(pPlayer):sendSystemMessage("Failed to get a good spawn location, please submit a bug report.")
		self:failTrial(pPlayer)
		return
	end

	local npcTemplate

	if (isThirdLocation and trialData.thirdTargetNpc ~= nil) then
		npcTemplate = trialData.thirdTargetNpc
	elseif (trialData.targetNpc ~= nil) then
		npcTemplate = trialData.targetNpc
	end

	if (npcTemplate ~= nil) then
		local pActiveArea = spawnActiveArea(zoneName, "object/active_area.iff", targetLoc[1], targetLoc[2], targetLoc[3], 100, 0)
		local playerID = SceneObject(pPlayer):getObjectID()

		if pActiveArea == nil then
			printLuaError("PadawanTrials:createTargetLocation, failed to create active area.")
			CreatureObject(pPlayer):sendSystemMessage("Failed to spawn quest area, please submit a bug report.")
			self:failTrial(pPlayer)
			return
		end

		local areaID = SceneObject(pActiveArea):getObjectID()
		writeData(areaID .. ":ownerID", playerID)
		writeData(playerID .. ":targetLocSpawnAreaID", areaID)

		if (isThirdLocation) then
			writeData(areaID .. ":isThirdLoc", 1)
		end

		createObserver(ENTEREDAREA, "PadawanTrials", "notifyEnteredTargetLocSpawnArea", pActiveArea)
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):addWaypoint(zoneName, "Padawan Trial waypoint", "", targetLoc[1], targetLoc[3], WAYPOINTBLUE, true, true, WAYPOINTQUESTTASK)
	end
end

function PadawanTrials:notifyEnteredTargetLocSpawnArea(pArea, pPlayer)
	if (pArea == nil or pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local areaID = SceneObject(pArea):getObjectID()
	local ownerID = readData(areaID .. ":ownerID")
	local isThirdLocation = readData(areaID .. ":isThirdLoc") == 1

	if (playerID ~= ownerID) then
		return 0
	end

	deleteData(playerID .. ":targetLocSpawnAreaID")
	deleteData(areaID .. ":ownerID")
	deleteData(areaID .. ":isThirdLoc")
	SceneObject(pArea):destroyObjectFromWorld()

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNumber]

	if (trialData == nil) then
		printLuaError("PadawanTrials:notifyEnteredTargetLocSpawnArea, unable to get trial data for player " .. SceneObject(pPlayer):getCustomObjectName() .. " on trial " .. trialNumber)
		return 1
	end

	local npcTemplate

	if (isThirdLocation and trialData.thirdTargetNpc ~= nil) then
		npcTemplate = trialData.thirdTargetNpc
	elseif (trialData.targetNpc ~= nil) then
		npcTemplate = trialData.targetNpc
	end

	if (npcTemplate ~= nil) then
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
			printLuaError("PadawanTrials:notifyEnteredTargetLocSpawnArea, failed to spawn quest mobile.")
			CreatureObject(pPlayer):sendSystemMessage("Failed to spawn quest mobile, please submit a bug report.")
			self:failTrial(pPlayer)
			return 1
		end

		local npcID = SceneObject(pNpc):getObjectID()
		writeData(npcID .. ":ownerID", playerID)

		if (isThirdLocation and trialData.thirdTargetName ~= nil) then
			SceneObject(pNpc):setCustomObjectName(trialData.thirdTargetName)
		elseif (trialData.targetNpcName ~= nil) then
			SceneObject(pNpc):setCustomObjectName(trialData.targetNpcName)
		end

		if (not string.find(trialData.targetNpc, ".iff")) then
			if ((isThirdLocation and trialData.thirdTargetKillable ~= nil and trialData.thirdTargetKillable) or trialData.targetKillable) then
				createObserver(OBJECTDESTRUCTION, "PadawanTrials", "notifyQuestTargetDead", pNpc)
			else
				CreatureObject(pNpc):setPvpStatusBitmask(0)
			end
		end

		if (trialData.trialType == TRIAL_TALK and not string.find(trialData.targetNpc, ".iff")) then
			CreatureObject(pNpc):setOptionsBitmask(136)

			if (isThirdLocation) then
				AiAgent(pNpc):setConvoTemplate("padawan_" .. trialData.trialName .. "_03_convo_template")
			else
				AiAgent(pNpc):setConvoTemplate("padawan_" .. trialData.trialName .. "_02_convo_template")
			end
		end

		local pActiveArea = spawnActiveArea(planetName, "object/active_area.iff", locX, locZ, locY, 32, 0)

		if pActiveArea == nil then
			printLuaError("PadawanTrials:notifyEnteredTargetLocSpawnArea, failed to create npc destroy active area.")
			CreatureObject(pPlayer):sendSystemMessage("Failed to spawn quest area, please submit a bug report.")
			self:failTrial(pPlayer)
			return 1
		end

		local areaID = SceneObject(pActiveArea):getObjectID()
		writeData(areaID .. ":ownerID", playerID)
		writeData(areaID .. ":npcID", npcID)
		createObserver(EXITEDAREA, "PadawanTrials", "notifyExitedLocDestroyArea", pActiveArea)
	end

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
		local trialNumber = JediTrials:getCurrentTrial(pOwner)
		local trialData = padawanTrialQuests[trialNumber]

		if (trialData == nil) then
			printLuaError("PadawanTrials:notifyQuestTargetDead, unable to get trial data for player " .. SceneObject(pOwner):getCustomObjectName() .. " on trial " .. trialNumber)
			return 1
		end

		if (trialData.killMessage ~= nil and trialData.killMessage ~= "") then
			CreatureObject(pOwner):sendSystemMessage(trialData.killMessage)
		end

		CreatureObject(pOwner):sendSystemMessage("@jedi_trials:padawan_trials_return_to_npc")
		writeData(ownerID .. ":JediTrials:killedTarget", 1)
		self:createMainLocation(pOwner)
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

	local areaID = readData(playerID .. ":mainLocSpawnAreaID")
	local pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	deleteData(areaID .. ":ownerID")
	deleteData(playerID .. ":mainLocSpawnAreaID")

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

	areaID = readData(playerID .. ":targetLocSpawnAreaID")
	pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	deleteData(areaID .. ":ownerID")
	deleteData(areaID .. ":isThirdLoc")
	deleteData(playerID .. ":targetLocSpawnAreaID")
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
	deleteData(playerID .. ":JediTrials:spokeToTarget01")
	deleteData(playerID .. ":JediTrials:spokeToTarget02")

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
	deleteData(playerID .. ":JediTrials:spokeToTarget01")
	deleteData(playerID .. ":JediTrials:spokeToTarget02")

	CreatureObject(pPlayer):setScreenPlayState(1, trialState) -- Complete Trial.
	JediTrials:setCurrentTrial(pPlayer, 0)
	JediTrials:setTrialsCompleted(pPlayer, trialsCompleted)
	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_next_trial") -- You have done well and successfully completed the trial you faced. To undertake your next trial, simply meditate at any Force shrine.
end


function PadawanTrials:showCurrentTrial(pShrine, pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialData = padawanTrialQuests[trialNumber]

	local sui = SuiMessageBox.new("PadawanTrials", "handleShowInfoChoice")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setTargetNetworkId(SceneObject(pShrine):getObjectID())
	sui.setCancelButtonText("@jedi_trials:button_close") -- Close
	sui.setOtherButtonText("@jedi_trials:button_restart") -- Restart Current Trial
	sui.setOkButtonText("@jedi_trials:button_abort_padawan") -- Quit Padawan Trials
	-- Other Button setup subscribe
	sui.setProperty("btnRevert", "OnPress", "RevertWasPressed=1\r\nparent.btnOk.press=t")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "btnRevert", "RevertWasPressed")

	if (trialData.trialType == TRIAL_LIGHTSABER) then
		local trialState = JediTrials:getTrialStateName(pPlayer, trialNumber)
		if (CreatureObject(pPlayer):hasScreenPlayState(1, trialState .. "_saber")) then
			sui.setPrompt("@jedi_trials:" .. trialData.trialName .. "_02")
		else
			sui.setPrompt("@jedi_trials:" .. trialData.trialName .. "_01")
		end
	else
		local suiPrompt = "@jedi_trials:" .. trialData.trialName .. "_03"

		if (trialData.trialType == TRIAL_HUNT) then
			local targetCount = tonumber(readScreenPlayData(pPlayer, "JediTrials", "huntTargetCount"))

			if (targetCount ~= nil and targetCount > 0) then
				suiPrompt = suiPrompt .. " " .. targetCount
			else
				local planetData = JediTrials:getTrialPlanetAndCity(pPlayer)
				local cityName = planetData[2]
				cityName = string.gsub(cityName, "_", " ")
				cityName = string.gsub(" "..cityName, "%W%l", string.upper):sub(2)

				local msgPrefix =  "@jedi_trials:" .. trialData.trialName .. "_01 " .. "@jedi_trials:" .. planetData[1]
				local msgPostfix =  "@jedi_trials:" .. trialData.trialName .. "_02 " .. cityName .. "."
				suiPrompt = msgPrefix .. " " .. msgPostfix
			end
		end

		sui.setPrompt(suiPrompt)
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
		return
	elseif (restart ~= nil) then
		self:restartCurrentPadawanTrial(pPlayer)
	elseif (eventIndex == 0) then
		self:quitPadawanTrials(pPlayer)
	end
end

function PadawanTrials:onPlayerLoggedIn(pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (trialNumber >= 1) then
		local trialData = padawanTrialQuests[trialNumber]
		local trialState = JediTrials:getTrialStateName(pPlayer, trialNumber)

		if (trialData.trialType == TRIAL_HUNT and readScreenPlayData(pPlayer, "JediTrials", "huntTargetGoal") ~= nil) then
			dropObserver(KILLEDCREATURE, "PadawanTrials", "notifyKilledHuntTarget", pPlayer)

			if (self:hasCompletedHunt(pPlayer) and not JediTrials:hasTrialArea(pPlayer)) then
				self:createMainLocation(pPlayer)
			elseif (not self:hasCompletedHunt(pPlayer)) then
				createObserver(KILLEDCREATURE, "PadawanTrials", "notifyKilledHuntTarget", pPlayer)
			end
		elseif (trialData.trialType == TRIAL_LIGHTSABER and not CreatureObject(pPlayer):hasScreenPlayState(1, trialState .. "_crystal")) then
			if (CreatureObject(pPlayer):hasScreenPlayState(1, trialState .. "_saber")) then
				dropObserver(TUNEDCRYSTAL, "PadawanTrials", "notifyTunedLightsaberCrystal", pPlayer)
				createObserver(TUNEDCRYSTAL, "PadawanTrials", "notifyTunedLightsaberCrystal", pPlayer)
			else
				dropObserver(PROTOTYPECREATED, "PadawanTrials", "notifyCraftedTrainingSaber", pPlayer)
				createObserver(PROTOTYPECREATED, "PadawanTrials", "notifyCraftedTrainingSaber", pPlayer)
			end
		elseif (trialData.trialType ~= TRIAL_HUNT and trialData.trialType ~= TRIAL_LIGHTSABER and not JediTrials:hasTrialArea(pPlayer) and trialData.trialName ~= "pannaqa" and readData(playerID .. ":JediTrials:acceptedTask") == 0) then
			-- Restarts trial if player does not have a properly stored spawn location
			if (JediTrials:getTrialLocation(pPlayer) == nil) then
				self:startTrial(pPlayer, trialNumber, true)
			else
				self:createMainLocation(pPlayer)
			end
		end
	end
end
