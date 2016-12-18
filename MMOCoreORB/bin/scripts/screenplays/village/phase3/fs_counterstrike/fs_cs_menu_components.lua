local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsCampRemoteMenuComponent = {}

function FsCampRemoteMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3, "@fs_quest_village:fs_cs_remote_use")
end

function FsCampRemoteMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil) then
		return 0
	end

	local csItem = LuaFsCsObject(pSceneObject)

	if (csItem:getDecayPercent() >= 100) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:p3_item_decayed")
		return 0
	end

	local campName = TangibleObject(pSceneObject):getLuaStringData("campName")
	local campNum = FsCounterStrike:getCampNumFromName(campName)

	if (campNum == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:fs_remote_fail")
		return 0
	end

	if (selectedID == 20) then
		local result = FsCsBaseControl:attemptPowerDownShield(pPlayer, campName)

		if (result) then
			SceneObject(pSceneObject):destroyObjectFromWorld()
			SceneObject(pSceneObject):destroyObjectFromDatabase()

			CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:remote_break")
		end
	end

	return 0
end

FsCampCommanderMenuComponent = {}

function FsCampCommanderMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	local commanderID = SceneObject(pSceneObject):getObjectID()
	local escorterID = readData(commanderID .. ":escorterID")
	local canBeRecaptured = readData(commanderID .. ":canBeRecaptured")

	if readData(commanderID .. ":deathSequence") ~= 0 then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	if (escorterID == 0) then
		menuResponse:addRadialMenuItem(20, 3, "@fs_quest_village:camp_commander_capture")
	end

	if (canBeRecaptured == 1) then
		local shieldKillerID = readData(commanderID .. ":shieldKillerID")

		if (shieldKillerID == SceneObject(pPlayer):getObjectID()) then
			menuResponse:addRadialMenuItem(21, 3, "@fs_quest_village:fs_cs_recapture")
		end
	end
end

function FsCampCommanderMenuComponent:handleObjectMenuSelect(pCommander, pPlayer, selectedID)
	if (pCommander == nil or pPlayer == nil) then
		return 0
	end

	local commanderID = SceneObject(pCommander):getObjectID()
	local escorterID = readData(commanderID .. ":escorterID")
	local playerID = SceneObject(pPlayer):getObjectID()
	local shieldKillerID = readData(commanderID .. ":shieldKillerID")
	local pShieldKiller = getCreatureObject(shieldKillerID)

	if (selectedID == 20) then
		if (escorterID ~= 0) then
			return 0
		end

		if (pShieldKiller == nil) then
			CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:camp_commander_no_auth")
			return 0
		end

		if (shieldKillerID ~= playerID and (not CreatureObject(pShieldKiller):isGroupedWith(pPlayer) or not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_INTRO))) then
			CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:camp_commander_no_auth")
			return 0
		end

		writeData(commanderID .. ":capturedBy", SceneObject(pPlayer):getObjectID())

		FsCsCommander:captureCommander(pCommander, pPlayer)

		if (shieldKillerID ~= playerID) then
			FsCsCommander:captureCommander(pCommander, pShieldKiller)
		end

		writeData(commanderID .. ":rescueSpawnPending", 1)
		createEvent(getRandomNumber(FsCsCommander.rescueSpawnTimer[1], FsCsCommander.rescueSpawnTimer[2]) * 1000, "FsCsCommander", "spawnRescuers", pCommander, "")

		spatialChat(pCommander, "@fs_quest_village:commander_death_notify")
	elseif (selectedID == 21) then
		if (readData(commanderID .. ":currentlyFree") == 0 or readData(commanderID .. ":canBeRecaptured") == 0 or readData(commanderID .. ":deathSequence") ~= 0) then
			return 0
		end

		if (not SceneObject(pPlayer):isInRangeWithObject(pCommander, 15)) then
			CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:commander_too_far")
			return 0
		end

		if (shieldKillerID ~= playerID) then
			return 0
		end

		local locX = SceneObject(pCommander):getWorldPositionX()
		local locZ = SceneObject(pCommander):getWorldPositionZ()
		local locY = SceneObject(pCommander):getWorldPositionY()
		AiAgent(pCommander):stopWaiting()
		AiAgent(pCommander):setWait(0)
		AiAgent(pCommander):setNextPosition(locX, locZ, locY, 0)
		AiAgent(pCommander):setHomeLocation(locX, locZ, locY, 0)
		AiAgent(pCommander):executeBehavior()

		deleteData(commanderID .. ":canBeRecaptured")
		deleteData(commanderID .. ":currentlyFree")
		writeData(commanderID .. ":capturedBy", SceneObject(pPlayer):getObjectID())
		AiAgent(pCommander):setAiTemplate("follow")
		AiAgent(pCommander):setFollowState(3)

		FsCsCommander:captureCommander(pCommander, pShieldKiller)

		if (readData(commanderID .. ":rescueSpawnPending") == 0) then
			writeData(commanderID .. ":rescueSpawnPending", 1)
			createEvent(getRandomNumber(FsCsCommander.rescueSpawnTimer[1], FsCsCommander.rescueSpawnTimer[2]) * 1000, "FsCsCommander", "spawnRescuers", pCommander, "")
		end
	end

	return 0
end
