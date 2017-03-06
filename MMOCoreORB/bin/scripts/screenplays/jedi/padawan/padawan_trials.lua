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

	if (trialsCompleted >= #padawanTrialQuests and trialsCompleted < 8) then
		CreatureObject(pPlayer):sendSystemMessage("You have completed all of the current Padawan Trials, more will be added in the near future.")
		return
	end

	if (trialsCompleted == 8) then
	-- TODO: Crafting Trial, after implemented uncomment below lines.
	-- JediPadawanTrialCraftLightsaberScreenPlay:startTrial(pPlayer)
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
		PadawanTrials:startTrial(pPlayer, randTrial)
	end
end

function PadawanTrials:resetAllPadawanTrials(pPlayer)
	--Remove All States.
	for i = 1, #padawanTrialQuests, 1 do
		local trialState = JediTrials:getTrialStateName(pPlayer, i)
		CreatureObject(pPlayer):removeScreenPlayState(1, trialState)
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (CreatureObject(pPlayer):hasSkill("force_title_jedi_rank_01")) then
		surrenderSkill(pPlayer, "force_title_jedi_rank_01")
	end

	JediTrials:resetTrialData(pPlayer, "padawan")
	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
end

function PadawanTrials:startTrial(pPlayer, trialNum)
	JediTrials:setCurrentTrial(pPlayer, trialNum)

	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. ":JediTrials:acceptedTask")
	deleteData(playerID .. ":JediTrials:killedTarget")
	deleteData(playerID .. ":JediTrials:spokeToTarget")

	local planetName = trialsCivilizedPlanets[getRandomNumber(1, #trialsCivilizedPlanets)]
	local trialData = padawanTrialQuests[trialNum]

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
	local planetData = JediTrials:getTrialPlanetAndCity(pPlayer)
	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local cityName = planetData[2]
	cityName = string.gsub(cityName, "_", " ")
	cityName = string.gsub(" "..cityName, "%W%l", string.upper):sub(2)

	local trialData = padawanTrialQuests[trialNumber]
	local msgPrefix =  "@jedi_trials:" .. trialData.trialName .. "_01 " .. "@jedi_trials:" .. planetData[1]
	local msgPostfix =  "@jedi_trials:" .. trialData.trialName .. "_02 " .. cityName .. "."
	local msgFinal = msgPrefix .. " " .. msgPostfix

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
		deleteData(areaID .. ":ownerID")
		deleteData(areaID .. ":npcID")
		return 1
	end

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)

	if (trialNumber == nil or not JediTrials:isOnPadawanTrials(pPlayer)) then
		self:removeNpcDestroyActiveArea(pPlayer)
		deleteData(npcID .. ":ownerID")
		deleteData(npcID .. ":destroyNpcOnExit")
		SceneObject(pNpc):destroyObjectFromWorld()
		return 1
	end

	local trialState = JediTrials:getTrialStateName(pPlayer, trialNumber)

	if (trialState == nil or CreatureObject(pPlayer):hasScreenPlayState(1, trialState) or readData(npcID .. ":destroyNpcOnExit") == 1) then
		self:removeNpcDestroyActiveArea(pPlayer)
		deleteData(npcID .. ":ownerID")
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

	local pNpc = spawnMobile(planetName, trialData.targetNpc, 0, locX, locZ, locY, getRandomNumber(180) - 180, 0)

	if (pNpc == nil) then
		printLuaError("PadawanTrials:notifyEnteredSecondLocSpawnArea, failed to spawn quest mobile.")
		CreatureObject(pPlayer):sendSystemMessage("Failed to spawn quest mobile, please submit a bug report.")
		self:failTrial(pPlayer)
		return 1
	end

	local npcID = SceneObject(pNpc):getObjectID()
	writeData(npcID .. ":ownerID", playerID)

	if (not trialData.targetKillable) then
		CreatureObject(pNpc):setPvpStatusBitmask(0)
	else
		createObserver(OBJECTDESTRUCTION, "PadawanTrials", "notifyQuestTargetDead", pNpc)
	end

	if (trialData.trialType == TRIAL_TALK) then
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

	local trialNumber = JediTrials:getCurrentTrial(pPlayer)
	local trialState = JediTrials:getTrialStateName(pPlayer, trialNumber)

	local trialsCompleted = JediTrials:getTrialsCompleted(pPlayer)

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_next_trial") -- You have done well and successfully completed the trial you faced. To undertake your next trial, simply meditate at any Force shrine.
	CreatureObject(pPlayer):setScreenPlayState(1, trialState) -- Complete Trial.
	JediTrials:setCurrentTrial(pPlayer, 0)
	JediTrials:setTrialsCompleted(pPlayer, trialsCompleted + 1)
	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
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
	sui.setPrompt("@jedi_trials:" .. trialData.trialName .. "_03")

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
