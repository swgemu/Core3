local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

--[[
Situations to test:
1P takes down shield, 1P escorts commander (no extra reward)
1P takes down shield, 1P dies, 1P escorts commander on last chance (1P should fail this if a 2P captures commander, no extra reward either way)
1P takes down shield, 2P escorts commander, 2P dies/abandons escort, 1P captures (2P fails)
1P takes down shield, 2P escorts, 2P dies, 1P escorts, 1P dies (both fail)
]]
FsCsCommander = {
	commanderDespawnTime = 60 * 60 * 1000, -- Time after spawning before commander automatically despawns

	rescueSpawnTimer = { 180, 300 }, -- Min/max time until a wave of npcs attempts to save the commander
	rescueAmount = { 1, 2 }, -- Number of rescuers to spawn
	runAwayTime = 180 * 1000, -- Time commander can run until he cant be recovered

	-- Defense wave data
	rescueMobDataTable = {
		spawnerPulse = 120 * 1000, -- Time between spawn pulses
		maxSpawn = 2, -- Max waves of mobiles to spawn over the entire lifetime of the spawner
		maxPopulation = 2, -- Max mobs to have up at any one time
		mobileLifespan = 300 * 1000, -- Time until spawned mobs should be destroyed
		expireTime = 10 * 1000, -- Time until spawner should expire
		aiHandlerFunc = "setupRescueMob" -- Name of function that should setup a defender after it's spawned
	},

	rescueMobSpawnList = {
		-- { "template", minToSpawn, maxToSpawn, weight }
		{ "sith_shadow_pirate_nonaggro", 1, 2, 2 },
	},
}

function FsCsCommander:captureCommander(pCommander, pPlayer)
	if (pCommander == nil or pPlayer == nil) then
		return
	end

	local commanderID = SceneObject(pCommander):getObjectID()
	local playerID = SceneObject(pPlayer):getObjectID()
	local theaterID = readData(commanderID .. ":theaterID")

	local capturedByID = readData(commanderID .. ":capturedBy")
	local pCapturedBy = getCreatureObject(capturedByID)

	if (pCapturedBy == nil) then
		return
	end

	deleteData(commanderID .. ":currentlyFree")

	if (capturedByID == playerID and (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_LAST_CHANCE) or QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE) or QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC))) then
		-- This block covers the player that captures the commander on a last chance or if doing it solo
		if QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_LAST_CHANCE) then
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_LAST_CHANCE)
		elseif QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE) then
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE)
		elseif QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC) then
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC)
		end

		self:setPlayerAsEscorter(pCommander, pPlayer)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI)
		writeData(playerID .. ":fsCounterStrike:commanderID", commanderID)
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_cs_capd_commander")
	elseif (capturedByID ~= playerID and QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_LAST_CHANCE)) then
		-- This block covers if the player was on a last chance after dying but someone else captured, resets player to start
		writeData(commanderID .. ":shieldKillerCantCapture", 1)
		FsCounterStrike:resetPlayerToStart(pPlayer)
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_cs_commander_cap_other")
	elseif (capturedByID ~= playerID and QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE)) then
		-- This block covers notifying the player that took down the shield that they are secondary escort if someone else captures
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC)
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_cs_escort_commander_sec")
		self:createCommanderWaypoint(pPlayer, theaterID)
	elseif (capturedByID == playerID and QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)) then
		-- This block covers the player doing the capture if they are assisting another player
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)

		self:setPlayerAsEscorter(pCommander, pPlayer)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI)
		writeData(playerID .. ":fsCounterStrike:commanderID", commanderID)
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_cs_capd_commander_via_group")
	else
		local errorLog = "FsCsCommander:captureCommander(), got to end of if block."
		errorLog = errorLog .. " Captured by: " .. capturedByID .. ", pPlayerID: " .. playerID .. ". "
		errorLog = errorLog .. " 1: " .. tostring(QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)) .. ". "
		errorLog = errorLog .. " 2: " .. tostring(QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_LAST_CHANCE)) .. ". "
		errorLog = errorLog .. " 3: " .. tostring(QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_ENSURE_CAPTURE)) .. ". "
		printLuaError(errorLog)
	end
end

function FsCsCommander:setPlayerAsEscorter(pCommander, pPlayer)
	if (pCommander == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local commanderID = SceneObject(pCommander):getObjectID()
	local theaterID = readData(commanderID .. ":theaterID")

	writeData(commanderID .. ":escorterID", playerID)
	writeData(theaterID .. ":shouldStopSpawn", 1)
	self:createCommanderWaypoint(pPlayer, theaterID)

	AiAgent(pCommander):setFollowState(3)
	AiAgent(pCommander):setAiTemplate("escort")
	AiAgent(pCommander):setFollowObject(pPlayer)
	AiAgent(pCommander):executeBehavior()
end

function FsCsCommander:createCommander(pTheater)
	if (pTheater == nil) then
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	local commanderID = readData(theaterID .. ":commanderID")
	local pCommander = getSceneObject(commanderID)

	if (pCommander ~= nil) then
		self:killCommander(pCommander)
	end

	local shieldKillerID = readData(theaterID .. ":attackerID")
	local tentIndex = readData(theaterID .. ":tentIndex")

	local theaterX = SceneObject(pTheater):getWorldPositionX()
	local theaterZ = SceneObject(pTheater):getWorldPositionZ()
	local theaterY = SceneObject(pTheater):getWorldPositionY()

	local tentData = FsCounterStrike.campLayout[tentIndex]

	local tentX = theaterX + tentData[2]
	local tentZ = theaterZ + tentData[3]
	local tentY = theaterY + tentData[4]

	pCommander = spawnMobile("dathomir", "sith_shadow_mercenary_nofaction", 0, tentX, tentZ, tentY, 0, 0)

	if (pCommander == nil) then
		printLuaError("FsCsCommander:createCommander, unable to create commander.")
		return
	end

	SceneObject(pCommander):setObjectMenuComponent("FsCampCommanderMenuComponent")
	commanderID = SceneObject(pCommander):getObjectID()
	writeData(theaterID .. ":commanderID", commanderID)

	CreatureObject(pCommander):setPvpStatusBitmask(0)

	writeData(commanderID .. ":shieldKillerID", shieldKillerID)
	writeData(commanderID .. ":theaterID", theaterID)

	local areaX = 5315
	local areaZ = 78
	local areaY = -4136

	if (FsCounterStrike.testMode) then
		local spawnPoint = getSpawnPoint("dathomir", theaterX, theaterY, 800, 1000, true)
		areaX = math.floor(spawnPoint[1])
		areaZ = math.floor(spawnPoint[2])
		areaY = math.floor(spawnPoint[3])
	end

	writeData(theaterID .. ":commanderTurnin:X", areaX)
	writeData(theaterID .. ":commanderTurnin:Y", areaY)
	local pActiveArea = spawnActiveArea("dathomir", "object/active_area.iff", areaX, areaZ, areaY, 15, 0)

	if pActiveArea ~= nil then
		local areaID = SceneObject(pActiveArea):getObjectID()
		createObserver(ENTEREDAREA, "FsCsCommander", "notifyEnteredCommanderTurninArea", pActiveArea)
		writeData(theaterID .. ":turninAreaID", areaID)
		writeData(areaID .. ":theaterID", theaterID)
	end

	createEvent(self.commanderDespawnTime, "FsCsCommander", "killCommander", pCommander, "")
end

function FsCsCommander:notifyEnteredCommanderTurninArea(pArea, pCreature)
	if (pArea == nil or pCreature == nil or not SceneObject(pCreature):isCreatureObject()) then
		return 0
	end

	if SceneObject(pCreature):getObjectName() ~= "shadow_mercenary_nofaction" then
		return 0
	end

	local areaID = SceneObject(pArea):getObjectID()

	local creatureID = SceneObject(pCreature):getObjectID()
	local theaterID = readData(areaID .. ":theaterID")
	local commanderID = readData(theaterID .. ":commanderID")

	if (creatureID ~= commanderID) then
		return 0
	end

	local escorterID = readData(commanderID .. ":escorterID")
	local teamTurnin = false

	local pEscorter = getSceneObject(escorterID)

	if (pEscorter == nil) then
		printLuaError("FsCsCommander:notifyEnteredCommanderTurninArea unable to get escorter object, returned nil.")
		return 1
	end

	local shieldKillerID = readData(commanderID .. ":shieldKillerID")

	local pShieldKiller = getSceneObject(shieldKillerID)

	if (pShieldKiller == nil) then
		printLuaError("FsCsCommander:notifyEnteredCommanderTurninArea unable to get shieldkiller object, returned nil.")
		return 1
	end

	if (shieldKillerID ~= escorterID and FsCounterStrike:isOnEscort(pShieldKiller)) then
		teamTurnin = true
	end

	SceneObject(pCreature):destroyObjectFromWorld()

	if (teamTurnin) then
		FsCounterStrike:completeQuest(pEscorter, true)
		FsCounterStrike:completeQuest(pShieldKiller, true)
	else
		FsCounterStrike:completeQuest(pEscorter, false)
	end

	deleteData(commanderID .. ":escorterID")
	deleteData(commanderID .. ":shieldKillerID")
	deleteData(commanderID .. ":theaterID")
	deleteData(theaterID .. ":commanderTurnin:X")
	deleteData(theaterID .. ":commanderTurnin:Y")
	deleteData(theaterID .. ":turninAreaID")
	deleteData(theaterID .. ":commanderID")
	deleteData(areaID .. ":theaterID")
	deleteData(commanderID .. ":capturedBy")
	deleteData(commanderID .. ":shieldKillerCantCapture")
	deleteData(commanderID .. ":rescueSpawnPending")

	return 1
end

function FsCsCommander:handleCommanderAbandoned(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local commanderID = readData(playerID .. ":fsCounterStrike:commanderID")

	local pCommander = getSceneObject(commanderID)

	if (pCommander == nil) then
		FsCounterStrike:resetPlayerToStart(pPlayer)
		deleteData(playerID .. ":fsCounterStrike:commanderID")
		return
	end

	self:handleCommanderEscorterFailure(pPlayer, pCommander)
end

function FsCsCommander:handleCommanderEscorterFailure(pPlayer, pCommander)
	local playerID = SceneObject(pPlayer):getObjectID()
	local commanderID = SceneObject(pCommander):getObjectID()
	local escorterID = readData(commanderID .. ":escorterID")

	-- Shouldn't happen, but just in case
	if (escorterID ~= playerID) then
		return
	end

	local shieldKillerID = readData(commanderID .. ":shieldKillerID")

	local pShieldKiller = getSceneObject(shieldKillerID)

	if (pShieldKiller == nil) then
		return
	end

	AiAgent(pCommander):setFollowObject(nil)
	writeData(commanderID .. ":currentlyFree", 1)

	if (escorterID ~= shieldKillerID) then
		local shieldKillerCantCapture = readData(commanderID .. ":shieldKillerCantCapture")

		if (shieldKillerCantCapture == 1) then
			self:killCommander(pCommander)
			return
		end

		AiAgent(pCommander):setAiTemplate("manualescort")
		createEvent(10, "FsCsCommander", "doRun", pCommander, "")
		createEvent(self.runAwayTime * 1000, "FsCsCommander", "runAwaySuccessful", pCommander, "")
		writeData(commanderID .. ":canBeRecaptured", 1)
		CreatureObject(pShieldKiller):sendSystemMessage("@fs_quest_village:commander_is_free")

		FsCounterStrike:resetPlayerToStart(pPlayer)
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_primary_escort_fail")
	else
		self:killCommander(pCommander)
	end

	deleteData(playerID .. ":fsCounterStrike:commanderID")
end

function FsCsCommander:doRun(pCommander)
	if (pCommander == nil) then
		return
	end

	local commanderID = SceneObject(pCommander):getObjectID()

	if (readData(commanderID .. ":currentlyFree") == 0 or readData(commanderID .. ":deathSequence") ~= 0) then
		return
	end

	local runLoc = getSpawnPoint("dathomir", SceneObject(pCommander):getWorldPositionX(), SceneObject(pCommander):getWorldPositionY(), 50, 100, true)

	AiAgent(pCommander):stopWaiting()
	AiAgent(pCommander):setWait(0)
	AiAgent(pCommander):setNextPosition(runLoc[1], runLoc[2], runLoc[3], 0)
	AiAgent(pCommander):setHomeLocation(runLoc[1], runLoc[2], runLoc[3], 0)
	AiAgent(pCommander):executeBehavior()

	createEvent(10 * 1000, "FsCsCommander", "doRun", pCommander, "")
end

function FsCsCommander:runAwaySuccessful(pCommander)
	if (pCommander == nil) then
		return
	end

	local commanderID = SceneObject(pCommander):getObjectID()

	if (readData(commanderID .. ":currentlyFree") == 0 or readData(commanderID .. ":deathSequence") ~= 0) then
		return
	end

	self:killCommander(pCommander)
end

function FsCsCommander:killCommander(pCommander)
	if (pCommander == nil) then
		return
	end

	local commanderID = SceneObject(pCommander):getObjectID()

	CreatureObject(pCommander):setPosture(KNOCKEDDOWN)
	AiAgent(pCommander):setAiTemplate("wait")
	AiAgent(pCommander):setFollowState(0)
	AiAgent(pCommander):setFollowObject(nil)
	writeData(commanderID .. ":deathSequence", 1)
	createEvent(5000, "FsCsCommander", "doCommanderDeathSequence", pCommander, "")
end

function FsCsCommander:doCommanderDeathSequence(pCommander)
	if (pCommander == nil) then
		return
	end

	local commanderID = SceneObject(pCommander):getObjectID()

	local theaterID = readData(commanderID .. ":theaterID")

	local pTheater = getSceneObject(theaterID)

	if (pTheater == nil) then
		SceneObject(pCommander):destroyObjectFromWorld()
		return
	end

	local deathSequence = readData(commanderID .. ":deathSequence")

	if (deathSequence == 0) then
		return
	end

	local spatialString

	if (deathSequence == 1) then
		spatialString = "commander_pain"
	elseif (deathSequence == 2) then
		spatialString = "commander_pain2"
	elseif (deathSequence == 3) then
		spatialString = "commander_pain3"
	else
		local escorterID = readData(commanderID .. ":escorterID")
		local pEscorter = getSceneObject(escorterID)

		if (pEscorter ~= nil) then
			self:notifyCommanderDied(pTheater, pEscorter, commanderID)
		end

		local shieldKillerID = readData(commanderID .. ":shieldKillerID")
		local pShieldKiller = getSceneObject(shieldKillerID)

		if (pShieldKiller ~= nil and pShieldKiller ~= pEscorter) then
			self:notifyCommanderDied(pTheater, pShieldKiller, commanderID)
		end

		deleteData(theaterID .. ":commanderTurnin:X")
		deleteData(theaterID .. ":commanderTurnin:Y")
		local areaID = readData(theaterID .. ":turninAreaID")

		local pArea = getSceneObject(areaID)

		if (pArea ~= nil) then
			SceneObject(pArea):destroyObjectFromWorld()
		end

		deleteData(theaterID .. ":turninAreaID")
		deleteData(areaID .. ":theaterID")

		SceneObject(pCommander):destroyObjectFromWorld()

		deleteData(commanderID .. ":shieldKillerID")
		deleteData(commanderID .. ":theaterID")
		deleteData(commanderID .. ":deathSequence")
		deleteData(commanderID .. ":escorterID")
		deleteData(theaterID .. ":commanderID")
		deleteData(commanderID .. ":shieldKillerCantCapture")
		deleteData(commanderID .. ":canBeRecaptured")
		deleteData(commanderID .. ":currentlyFree")
		deleteData(commanderID .. ":capturedBy")
		deleteData(commanderID .. ":rescueSpawnPending")

		return
	end

	spatialChat(pCommander, "@fs_quest_village:" .. spatialString)
	writeData(commanderID .. ":deathSequence", deathSequence + 1)
	createEvent(getRandomNumber(5, 10) * 1000, "FsCsCommander", "doCommanderDeathSequence", pCommander, "")
end

function FsCsCommander:notifyCommanderDied(pTheater, pPlayer, commanderID)
	if (pTheater == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local playerOwnedCommander = readData(playerID .. ":fsCounterStrike:commanderID")

	if (commanderID ~= 0 and playerOwnedCommander ~= 0 and commanderID ~= playerOwnedCommander) then
		return
	end

	self:destroyCommanderWaypoint(pPlayer)
	deleteData(playerID .. ":fsCounterStrike:commanderID")
	FsCounterStrike:resetPlayerToStart(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:commander_died_toxins")
end

function FsCsCommander:destroyCommanderWaypoint(pPlayer)
	local waypointID = readData(SceneObject(pPlayer):getObjectID() .. ":village:csCommanderWaypoint")

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):removeWaypoint(waypointID, true)
	end

	deleteData(SceneObject(pPlayer):getObjectID() .. ":village:csCommanderWaypoint")
end

function FsCsCommander:createCommanderWaypoint(pPlayer, theaterID)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		local wayX = readData(theaterID .. ":commanderTurnin:X")
		local wayY = readData(theaterID .. ":commanderTurnin:Y")
		local wayDesc = "Return the Commander"

		if (FsCounterStrike.testMode) then
			wayDesc = "Return the Commander (Testing mode)"
		end

		local waypointID = PlayerObject(pGhost):addWaypoint("dathomir", wayDesc, "", wayX, wayY, WAYPOINTYELLOW, true, true, 0)
		writeData(SceneObject(pPlayer):getObjectID() .. ":village:csCommanderWaypoint", waypointID)
	end
end

function FsCsCommander:spawnRescuers(pCommander)
	if (pCommander == nil) then
		return
	end

	local commanderID = SceneObject(pCommander):getObjectID()

	if (readData(commanderID .. ":rescueSpawnPending") ~= 1) then
		return
	end

	if (readData(commanderID .. ":currentlyFree") == 1 or readData(commanderID .. ":deathSequence") ~= 0) then
		deleteData(commanderID .. ":rescueSpawnPending")
		return
	end

	local escorterID = readData(commanderID .. ":escorterID")
	local pEscorter = getSceneObject(escorterID)

	if (pEscorter == nil) then
		return
	end

	local theaterID = readData(commanderID .. ":theaterID")

	local pTheater = getSceneObject(theaterID)

	if (pTheater == nil) then
		return
	end

	-- Only trigger rescue wave if player is in range of commander
	if (SceneObject(pCommander):isInRangeWithObject(pEscorter, 300)) then
		local spawnPoint = getSpawnPoint("dathomir", SceneObject(pCommander):getWorldPositionX(), SceneObject(pCommander):getWorldPositionY(), 75, 100, true)
		QuestSpawner:createQuestSpawner("FsCsCommander", "rescueMobDataTable", "rescueMobSpawnList", spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, "dathomir", pTheater)
	end

	createEvent(getRandomNumber(self.rescueSpawnTimer[1], self.rescueSpawnTimer[2]) * 1000, "FsCsCommander", "spawnRescuers", pCommander, "")
end

function FsCsCommander:setupRescueMob(pMobile)
	if (pMobile == nil) then
		return
	end

	local mobileID = SceneObject(pMobile):getObjectID()
	local spawnerID = readData(mobileID .. ":spawnerID")

	local pSpawner = getSceneObject(spawnerID)

	if pSpawner == nil then
		return
	end

	local theaterID = readData(spawnerID .. ":parentID")

	local pTheater = getSceneObject(theaterID)

	if (pTheater == nil) then
		return
	end

	local commanderID = readData(theaterID .. ":commanderID")
	local escorterID = readData(commanderID .. ":escorterID")

	local pEscorter = getSceneObject(escorterID)

	if (pEscorter == nil) then
		SceneObject(pMobile):destroyObjectFromWorld()
		return
	end

	AiAgent(pMobile):setAiTemplate("villageraider")
	AiAgent(pMobile):setFollowObject(pEscorter)
	AiAgent(pMobile):setDefender(pEscorter)

	createEvent(getRandomNumber(20, 60) * 1000, "FsCsCommander", "doRescuerSpatial", pMobile, "")
end

function FsCsCommander:doRescuerSpatial(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead() or getRandomNumber(100) < 75) then
		return
	end

	spatialChat(pMobile, "@fs_quest_village:rescue" .. getRandomNumber(1,10))
end
