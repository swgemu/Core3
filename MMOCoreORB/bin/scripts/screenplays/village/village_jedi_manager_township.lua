local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

-- Utils.
local Logger = require("utils.logger")
require("utils.helpers")

VillageJediManagerTownship = ScreenPlay:new {
	VILLAGE_TOTAL_NUMBER_OF_PHASES = 4,
	phaseChangeTimeOfDay = { hour = 18, min = 0 }, -- Hour of day, server military time, to change the phase. Comment out to disable

	VILLAGE_PHASE_DURATION = 3 * 7 * 24 * 60 * 60 * 1000 -- 3 weeks
}

-- Set the current Village Phase for the first time.
function VillageJediManagerTownship.setCurrentPhaseInit()
	if (not hasServerEvent("VillagePhaseChange")) then
		VillageJediManagerTownship.setCurrentPhase(1)
		VillageJediManagerTownship.setCurrentPhaseID(1)
		VillageJediManagerTownship.setLastPhaseChangeTime(os.time())
		createServerEvent(VillageJediManagerTownship.VILLAGE_PHASE_DURATION, "VillageJediManagerTownship", "switchToNextPhase", "VillagePhaseChange")
	else
		local eventID = getServerEventID("VillagePhaseChange")

		if (eventID == nil) then
			VillageJediManagerTownship:switchToNextPhase(true)
			return
		end

		local eventTimeLeft = getServerEventTimeLeft(eventID)

		if (eventTimeLeft == nil) then
			VillageJediManagerTownship:switchToNextPhase(true)
			return
		end

		if (eventTimeLeft < 0) then
			return
		end

		-- Fixes servers that were already running the village prior to the change in schedule handling
		local lastChange = tonumber(getQuestStatus("Village:lastPhaseChangeTime"))

		if (lastChange ~= nil and lastChange ~= 0) then
			return
		end

		VillageJediManagerTownship.setLastPhaseChangeTime(os.time())

		local timeToSchedule = (VillageJediManagerTownship.getNextPhaseChangeTime(false) - os.time()) * 1000

		rescheduleServerEvent("VillagePhaseChange", timeToSchedule)
	end
end

function VillageJediManagerTownship.getVillagePhaseDuration()
	return VillageJediManagerTownship.VILLAGE_PHASE_DURATION
end

function VillageJediManagerTownship.getNextPhaseChangeTime(includePast)
	local lastPhaseChange = VillageJediManagerTownship.getLastPhaseChangeTime()
	local nextPhaseChange = lastPhaseChange + (VillageJediManagerTownship.getVillagePhaseDuration() / 1000)

	local timeTable = os.date("*t", nextPhaseChange)
	local disregardTimeOfDay = VillageJediManagerTownship.getVillagePhaseDuration() < (24 * 60 * 60 * 1000)

	if (VillageJediManagerTownship.phaseChangeTimeOfDay ~= nil) then
		if (disregardTimeOfDay) then
			printf("VillageJediManagerTownship.getNextPhaseChangeTime disregarding phaseChangeTimeOfDay due to a phase duration under 24 hours.\n")
		else
			timeTable.hour = VillageJediManagerTownship.phaseChangeTimeOfDay.hour
			timeTable.min = VillageJediManagerTownship.phaseChangeTimeOfDay.min
			timeTable.sec = 0
		end
	end

	local returnTime = os.time(timeTable)

	if (returnTime < os.time() and not includePast and not disregardTimeOfDay) then
		returnTime = returnTime + 86400 -- If the time was modified by phaseChangeTimeOfDay and ended up being in the past, push it forward by 24 hours
	end

	return returnTime
end

function VillageJediManagerTownship.setLastPhaseChangeTime(time)
	setQuestStatus("Village:lastPhaseChangeTime", time)
end

function VillageJediManagerTownship.getLastPhaseChangeTime()
	local lastChange = tonumber(getQuestStatus("Village:lastPhaseChangeTime"))

	if (lastChange == nil) then
		lastChange = os.time()
		setQuestStatus("Village:lastPhaseChangeTime", lastChange)
	end

	return lastChange
end

function VillageJediManagerTownship.setCurrentPhaseID(phaseID)
	setQuestStatus("Village:phaseID", phaseID)
end

function VillageJediManagerTownship.getCurrentPhaseID()
	local curPhase = tonumber(getQuestStatus("Village:phaseID"))

	if (curPhase == nil) then
		return 1
	end

	return curPhase
end

-- Set the current Village Phase.
function VillageJediManagerTownship.setCurrentPhase(nextPhase)
	setQuestStatus("Village:CurrentPhase", nextPhase)
end

function VillageJediManagerTownship.getCurrentPhase()
	local curPhase = tonumber(getQuestStatus("Village:CurrentPhase"))

	if (curPhase == nil) then
		return 1
	end

	return curPhase
end

function VillageJediManagerTownship:switchToNextPhase(manualSwitch)
	if (manualSwitch == nil) then
		manualSwitch = false
	end

	if (not isZoneEnabled("dathomir")) then
		if (hasServerEvent("VillagePhaseChange")) then
			rescheduleServerEvent("VillagePhaseChange", 60 * 60 * 1000)
		end

		return
	end

	local nextPhaseChange = VillageJediManagerTownship.getNextPhaseChangeTime(true)

	if (manualSwitch) then
		nextPhaseChange = os.time()
	end

	VillageJediManagerTownship.setLastPhaseChangeTime(nextPhaseChange)

	local timeToSchedule = (VillageJediManagerTownship.getNextPhaseChangeTime(false) - os.time()) * 1000

	if (hasServerEvent("VillagePhaseChange")) then
		rescheduleServerEvent("VillagePhaseChange", timeToSchedule)
	else
		createServerEvent(timeToSchedule, "VillageJediManagerTownship", "switchToNextPhase", "VillagePhaseChange")
	end

	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	local phaseID = VillageJediManagerTownship.getCurrentPhaseID()
	VillageJediManagerTownship:despawnMobiles(currentPhase)
	VillageJediManagerTownship:despawnSceneObjects(currentPhase)
	VillageJediManagerTownship:handlePhaseChangeActiveQuests(phaseID, currentPhase)
	VillageCommunityCrafting:doEndOfPhaseCheck()
	VillageCommunityCrafting:doEndOfPhasePrizes()
	VillageJediManagerTownship:destroyVillageMasterObject()

	-- Despawn camps going into phase 4
	if (currentPhase == 3) then
		FsCounterStrike:despawnAllCamps()
	end

	if (currentPhase == 3 or currentPhase == 4) then
		VillageRaids:despawnTurrets()
	end

	currentPhase = currentPhase + 1

	if currentPhase > VillageJediManagerTownship.VILLAGE_TOTAL_NUMBER_OF_PHASES then
		currentPhase = 1
	end

	VillageJediManagerTownship.setCurrentPhase(currentPhase)
	VillageJediManagerTownship.setCurrentPhaseID(phaseID + 1)
	VillageJediManagerTownship:spawnMobiles(currentPhase, false)
	VillageJediManagerTownship:spawnSceneObjects(currentPhase, false)

	-- Spawn camps going into phase 3
	if (currentPhase == 3) then
		FsCounterStrike:pickPhaseCamps()
	end

	if (currentPhase == 2 or currentPhase == 3) then
		VillageCommunityCrafting:createAttributeValueTables()
		VillageCommunityCrafting:createProjectStatsTables()
	end

	VillageJediManagerTownship:createVillageMasterObject()

	if (currentPhase == 3 or currentPhase == 4) then
		local pMaster = VillageJediManagerTownship:getMasterObject()
		createEvent(60 * 1000, "VillageRaids", "doPhaseInit", pMaster, "")
	end

	Logger:log("Switching village phase to " .. currentPhase, LT_INFO)
end

function VillageJediManagerTownship:start()
	if (isZoneEnabled("dathomir")) then
		Logger:log("Starting the Village Township Screenplay.", LT_INFO)

		local currentPhase = VillageJediManagerTownship.getCurrentPhase()
		VillageJediManagerTownship.setCurrentPhaseInit()
		VillageJediManagerTownship:spawnMobiles(currentPhase, true)
		VillageJediManagerTownship:spawnSceneObjects(currentPhase, true)
		VillageJediManagerTownship:createVillageMasterObject()

		createNavMesh("dathomir", 5292, -4119, 210, true, "village_township")

		if (currentPhase == 3 or currentPhase == 4) then
			local pMaster = VillageJediManagerTownship:getMasterObject()
			createEvent(60 * 1000, "VillageRaids", "doPhaseInit", pMaster, "")

			if (currentPhase == 3) then
				local campList = FsCounterStrike:getPhaseCampList()

				if (campList == nil) then
					FsCounterStrike:pickPhaseCamps()
				else
					FsCounterStrike:spawnCamps()
				end
			end
		end
	end
end

function VillageJediManagerTownship:createVillageMasterObject()
	local phaseID = VillageJediManagerTownship.getCurrentPhaseID()
	local pMaster = spawnSceneObject("dathomir", "object/tangible/spawning/quest_spawner.iff", 5291, 78.5, -4126, 0, 0)

	if (pMaster == nil) then
		printLuaError("VillageJediManagerTownship:createVillageMasterObject(), unable to create master village object.")
		return
	end

	VillageJediManagerTownship:setMasterID(SceneObject(pMaster):getObjectID())
end

function VillageJediManagerTownship:destroyVillageMasterObject()
	local pMaster = VillageJediManagerTownship:getMasterObject()

	if (pMaster == nil) then
		return
	end

	SceneObject(pMaster):destroyObjectFromWorld()

	local phaseID = VillageJediManagerTownship.getCurrentPhaseID()
	deleteData("Village:masterID:" .. phaseID)
end

function VillageJediManagerTownship:setMasterID(objectID)
	local phaseID = VillageJediManagerTownship.getCurrentPhaseID()
	writeData("Village:masterID:" .. phaseID, objectID)
end

function VillageJediManagerTownship:getMasterObject()
	local phaseID = VillageJediManagerTownship.getCurrentPhaseID()
	local masterID = readData("Village:masterID:" .. phaseID)

	return getSceneObject(masterID)
end

-- Spawning functions.

function VillageJediManagerTownship:spawnMobiles(currentPhase, spawnStaticMobs)
	if (spawnStaticMobs == true) then
		local mobileTable = villageMobileSpawns[0]

		for i = 1, #mobileTable, 1 do
			local mobile = mobileTable[i]
			local pMobile = spawnMobile("dathomir", mobile[1], 0, mobile[2], mobile[3], mobile[4], mobile[5], 0)
			if (pMobile ~= nil) then
				CreatureObject(pMobile):setPvpStatusBitmask(0)
				if (mobile[6] ~= "") then
					self[mobile[6]](pMobile)
				end
				if (mobile[7] ~= "") then
					CreatureObject(pMobile):setOptionsBitmask(136)
					AiAgent(pMobile):setConvoTemplate(mobile[7])
				end
			end
		end
	end

	local mobileTable = villageMobileSpawns[currentPhase]

	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]
		local pMobile = spawnMobile("dathomir", mobile[1], 0, mobile[2], mobile[3], mobile[4], mobile[5], 0)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			if (mobile[6] ~= nil and mobile[6] ~= "") then
				self[mobile[6]](pMobile)
			end
			if (mobile[7] ~= nil and mobile[7] ~= "") then
				CreatureObject(pMobile):setOptionsBitmask(136)
				AiAgent(pMobile):setConvoTemplate(mobile[7])
			end
			local mobileID = SceneObject(pMobile):getObjectID()
			writeData("village:npc:object:" .. i, mobileID)
		end
	end
end

-- Despawn and cleanup current phase mobiles.
function VillageJediManagerTownship:despawnMobiles(currentPhase)
	local mobileTable = villageMobileSpawns[currentPhase]
	for i = 1, #mobileTable, 1 do
		local objectID = readData("village:npc:object:" .. i)
		local pMobile = getSceneObject(objectID)

		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
			deleteData("village:npc:object:" .. i)
		end
	end
end

function VillageJediManagerTownship:spawnSceneObjects(currentPhase, spawnStaticObjects)
	if (spawnStaticObjects == true) then
		local objectTable = villageObjectSpawns[0]
		foreach(objectTable, function(sceneObject)
			spawnSceneObject("dathomir", sceneObject[1], sceneObject[2], sceneObject[3], sceneObject[4], 0, math.rad(sceneObject[5]))
		end)
	end

	local objectTable = villageObjectSpawns[currentPhase]
	for i = 1, #objectTable, 1 do
		local sceneObject = objectTable[i]
		local pObject = spawnSceneObject("dathomir", sceneObject[1], sceneObject[2], sceneObject[3], sceneObject[4], 0, math.rad(sceneObject[5]))

		if (pObject ~= nil) then
			local objectID = SceneObject(pObject):getObjectID()
			writeData("village:scene:object:" .. i, objectID)
		end
	end
end

-- Despawn and cleanup current phase scene objects.
function VillageJediManagerTownship:despawnSceneObjects(currentPhase)
	local objectTable = villageObjectSpawns[currentPhase]
	for i = 1, #objectTable, 1 do
		local objectID = readData("village:scene:object:" .. i)
		local pObject = getSceneObject(objectID)

		if (pObject ~= nil) then
			SceneObject(pObject):destroyObjectFromWorld()
			deleteData("village:npc:object:" .. i)
		end
	end
end

function VillageJediManagerTownship:handlePhaseChangeActiveQuests(phaseID, currentPhase)
	local pMap = VillageJediManagerCommon.getActiveQuestList(phaseID)

	if (pMap == nil) then
		return
	end

	local questMap = LuaQuestVectorMap(pMap)
	local mapSize = questMap:getMapSize()

	for i = 1, mapSize, 1 do
		local playerID = tonumber(questMap:getMapKeyAtIndex(i - 1))
		removeQuestStatus(playerID .. ":village:activeQuestName")

		local pPlayer = getSceneObject(playerID)

		if (pPlayer ~= nil) then
			local pGhost = CreatureObject(pPlayer):getPlayerObject()

			if (pGhost ~= nil) then
				if (PlayerObject(pGhost):isOnline()) then
					self:doOnlinePhaseChangeFails(pPlayer, currentPhase)
				end
			end
		end
	end

	VillageJediManagerCommon.removeActiveQuestList(phaseID)
end

function VillageJediManagerTownship:doOnlinePhaseChangeFails(pPlayer, currentPhase)
	if (currentPhase == 1) then
		FsPhase1:doPhaseChangeFails(pPlayer)
	elseif (currentPhase == 2) then
		FsPhase2:doPhaseChangeFails(pPlayer)
	elseif (currentPhase == 3) then
		FsCounterStrike:doPhaseChangeFail(pPlayer)
	elseif (currentPhase == 4) then
		FsVillageDefense:doPhaseChangeFail(pPlayer)

		if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_06) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_06)) then
			FsCrafting4:sendTooLateSui(pPlayer)
		end
	end
end

function VillageJediManagerTownship.initPukingVillager(pNpc)
	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doPukingVillager", pNpc, "") -- 2-5 minute initial delay
end

function VillageJediManagerTownship:doPukingVillager(pNpc)
	if (pNpc == nil) then
		return
	end

	CreatureObject(pNpc):doAnimation("heavy_cough_vomit")

	spatialChat(pNpc, "@quest/force_sensitive/fs_sick:fs_response0" .. getRandomNumber(1,7))

	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doPukingVillager", pNpc, "") -- 2-5 minute delay
end

function VillageJediManagerTownship.initPanickedVillager(pNpc)
	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doPanickedVillager", pNpc, "") -- 2-5 minute initial delay
end

function VillageJediManagerTownship:doPanickedVillager(pNpc)
	if (pNpc == nil) then
		return
	end

	local rand = getRandomNumber(1,20)

	CreatureObject(pNpc):doAnimation("weeping")

	if (rand < 10) then
		spatialChat(pNpc, "@quest/force_sensitive/fs_panicked:fs_response0" .. rand)
	else
		spatialChat(pNpc, "@quest/force_sensitive/fs_panicked:fs_response" .. rand)
	end

	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doPanickedVillager", pNpc, "") -- 2-5 minute delay
end

function VillageJediManagerTownship.initWoundedVillager(pNpc)
	if (pNpc == nil) then
		return
	end

	CreatureObject(pNpc):setPosture(KNOCKEDDOWN)
	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doWoundedVillager", pNpc, "") -- 2-5 minute initial delay
end

function VillageJediManagerTownship:doWoundedVillager(pNpc)
	if (pNpc == nil) then
		return
	end

	local rand = getRandomNumber(1,10)

	if (rand < 10) then
		spatialChat(pNpc, "@quest/force_sensitive/fs_lamentations:fs_response0" .. rand)
	else
		spatialChat(pNpc, "@quest/force_sensitive/fs_lamentations:fs_response" .. rand)
	end

	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doWoundedVillager", pNpc, "") -- 2-5 minute delay
end

function VillageJediManagerTownship.initMedDroid(pNpc)
	if (pNpc ~= nil) then
		SceneObject(pNpc):setContainerComponent("MedDroidContainerComponent")
	end
end

function VillageJediManagerTownship.initVillageRepairer(pNpc)
	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doVillageRepairer", pNpc, "") -- 2-5 minute initial delay
end

function VillageJediManagerTownship:doVillageRepairer(pNpc)
	if (pNpc == nil) then
		return
	end

	local rand = getRandomNumber(1,10)

	if (rand < 5) then
		CreatureObject(pNpc):doAnimation("manipulate_medium")
	else
		CreatureObject(pNpc):doAnimation("manipulate_high")
	end

	rand = getRandomNumber(1,2)

	if (rand == 1) then
		rand = getRandomNumber(1,7)
		spatialChat(pNpc, "@quest/force_sensitive/fs_wall_repair:fs_response0" .. rand)
	end

	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doVillageRepairer", pNpc, "") -- 2-5 minute delay
end

MedDroidContainerComponent = {}

function MedDroidContainerComponent:transferObject(pContainer, pObj, slot)
	local pPlayer = VillageJediManagerTownship:getObjOwner(pObj)

	if (pPlayer == nil or pContainer == nil) then
		return 0
	end

	FsMedicPuzzle:cureSymptoms(pPlayer, pContainer, pObj)

	return 1
end

function MedDroidContainerComponent:canAddObject(pContainer, pObj, slot)
	local pPlayer = VillageJediManagerTownship:getObjOwner(pObj)

	if (pPlayer == nil or pContainer == nil) then
		return -1
	end

	if (SceneObject(pObj):getTemplateObjectPath() ~= "object/tangible/item/quest/force_sensitive/fs_medic_puzzle_heal_pack.iff") then
		return -1
	end

	if FsMedicPuzzle:hasAnySymptoms(pPlayer, pContainer) then
		return true
	else
		return -1
	end
end

function MedDroidContainerComponent:removeObject(pContainer, pObj, slot)
	return -1
end

function VillageJediManagerTownship:getObjOwner(pObj)
	if (pObj == nil) then
		return nil
	end

	local pPlayerInv = SceneObject(pObj):getParent()

	if (pPlayerInv == nil) then
		return nil
	end

	local parent = SceneObject(pPlayerInv):getParent()

	if (parent == nil) then
		return nil
	end

	if (SceneObject(parent):isCreatureObject()) then
		return parent
	end

	return nil
end

function VillageJediManagerTownship.initQtQcComponent(pNpc)
	SceneObject(pNpc):setContainerComponent("QtQcContainerComponent")
end

registerScreenPlay("VillageJediManagerTownship", true)

return VillageJediManagerTownship
