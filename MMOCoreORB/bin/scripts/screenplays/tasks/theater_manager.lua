local ObjectManager = require("managers.object.object_manager")

--[[
Theater Manager Steps:
1 - Accepted audition
2 - Started audition
3 - Completed audition
4 - Got audition reward
5 - Started first promotion
6 - Completed first promotion
7 - Spoke to theater manager and ready for first show
8 - Started first show
9 - Completed first show
10 - Got first show reward
11 - Started second promotion
12 - Completed second promotion
13 - Spoke to theater manager and ready for second show
14 - Started second show
15 - Completed second show
16 - Got second show reward
17 - Started third promotion
18 - Completed third promotion
19 - Spoke to theater manager and ready for final show
20 - Started final show
21 - Completed final show

Series legend:
0 - No current series
1 - Dance
2 - Music

]]

TheaterManagerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "TheaterManagerScreenPlay",

	enabled = 1,

	-- Promotions required for each promotional phase (strings match values 10, 20, 30)
	--requiredPromotions = { 10, 20, 30 },
	requiredPromotions = { 2, 2, 2 },

	-- Time in miliseconds between steps of audition
	auditionHeartbeat = 15 * 1000, -- 15 seconds

	-- Time before player can re-attempt a step, strings match 24 hours. This value is in seconds not miliseconds
	--failureTimerReset = 24 * 60 * 60, -- 24 hours
	failureTimerReset = 5 * 60, -- 5 minutes for testing

	songs = { "ballad", "ceremonial", "folk", "jazz", "rock", "starwars1", "starwars2", "starwars3", "virtuoso", "waltz" },
	dances = { "basic", "exotic", "footloose", "formal", "lyrical", "poplock", "popular", "rhythmic" },
	flourishes = 8
}

registerScreenPlay("TheaterManagerScreenPlay", true)

function TheaterManagerScreenPlay:start()
	self:spawnMobiles()
end

function TheaterManagerScreenPlay:spawnMobiles()
	if (isZoneEnabled("naboo")) then
		spawnMobile("naboo", "theater_manager",0,21.6399,2.12801,63.523,0,5475487)
	end
end

function TheaterManagerScreenPlay:getCurrentStep(pPlayer)
	local totalSteps = 21
	local curSeries = self:getCurrentSeries(pPlayer)

	local stateName
	if (curSeries == 0) then
		return 0
	elseif (curSeries == 1) then
		stateName = "theater_manager_dance_series"
	elseif (curSeries == 2) then
		stateName = "theater_manager_music_series"
	end

	for i = totalSteps, 1, -1 do
		local stateNum = 2 ^ (i - 1)

		if (CreatureObject(pPlayer):hasScreenPlayState(stateNum, stateName)) then
			return i
		end
	end

	return 0
end

function TheaterManagerScreenPlay:completeCurrentStep(pPlayer)
	local curStep = self:getCurrentStep(pPlayer)
	local curSeries = self:getCurrentSeries(pPlayer)

	local stateName
	if (curSeries == 0) then
		printf("Error in TheaterManagerScreenPlay:completeCurrentStep(), player is not currently participating in a Theater Manager series.")
		return
	elseif (curSeries == 1) then
		stateName = "theater_manager_dance_series"
	elseif (curSeries == 2) then
		stateName = "theater_manager_music_series"
	end
	local stateNum = 2 ^ (curStep)

	CreatureObject(pPlayer):setScreenPlayState(stateNum, stateName)
end

function TheaterManagerScreenPlay:getCurrentSeries(pPlayer)
	local curSeries = readScreenPlayData(pPlayer, "theaterManager", "currentSeries")

	if (curSeries == nil or curSeries == "") then
		curSeries = 0
	end

	return tonumber(curSeries)
end

function TheaterManagerScreenPlay:setCurrentSeries(pPlayer, val)
	writeScreenPlayData(pPlayer, "theaterManager", "currentSeries", val)
end

function TheaterManagerScreenPlay:setFailedStep(pPlayer)
	writeScreenPlayData(pPlayer, "theaterManager", "failTimer", os.time())
end

function TheaterManagerScreenPlay:isOnFailureTimer(pPlayer)
	local failTimer = readScreenPlayData(pPlayer, "theaterManager", "failTimer")

	if (failTimer == "" or failTimer == 0) then
		return false
	end

	return os.difftime(os.time(), tonumber(failTimer)) < self.failureTimerReset
end

function TheaterManagerScreenPlay:startAudition(pPlayer)
	local pTheater = self:getTheaterBuilding(pPlayer)

	if (pTheater == nil) then
		printf("Error in TheaterManagerScreenPlay:startAudition(), unable to get theater building object.\n")
		return
	end

	local pCell = BuildingObject(pTheater):getNamedCell("theater")

	if (pCell == nil) then
		printf("Error in TheaterManagerScreenPlay:startAudition(), unable to find main theater cell.\n")
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	writeData(theaterID .. ":theater_manager:show_running", 1)

	local playerID = SceneObject(pPlayer):getObjectID()
	writeData(theaterID .. ":theater_manager:show_performer", playerID)

	self:spawnJudges(pTheater)

	local areaX = SceneObject(pCell):getWorldPositionX() + 0
	local areaY = SceneObject(pCell):getWorldPositionY() + 51
	local areaZ = getTerrainHeight(pCell, areaX, areaY) + 2

	local pAuditionArea = spawnActiveArea(SceneObject(pTheater):getZoneName(), "object/active_area.iff", areaX, areaZ, areaY, 7, 0)

	if (pAuditionArea == nil) then
		printf("Error in TheaterManagerScreenPlay:startAudition, unable to create activeArea.\n")
		return
	end

	local areaID = SceneObject(pAuditionArea):getObjectID()
	writeData(playerID .. ":theater_manager:auditionAreaID", areaID)
	writeData(areaID .. ":ownerID", playerID)
	createObserver(ENTEREDAREA, "TheaterManagerScreenPlay", "notifyEnteredAuditionArea", pAuditionArea)
	createObserver(EXITEDAREA, "TheaterManagerScreenPlay", "notifyExitedAuditionArea", pAuditionArea)

	CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:audition_time_remaining")
	createEvent(30 * 1000, "TheaterManagerScreenPlay", "beginAudition", pPlayer)
end

function TheaterManagerScreenPlay:spawnJudges(pTheater)
	local theaterID = SceneObject(pTheater):getObjectID()

	local pCell = BuildingObject(pTheater):getNamedCell("theater")

	if (pCell == nil) then
		printf("Error in TheaterManagerScreenPlay:spawnJudges(), unable to find main theater cell.\n")
		return
	end

	local cellID = SceneObject(pCell):getObjectID()
	local planetName = SceneObject(pTheater):getZoneName()

	local pObject = spawnSceneObject(planetName, "object/tangible/furniture/modern/dining_table_modern_style_01.iff", 0.61, 2.13, 53.7, cellID, 0)
	if (pObject ~= nil) then
		writeData(theaterID .. ":theater_manager:judgeTableID", SceneObject(pObject):getObjectID())
	end

	pObject = spawnSceneObject(planetName, "object/tangible/furniture/modern/chair_modern_style_01.iff", -0.95, 2.13, 51.69, cellID, 0)
	if (pObject ~= nil) then
		writeData(theaterID .. ":theater_manager:judgeChair1ID", SceneObject(pObject):getObjectID())
	end

	pObject = spawnSceneObject(planetName, "object/tangible/furniture/modern/chair_modern_style_01.iff", 0.56, 2.13, 51.69, cellID, 0)
	if (pObject ~= nil) then
		writeData(theaterID .. ":theater_manager:judgeChair2ID", SceneObject(pObject):getObjectID())
	end

	pObject = spawnSceneObject(planetName, "object/tangible/furniture/modern/chair_modern_style_01.iff", 2.07, 2.13, 51.69, cellID, 0)
	if (pObject ~= nil) then
		writeData(theaterID .. ":theater_manager:judgeChair3ID", SceneObject(pObject):getObjectID())
	end

	local pJudge = spawnMobile(planetName, "judge", 0, -0.95, 2.13, 51.85, 0, cellID)
	if (pJudge ~= nil) then
		CreatureObject(pJudge):setState(STATESITTINGONCHAIR)
		writeData(theaterID .. ":theater_manager:judge1ID", CreatureObject(pJudge):getObjectID())
	end

	pJudge = spawnMobile(planetName, "judge", 0, 0.56, 2.13, 51.85, 0, cellID)
	if (pJudge ~= nil) then
		CreatureObject(pJudge):setState(STATESITTINGONCHAIR)
		writeData(theaterID .. ":theater_manager:judge2ID", CreatureObject(pJudge):getObjectID())
	end

	pJudge = spawnMobile(planetName, "judge", 0, 2.07, 2.13, 51.85, 0, cellID)
	if (pJudge ~= nil) then
		CreatureObject(pJudge):setState(STATESITTINGONCHAIR)
		writeData(theaterID .. ":theater_manager:judge3ID", CreatureObject(pJudge):getObjectID())
	end
end

function TheaterManagerScreenPlay:notifyEnteredAuditionArea(pActiveArea, pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end
	
	local playerID = SceneObject(pPlayer):getObjectID()
	local areaOwnerID = readData(SceneObject(pActiveArea):getObjectID() .. ":ownerID")

	if (playerID == areaOwnerID) then
		writeData(playerID .. ":theater_manager:inAuditionArea", 1)
	end

	return 0
end

function TheaterManagerScreenPlay:notifyExitedAuditionArea(pActiveArea, pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local areaOwnerID = readData(SceneObject(pActiveArea):getObjectID() .. ":ownerID")

	if (playerID == areaOwnerID) then
		writeData(playerID .. ":theater_manager:inAuditionArea", 0)

		if (readData(playerID .. ":theater_manager:auditionPhase") ~= 0) then
			self:failAudition(pPlayer, "fail_left_audition_area")
			return 1
		end
	end

	return 0
end

function TheaterManagerScreenPlay:beginAudition(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (readData(playerID .. ":theater_manager:inAuditionArea") == 0) then
		self:failAudition(pPlayer, "fail_not_in_audition_area")
	else
		CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:audition_begin")
		writeData(playerID .. ":theater_manager:auditionPhase", 1)
		createEvent(5 * 1000, "TheaterManagerScreenPlay", "runAuditionPhase", pPlayer)
	end
end

function TheaterManagerScreenPlay:runAuditionPhase(pPlayer)
	if (self:isOnFailureTimer(pPlayer)) then
		return
	end

	local pTheater = self:getTheaterBuilding(pPlayer)

	if (pTheater == nil) then
		printf("Error in TheaterManagerScreenPlay:runAuditionPhase(), unable to get theater building object.\n")
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local theaterID = SceneObject(pTheater):getObjectID()

	local phase = readData(playerID .. ":theater_manager:auditionPhase")
	local judgeID = readData(theaterID .. ":theater_manager:judge" .. getRandomNumber(3) .. "ID")
	local pJudge = getSceneObject(judgeID)

	if (pJudge == nil) then
		printf("Error finding judge in TheaterManagerScreenPlay:runAuditionPhase()\n")
		return
	end

	local auditionType = self:getCurrentSeries(pPlayer)
	local expectedPerformance, performanceName

	if (phase == 1 or phase == 4) then
		expectedPerformance = self:getExpectedPerformance(pPlayer, auditionType)

		if expectedPerformance == nil then
			printf("No valid performance found in TheaterManagerScreenPlay:runAuditionPhase()\n")
			return
		elseif auditionType == 1 then
			performanceName = self.dances[expectedPerformance]
		elseif auditionType == 2 then
			performanceName = self.songs[expectedPerformance]
		end

		writeData(playerID .. ":theater_manager:expectedPerformance", expectedPerformance)
		writeData(playerID .. ":theater_manager:performanceCompleted", 0)

		performanceName = performanceName:gsub("^%l", string.upper)
		createObserver(STARTENTERTAIN, "TheaterManagerScreenPlay", "notifyPerformanceObserver", pPlayer)
		createObserver(CHANGEENTERTAIN, "TheaterManagerScreenPlay", "notifyPerformanceObserver", pPlayer)
		createEvent(self.auditionHeartbeat, "TheaterManagerScreenPlay", "checkPerformanceStatus", pPlayer)

		local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:audition_step_" .. phase)
		messageString:setTO(performanceName)
		spatialChat(pJudge, messageString:_getObject())

	elseif (phase == 2 or phase == 3 or phase == 5 or phase == 6) then
		expectedPerformance = self:getExpectedPerformance(pPlayer, 3)
		writeData(playerID .. ":theater_manager:expectedPerformance", expectedPerformance)
		writeData(playerID .. ":theater_manager:performanceCompleted", 0)

		createObserver(FLOURISH, "TheaterManagerScreenPlay", "notifyFlourishObserver", pPlayer)
		createEvent(self.auditionHeartbeat, "TheaterManagerScreenPlay", "checkPerformanceStatus", pPlayer)

		local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:audition_step_" .. phase)
		messageString:setDI(expectedPerformance)
		spatialChat(pJudge, messageString:_getObject())

	elseif (phase == 7) then
		self:completeAudition(pPlayer)
	end
end

function TheaterManagerScreenPlay:getExpectedPerformance(pPlayer, type)
	if (not self:isValidEntertainer(pPlayer)) then
		return nil
	end

	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local performance, currentPerformance
		if (player:isDancing() or player:isPlayingMusic()) then
			currentPerformance = player:getPerformanceName()
		end
		if (type == 1) then
			while performance == nil do
				local performanceName = self.dances[getRandomNumber(table.getn(self.dances))]

				if (playerObject:hasAbility("startDance+" .. performanceName) and (currentPerformance == nil or performanceName ~= currentPerformance)) then
					performance = self:getPerformanceKey(1, performanceName)
				end
			end
			return performance
		elseif (type == 2) then
			while performance == nil do
				local performanceName = self.songs[getRandomNumber(table.getn(self.songs))]
				if (playerObject:hasAbility("startMusic+" .. performanceName) and (currentPerformance == nil or performanceName ~= currentPerformance)) then
					performance = self:getPerformanceKey(2, performanceName)
				end
			end
			return performance
		elseif (type == 3) then
			return getRandomNumber(self.flourishes)
		else
			printf("Invalid audition type in TheaterManagerScreenPlay:getExpectedPerformance() \n")
			return 0
		end
	end)
end

function TheaterManagerScreenPlay:isValidEntertainer(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):hasSkill("social_entertainer_music_02") or CreatureObject(pPlayer):hasSkill("social_entertainer_dance_02")
end

function TheaterManagerScreenPlay:isExpectedPerformance(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local auditionType = self:getCurrentSeries(pPlayer)
	local expectedPerformance = readData(playerID .. ":theater_manager:expectedPerformance")

	local expectedPerformanceName
	if (auditionType == 1) then
		expectedPerformanceName = self.dances[expectedPerformance]
	elseif (auditionType == 2) then
		expectedPerformanceName = self.songs[expectedPerformance]
	end

	if (auditionType == 1 and CreatureObject(pPlayer):isDancing() and CreatureObject(pPlayer):getPerformanceName() == expectedPerformanceName) then
		return true
	elseif (auditionType == 2 and CreatureObject(pPlayer):isPlayingMusic() and CreatureObject(pPlayer):getPerformanceName() == expectedPerformanceName) then
		return true
	else
		return false
	end
end

function TheaterManagerScreenPlay:failAudition(pPlayer, reason)
	self:auditionCleanup(pPlayer)
	createEvent(2 * 1000, "TheaterManagerScreenPlay", "auditionJudgeCleanup", pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:" .. reason)
	self:setFailedStep(pPlayer)
end

function TheaterManagerScreenPlay:auditionCleanup(pPlayer)
	local pTheater = self:getTheaterBuilding(pPlayer)

	if (pTheater == nil) then
		printf("Error in TheaterManagerScreenPlay:auditionCleanup(), unable to get theater building object.\n")
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()
	local playerID = SceneObject(pPlayer):getObjectID()

	dropObserver(STARTENTERTAIN, pPlayer)
	dropObserver(CHANGEENTERTAIN, pPlayer)
	dropObserver(FLOURISH, pPlayer)
	
	writeData(theaterID .. ":theater_manager:show_running", 0)

	local auditionAreaID = readData(playerID .. ":theater_manager:auditionAreaID")
	local pAuditionArea = getSceneObject(auditionAreaID)

	if (pAuditionArea ~= nil) then
		SceneObject(pAuditionArea):destroyObjectFromWorld()
	end
	
	deleteData(playerID .. ":theater_manager:auditionAreaID")

	deleteData(playerID .. ":theater_manager:auditionPhase")
	deleteData(playerID .. ":theater_manager:expectedPerformance")
	deleteData(playerID .. ":theater_manager:performanceCompleted")
	deleteData(playerID .. ":theater_manager:inAuditionArea")

end

function TheaterManagerScreenPlay:auditionJudgeCleanup(pPlayer)
	local pTheater = self:getTheaterBuilding(pPlayer)

	if (pTheater == nil) then
		printf("Error in TheaterManagerScreenPlay:auditionJudgeCleanup(), unable to get theater building object.\n")
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	for i = 1, 3, 1 do
		local judgeID = readData(theaterID .. ":theater_manager:judge" .. i .. "ID")
		local pJudge = getSceneObject(judgeID)
		if (pJudge ~= nil) then
			SceneObject(pJudge):destroyObjectFromWorld()
		end
		deleteData(theaterID .. ":theater_manager:judge" .. i .. "ID")
	end

	local judgeTableID = readData(theaterID .. ":theater_manager:judgeTableID")
	local pObject = getSceneObject(judgeTableID)

	if (pObject ~= nil) then
		SceneObject(pObject):destroyObjectFromWorld()
	end
	deleteData(theaterID .. ":theater_manager:judgeTableID")

	for i = 1, 3, 1 do
		local chairID = readData(theaterID .. ":theater_manager:judgeChair" .. i .. "ID")
		local pChair = getSceneObject(chairID)
		if (pChair ~= nil) then
			SceneObject(pChair):destroyObjectFromWorld()
		end
		deleteData(theaterID .. ":theater_manager:judgeChair" .. i .. "ID")
	end
end

function TheaterManagerScreenPlay:getPerformanceKey(type, performance)
	if (type == 1) then
		for k,v in pairs(self.dances) do
			if v == performance then
				return k
			end
		end
	elseif (type == 2) then
		for k,v in pairs(self.songs) do
			if v == performance then
				return k
			end
		end
	end
end

function TheaterManagerScreenPlay:checkPerformanceStatus(pPlayer)
	if (self:isOnFailureTimer(pPlayer)) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local performanceCompleted = readData(playerID .. ":theater_manager:performanceCompleted")

	if (performanceCompleted == 0) then
		self:failAudition(pPlayer, "fail_audition")
		return 0
	end

	local phase = readData(playerID .. ":theater_manager:auditionPhase")
	writeData(playerID .. ":theater_manager:auditionPhase", phase + 1)

	self:runAuditionPhase(pPlayer)
end

function TheaterManagerScreenPlay:notifyPerformanceObserver(pPlayer, pPlayer2)
	if pPlayer == nil then
		return 1
	end

	if (self:isExpectedPerformance(pPlayer)) then
		writeData(SceneObject(pPlayer):getObjectID() .. ":theater_manager:performanceCompleted", 1)
		dropObserver(STARTENTERTAIN, pPlayer)
		dropObserver(CHANGEENTERTAIN, pPlayer)
		return 1
	end

	return 0
end

function TheaterManagerScreenPlay:notifyFlourishObserver(pPlayer, pPlayer2, flourishID)
	if pPlayer == nil then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (flourishID == readData(playerID .. ":theater_manager:expectedPerformance")) then
		writeData(playerID .. ":theater_manager:performanceCompleted", 1)
		return 1
	end

	return 0
end

function TheaterManagerScreenPlay:completeAudition(pPlayer)
	self:completeCurrentStep(pPlayer)
	self:auditionCleanup(pPlayer)
	createEvent(5 * 1000, "TheaterManagerScreenPlay", "auditionJudgeCleanup", pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:succeed_audition")
end

function TheaterManagerScreenPlay:doPayout(pPlayer, amount)
	CreatureObject(pPlayer):addCashCredits(amount, true)
	local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:payout")
	messageString:setDI(amount)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

function TheaterManagerScreenPlay:getTheaterBuilding(pPlayer)
	if (pPlayer == nil) then
		return nil
	end

	local pCell = SceneObject(pPlayer):getParent()

	if (pCell == nil) then
		return nil
	end

	return SceneObject(pCell):getParent()
end

function TheaterManagerScreenPlay:startPromotion(pPlayer)
	dropObserver(WASWATCHED, pPlayer)
	dropObserver(WASLISTENEDTO, pPlayer)

	local series = self:getCurrentSeries(pPlayer)

	if (series == 0) then
		return
	end

	local currentStep = self:getCurrentStep(pPlayer)
	local requiredPromotions = self:getRequiredPromotions(currentStep)

	self:setCurrentPromotions(pPlayer, 0)

	local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:popularity_starting_message")
	messageString:setDI(requiredPromotions)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

	if (series == 2) then
		createObserver(WASLISTENEDTO, "TheaterManagerScreenPlay", "notifyPromotionObserver", pPlayer, 1)
	elseif (series == 1) then
		createObserver(WASWATCHED, "TheaterManagerScreenPlay", "notifyPromotionObserver", pPlayer, 1)
	end
end

function TheaterManagerScreenPlay:getRequiredPromotions(step)
	if (step == 5) then
		return self.requiredPromotions[1]
	elseif (step == 11) then
		return self.requiredPromotions[2]
	elseif (step == 17) then
		return self.requiredPromotions[3]
	end
end

function TheaterManagerScreenPlay:setCurrentPromotions(pPlayer, promotions)
	writeScreenPlayData(pPlayer, "theaterManager", "currentPromotions", promotions)
end

function TheaterManagerScreenPlay:eraseCurrentPromotions(pPlayer)
	deleteScreenPlayData(pPlayer, "theaterManager", "currentPromotions")
end

function TheaterManagerScreenPlay:getCurrentPromotions(pPlayer)
	local curPromos = readScreenPlayData(pPlayer, "theaterManager", "currentPromotions")

	if (curPromos == nil or curPromos == "") then
		curPromos = 0
	end

	return tonumber(curPromos)
end

function TheaterManagerScreenPlay:notifyPromotionObserver(pPlayer, pEntertained)
	if (pPlayer == nil or pEntertained == nil) then
		return 1
	end

	local currentStep = self:getCurrentStep(pPlayer)
	local requiredPromotions = self:getRequiredPromotions(currentStep)
	local currentPromotions = self:getCurrentPromotions(pPlayer)

	local entertainedID = SceneObject(pEntertained):getObjectID()

	if (currentPromotions == requiredPromotions) then
		return 1
	elseif (self:isInPlayersEntertainedList(pPlayer, entertainedID)) then
		return 0
	end

	currentPromotions = currentPromotions + 1
	self:setCurrentPromotions(pPlayer, currentPromotions)

	self:writeToPlayersEntertainedList(pPlayer, entertainedID)
	
	local popStep = 1
	
	if (currentStep == 11) then
		popStep = 2
	elseif (currentStep == 17) then
		popStep = 3
	end

	if (requiredPromotions == currentPromotions) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:popularity_" .. popStep .. "_complete")
	else
		local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:popularity_" .. popStep .. "_remaining")
		messageString:setDI(requiredPromotions - currentPromotions)
		messageString:setTO(CreatureObject(pEntertained):getFirstName())
		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	end

	return 0
end


function TheaterManagerScreenPlay:getPlayersEntertainedList(pPlayer)
	local list = readScreenPlayData(pPlayer, "theaterManager", "currentPromotionList")

	if (list == nil or list == "") then
		return nil
	end

	return self:splitString(list, ",")
end

function TheaterManagerScreenPlay:writeToPlayersEntertainedList(pPlayer, playerID)
	local list = readScreenPlayData(pPlayer, "theaterManager", "currentPromotionList")

	if (list == nil or list == "") then
		list = playerID
	else
		list = list .. "," .. playerID
	end

	writeScreenPlayData(pPlayer, "theaterManager", "currentPromotionList", list)
end

function TheaterManagerScreenPlay:resetPlayersEntertainedList(pPlayer)
	deleteScreenPlayData(pPlayer, "theaterManager", "currentPromotionList")
end

function TheaterManagerScreenPlay:isInPlayersEntertainedList(pPlayer, playerID)
	local playersEntertained = self:getPlayersEntertainedList(pPlayer)

	if (playersEntertained == nil) then
		return false
	end

	for i = 1, table.getn(playersEntertained), 1 do
		if tonumber(playersEntertained[i]) == playerID then
			return true
		end
	end

	return false
end

function TheaterManagerScreenPlay:hasPromotedEnough(pPlayer)
	local currentStep = self:getCurrentStep(pPlayer)
	local requiredPromotions = self:getRequiredPromotions(currentStep)
	local currentPromotions = self:getCurrentPromotions(pPlayer)

	return requiredPromotions == currentPromotions
end

function TheaterManagerScreenPlay:completePromotionPhase(pPlayer)
	self:resetPlayersEntertainedList(pPlayer)
	self:eraseCurrentPromotions(pPlayer)
	self:completeCurrentStep(pPlayer)
end

function TheaterManagerScreenPlay:splitString(string, delimiter)
	local outResults = { }
	local start = 1
	local splitStart, splitEnd = string.find( string, delimiter, start )
	while splitStart do
		table.insert( outResults, string.sub( string, start, splitStart-1 ) )
		start = splitEnd + 1
		splitStart, splitEnd = string.find( string, delimiter, start )
	end
	table.insert( outResults, string.sub( string, start ) )
	return outResults
end