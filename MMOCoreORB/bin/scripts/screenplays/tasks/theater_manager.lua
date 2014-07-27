local ObjectManager = require("managers.object.object_manager")

TheaterManagerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "TheaterManagerScreenPlay"
}

local AUDITION_COUNTDOWN_TIME = 30 * 1000 -- 30 seconds
local PROMOTION_ONE_REQUIRED = 1
local PROMOTION_TWO_REQUIRED = 2
local PROMOTION_THREE_REQUIRED = 3

local AUDITION_SONGS = { "ballad", "ceremonial", "folk", "jazz", "rock", "starwars1", "starwars2", "starwars3", "virtuoso", "waltz" }
local AUDITION_DANCES = { "basic", "exotic", "footloose", "formal", "lyrical", "poplock", "popular", "rhythmic" }
local AUDITION_FLOURISHES = 8

function TheaterManagerScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
	end
end

function TheaterManagerScreenPlay:spawnMobiles()
	spawnMobile("naboo", "theater_manager",0,21.6399,2.12801,63.523,0,5475487)
end

function TheaterManagerScreenPlay:spawnAudition(pPlayer)
	writeData("theater_manager:show_running", 1)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local pJudge1 = spawnMobile("naboo", "judge", 0, 3.0, 0.7, 42.7, 0, 5475485)
		ObjectManager.withCreatureObject(pJudge1, function(judge)
			judge:setState(STATESITTINGONCHAIR)
			writeData(player:getObjectID() .. ":judge1ID", judge:getObjectID())
		end)
		local pJudge2 = spawnMobile("naboo", "judge", 0, -1.0, 0.7, 42.7, 0, 5475485)
		ObjectManager.withCreatureObject(pJudge2, function(judge)
			judge:setState(STATESITTINGONCHAIR)
			writeData(player:getObjectID() .. ":judge2ID", judge:getObjectID())
		end)
		local pJudge3 = spawnMobile("naboo", "judge", 0, -5.0, 0.7, 42.7, 0, 5475485)
		ObjectManager.withCreatureObject(pJudge3, function(judge)
			judge:setState(STATESITTINGONCHAIR)
			writeData(player:getObjectID() .. ":judge3ID", judge:getObjectID())
		end)
		local pAuditionArea = spawnSceneObject("naboo", "object/active_area.iff", -5791.9, 8.1, 4235.9, 0, 0, 0, 0, 0)
		ObjectManager.withActiveArea(pAuditionArea, function(auditionArea)
			auditionArea:setRadius(7)
			writeData(player:getObjectID() .. ":auditionAreaID", auditionArea:getObjectID())
			writeData(auditionArea:getObjectID() .. ":ownerID", player:getObjectID())
			createObserver(ENTEREDAREA, "TheaterManagerScreenPlay", "notifyEnteredAuditionArea", pAuditionArea)
			createObserver(EXITEDAREA, "TheaterManagerScreenPlay", "notifyExitedAuditionArea", pAuditionArea)
		end)

		player:sendSystemMessage("@quest/crowd_pleaser/system_messages:audition_time_remaining")
		createEvent(AUDITION_COUNTDOWN_TIME, "TheaterManagerScreenPlay", "startAudition", pPlayer)
	end)
end

function TheaterManagerScreenPlay:notifyEnteredAuditionArea(pActiveArea, pPlayer)
	ObjectManager.withActiveArea(pActiveArea, function(activeArea)
		ObjectManager.withCreatureObject(pPlayer, function(player)
			local playerID = player:getObjectID()
			local areaOwnerID = readData(activeArea:getObjectID() .. ":ownerID")
			if (playerID == areaOwnerID) then
				writeData(player:getObjectID() .. ":inAuditionArea", 1)
			end
		end)
	end)
end

function TheaterManagerScreenPlay:notifyExitedAuditionArea(pActiveArea, pPlayer)
	ObjectManager.withActiveArea(pActiveArea, function(activeArea)
		ObjectManager.withCreatureObject(pPlayer, function(player)
			local playerID = player:getObjectID()
			local areaOwnerID = readData(activeArea:getObjectID() .. ":ownerID")
			if (playerID == areaOwnerID) then
				writeData(player:getObjectID() .. ":inAuditionArea", 0)
				if (readData(player:getObjectID() .. ":auditionPhase") ~= nil and readData(player:getObjectID() .. ":auditionPhase") ~= 0) then
					self:failAudition(pPlayer, "fail_left_audition_area")
				end
			end
		end)
	end)
end

function TheaterManagerScreenPlay:startAudition(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local inAuditionArea = readData(player:getObjectID() .. ":inAuditionArea")
		if (inAuditionArea == 0) then
			self:failAudition(pPlayer, "fail_not_in_audition_area")
		else
			player:sendSystemMessage("@quest/crowd_pleaser/system_messages:audition_begin")
			writeData(player:getObjectID() .. ":auditionPhase", 1)
			createEvent(math.random(8,12) * 1000, "TheaterManagerScreenPlay", "runAuditionPhase", pPlayer)
		end
	end)
end

function TheaterManagerScreenPlay:runAuditionPhase(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local phase = readData(player:getObjectID() .. ":auditionPhase")
		local judgeID = readData(player:getObjectID() .. ":judge" .. math.random(3) .. "ID")
		local pJudge = getSceneObject(judgeID)
		local auditionType = readData(player:getObjectID() .. ":auditionType")
		local expectedPerformance, performanceName

		if (phase == 1 or phase == 4) then
			expectedPerformance = self:getExpectedPerformance(pPlayer, auditionType)

			if expectedPerformance == nil then
				printf("No valid performance found in TheaterManagerScreenPlay:runAuditionPhase()\n")
				return 0
			elseif auditionType == 1 then
				performanceName = AUDITION_DANCES[expectedPerformance]
			elseif auditionType == 2 then
				performanceName = AUDITION_SONGS[expectedPerformance]
			end

			writeData(player:getObjectID() .. ":expectedPerformance", expectedPerformance)
			writeData(player:getObjectID() .. ":performanceCompleted", 0)

			performanceName = performanceName:gsub("^%l", string.upper)
			createObserver(STARTENTERTAIN, "TheaterManagerScreenPlay", "notifyPerformanceObserver", pPlayer)
			createObserver(CHANGEENTERTAIN, "TheaterManagerScreenPlay", "notifyPerformanceObserver", pPlayer)
			createEvent(math.random(8,15) * 1000, "TheaterManagerScreenPlay", "checkPerformanceStatus", pPlayer)
			if (phase == 1) then
				spatialChat(pJudge, "Hello and welcome. Begin by performing " .. performanceName .. " for us, please.")
			else
				spatialChat(pJudge, "Excellent. Now change the style and perform " .. performanceName .. ", please.")
			end
		elseif (phase == 2 or phase == 3 or phase == 5 or phase == 6) then
			expectedPerformance = self:getExpectedPerformance(pPlayer, "flourish")

			writeData(player:getObjectID() .. ":expectedPerformance", expectedPerformance)
			writeData(player:getObjectID() .. ":performanceCompleted", 0)

			createObserver(FLOURISH, "TheaterManagerScreenPlay", "notifyFlourishObserver", pPlayer)
			createEvent(math.random(8,15) * 1000, "TheaterManagerScreenPlay", "checkPerformanceStatus", pPlayer)
			if (phase == 2) then
				spatialChat(pJudge, "Very good. Now perform flourish " .. expectedPerformance .. " for us, please.")
			elseif (phase == 3) then
				spatialChat(pJudge, "Good. Perform flourish " .. expectedPerformance .. " now, please.")
			elseif (phase == 5) then
				spatialChat(pJudge, "Good, good. And perform flourish " .. expectedPerformance .. ", please.")
			elseif (phase == 6) then
				spatialChat(pJudge, "Yes, good. And now flourish " .. expectedPerformance .. ", please.")
			end
		elseif (phase == 7) then
			self:completeAudition(pPlayer)
		end
	end)
end

function TheaterManagerScreenPlay:checkPerformanceStatus(pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local performanceCompleted = readData(player:getObjectID() .. ":performanceCompleted")

		if (performanceCompleted == 0) then
			self:failAudition(pPlayer, "fail_audition")
			return 0
		end

		local phase = readData(player:getObjectID() .. ":auditionPhase")
		writeData(player:getObjectID() .. ":auditionPhase", phase + 1)
		self:runAuditionPhase(pPlayer)
	end)
end

function TheaterManagerScreenPlay:notifyPerformanceObserver(pPlayer, pPlayer2)
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local auditionType = readData(player:getObjectID() .. ":auditionType")
		local expectedPerformance = readData(player:getObjectID() .. ":expectedPerformance")
		if (self:isExpectedPerformance(pPlayer, expectedPerformance, auditionType) == true) then
			writeData(player:getObjectID() .. ":performanceCompleted", 1)
			dropObserver(STARTENTERTAIN, pPlayer)
			dropObserver(CHANGEENTERTAIN, pPlayer)
		else
			self:failAudition(pPlayer, "fail_audition")
		end
	end)
end

function TheaterManagerScreenPlay:notifyFlourishObserver(pPlayer, pPlayer2, flourishID)
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local auditionType = readData(player:getObjectID() .. ":auditionType")
		local expectedPerformance = readData(player:getObjectID() .. ":expectedPerformance")
		if (flourishID == expectedPerformance) then
			writeData(player:getObjectID() .. ":performanceCompleted", 1)
			dropObserver(FLOURISH, pPlayer)
		else
			self:failAudition(pPlayer, "fail_audition")
		end
	end)
end

function TheaterManagerScreenPlay:isExpectedPerformance(pPlayer, performance, auditionType)
	local expectedPerformance
	if (auditionType == 1) then
		expectedPerformance = AUDITION_DANCES[performance]
	elseif (auditionType == 2) then
		expectedPerformance = AUDITION_SONGS[performance]
	end

	return ObjectManager.withCreatureObject(pPlayer, function(player)
		if (auditionType == 1 and player:isDancing() == true and player:getPerformanceName() == expectedPerformance) then
			return true
		elseif (auditionType == 2 and player:isPlayingMusic() == true and player:getPerformanceName() == expectedPerformance) then
			return true
		else
			return false
		end
	end)
end

function TheaterManagerScreenPlay:isValidEntertainer(pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		if player:hasSkill("social_entertainer_music_02") or player:hasSkill("social_entertainer_dance_02") then
			return true
		else
			return false
		end
	end)
end

function TheaterManagerScreenPlay:getExpectedPerformance(pPlayer, type)
	if (self:isValidEntertainer(pPlayer) == false) then
		return nil
	end
	
	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local performance, currentPerformance
		if (player:isDancing() == true or player:isPlayingMusic() == true) then
			currentPerformance = player:getPerformanceName()
		end
		if (type == 1) then
			while performance == nil do
				local performanceName = AUDITION_DANCES[math.random(table.getn(AUDITION_DANCES))]
				if (playerObject:hasAbility("startDance+" .. performanceName) == true and (currentPerformance == nil or performanceName ~= currentPerformance)) then
					performance = self:getPerformanceKey(1, performanceName)
				end
			end
			return performance
		elseif (type == 2) then
			while performance == nil do
				local performanceName = AUDITION_SONGS[math.random(table.getn(AUDITION_SONGS))]
				if (playerObject:hasAbility("startMusic+" .. performanceName) == true and (currentPerformance == nil or performanceName ~= currentPerformance)) then
					performance = self:getPerformanceKey(2, performanceName)
				end
			end
			return performance
		elseif (type == "flourish") then
			return math.random(AUDITION_FLOURISHES)
		else
			printf("Invalid audition type in TheaterManagerScreenPlay:getExpectedPerformance() \n")
			return 0
		end
	end)
end

function TheaterManagerScreenPlay:getPerformanceKey(type, performance)
	if (type == 1) then
		for k,v in pairs(AUDITION_DANCES) do
			if v == performance then
				return k
			end
		end
	elseif (type == 2) then
		for k,v in pairs(AUDITION_SONGS) do
			if v == performance then
				return k
			end
		end
	end
end

function TheaterManagerScreenPlay:completeAudition(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local auditionType = readData(player:getObjectID() .. ":auditionType")
		writeData(player:getObjectID() .. ":auditionSuccessful", 1)
		if (auditionType == 1) then
			player:setScreenPlayState(1, "theater_manager_dance")
		elseif (auditionType == 2) then
			player:setScreenPlayState(1, "theater_manager_music")
		end
		self:auditionCleanup(pPlayer)
		player:sendSystemMessage("@quest/crowd_pleaser/system_messages:succeed_audition")
	end)
end

function TheaterManagerScreenPlay:failAudition(pPlayer, reason)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		self:auditionCleanup(pPlayer)
		player:sendSystemMessage("@quest/crowd_pleaser/system_messages:" .. reason)
	end)
end

function TheaterManagerScreenPlay:auditionCleanup(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		dropObserver(STARTENTERTAIN, pPlayer)
		dropObserver(CHANGEENTERTAIN, pPlayer)
		dropObserver(FLOURISH, pPlayer)

		local auditionAreaID = readData(player:getObjectID() .. ":auditionAreaID")
		local pAuditionArea = getSceneObject(auditionAreaID)

		ObjectManager.withSceneObject(pAuditionArea, function(auditionArea)
			auditionArea:destroyObjectFromWorld()
		end)
		deleteData(player:getObjectID() .. ":auditionAreaID")

		for i = 1, 3, 1 do
			local judgeID = readData(player:getObjectID() .. ":judge" .. i .. "ID")
			local pJudge = getSceneObject(judgeID)
			ObjectManager.withSceneObject(pJudge, function(judge)
				judge:destroyObjectFromWorld()
			end)
			deleteData(player:getObjectID() .. ":judge" .. i .. "ID")
		end

		deleteData(player:getObjectID() .. ":auditionStarted")
		deleteData(player:getObjectID() .. ":auditionPhase")
		deleteData(player:getObjectID() .. ":expectedPerformance")
		deleteData(player:getObjectID() .. ":performanceCompleted")
		deleteData(player:getObjectID() .. ":inAuditionArea")

		writeData("theater_manager:show_running", 0)
	end)
end

registerScreenPlay("TheaterManagerScreenPlay", true)

theater_manager_conv_handler = TheaterManagerConvoHandler:new {
	themePark = TheaterManager
}