local ObjectManager = require("managers.object.object_manager")
includeFile("tasks/theaterManagerSeatingChart.lua")

--[[
Theater Manager Steps:
1 - Accepted audition
2 - Started audition
3 - Completed audition
4 - Got audition reward
5 - Started first promotion
6 - Talked to theater manager and completed first promotion
7 - Started first show
8 - Completed first show
9 - Got first show reward
10 - Started second promotion
11 - Talked to theater manager and completed second promotion
12 - Started second show
13 - Completed second show
14 - Got second show reward
15 - Started third promotion
16 - Talked to theater manager and completed third promotion
17 - Started final show
18 - Completed final show

Series legend:
0 - No current series
1 - Dance
2 - Music

]]

TheaterManagerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "TheaterManagerScreenPlay",

	enabled = 1,

	-- Number of promotions required for each promotional phase (strings match values 10, 20, 30)
	--requiredPromotions = { 10, 20, 30 },
	requiredPromotions = { 2, 2, 2 },

	-- Time in miliseconds between steps of audition
	auditionHeartbeat = 15 * 1000, -- 15 seconds

	-- Time in miliseconds between checks on a player's performance
	performanceHeartbeat = 15 * 1000, -- 15 seconds

	-- Time before player can re-attempt a step, strings match 24 hours. This value is in seconds not miliseconds
	--failureTimerReset = 24 * 60 * 60, -- 24 hours
	failureTimerReset = 5 * 60, -- 5 minutes for testing

	-- List of performances used by auditions and performances
	songs = { "ballad", "ceremonial", "folk", "jazz", "rock", "starwars1", "starwars2", "starwars3", "virtuoso", "waltz" },
	dances = { "basic", "exotic", "footloose", "formal", "lyrical", "poplock", "popular", "rhythmic" },
	flourishes = 8,

	-- Audiences interests, positive and negative. These randomized interests have a different default satisfaction
	-- rating as non interest performances.
	audienceInterests = {
		-- Each value represents how many of each are generated when the show starts
		-- [step] = { preferredPerformances, dislikedPerformances, preferredFlourishes, dislikedFlourishes }
		[7] = { 1, 0, 1, 1 },
		[12] = { 2, 0, 2, 0 },
		[17] = { 2, 1, 3, 1 }
	},

	-- Default rating values used in scoring performances
	performanceRatings = {
		default = 5, -- Starting value if a performance is not an audience interest
		minPositive = 2, -- Minimum rating a performance can reach if it's a positive interest
		minNegative = -10 -- Minimum rating a performance can reach if its a negative interest
	},

	-- Number of audience members spawned per performance, must be in multiples of 5
	performanceAudienceSize = { 10, 20, 30 },

	-- Length of player performance in seconds
	performanceLength = { 120, 210, 300 },

	-- Length of countdown prior to a player's performance.
	-- Note: The default values match the client string files
	performanceCountdownLength = { 120, 150, 180 },

	-- Score required to pass a performance
	performanceThresholds = { [7] = 100, [12] = 180, [17] = 244 }
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

-- This function gets the current step of the questline that the player is on
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

-- Completes the player's current step and moves them to the next step
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

-- Teaches the player the skills for completing a series
function TheaterManagerScreenPlay:teachSkills(pPlayer)
	local curSeries = self:getCurrentSeries(pPlayer)

	ObjectManager.withCreaturePlayerObject(pPlayer, function(player, playerObject)
		if (curSeries == 1) then
			playerObject:addAbility("startDance+theatrical")
			playerObject:addAbility("startDance+theatrical2")
		elseif (curSeries == 2) then
			playerObject:addAbility("startMusic+western")
		end
	end)
end

-- Completes the player's current series
function TheaterManagerScreenPlay:completeCurrentSeries(pPlayer)
	local curSeries = self:getCurrentSeries(pPlayer)

	if (curSeries == 0) then
		printf("Error in TheaterManagerScreenPlay:completeCurrentSeries(), player is not currently participating in a Theater Manager series.")
		return
	end

	CreatureObject(pPlayer):setScreenPlayState(curSeries, "theater_manager_series_completed")
	self:setCurrentSeries(pPlayer, 0)
end

-- Checks if the player's series is completed
function TheaterManagerScreenPlay:isSeriesComplete(pPlayer, type)
	return CreatureObject(pPlayer):hasScreenPlayState(type, "theater_manager_series_completed")
end

-- Get's the player's current series, dance or music
function TheaterManagerScreenPlay:getCurrentSeries(pPlayer)
	local curSeries = readScreenPlayData(pPlayer, "theaterManager", "currentSeries")

	if (curSeries == nil or curSeries == "") then
		curSeries = 0
	end

	return tonumber(curSeries)
end

-- Stores a value as the player's current series
function TheaterManagerScreenPlay:setCurrentSeries(pPlayer, val)
	writeScreenPlayData(pPlayer, "theaterManager", "currentSeries", val)
end

-- Set's the player's current step is failed by storing current OS time, used to check if a player
-- is able to repeat a step or must wait the remaining timer
function TheaterManagerScreenPlay:setFailedStep(pPlayer)
	writeScreenPlayData(pPlayer, "theaterManager", "failTimer", os.time())
end

-- Checks if a player is on a failure timer, used to determine if a failed player must wait before trying again
function TheaterManagerScreenPlay:isOnFailureTimer(pPlayer)
	local failTimer = readScreenPlayData(pPlayer, "theaterManager", "failTimer")

	if (failTimer == "" or failTimer == 0) then
		return false
	end

	return os.difftime(os.time(), tonumber(failTimer)) < self.failureTimerReset
end

-- Spawns an invisible control object that is used to control the various aspects of auditions and performances
function TheaterManagerScreenPlay:spawnControl(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	local pTheater = self:getTheaterBuilding(pPlayer)

	if (pTheater == nil) then
		printf("Error in TheaterManagerScreenPlay:spawnControl(), unable to get theater building object.\n")
		return nil
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	local pCell = BuildingObject(pTheater):getNamedCell("theater")

	if (pCell == nil) then
		printf("Error in TheaterManagerScreenPlay:spawnControl(), unable to find main theater cell.\n")
		return nil
	end

	local cellID = SceneObject(pCell):getObjectID()
	local planetName = SceneObject(pTheater):getZoneName()

	local areaX = SceneObject(pCell):getWorldPositionX() + 0
	local areaY = SceneObject(pCell):getWorldPositionY() + 51
	local areaZ = getTerrainHeight(pCell, areaX, areaY) + 2

	local pControl = spawnSceneObject(planetName, "object/tangible/theme_park/invisible_object.iff", areaX, areaZ, areaY, cellID, 0)

	if (pControl == nil) then
		return nil
	end

	local controlID = SceneObject(pControl):getObjectID()

	writeData(controlID .. ":theater_manager:theaterID", theaterID)
	writeData(controlID .. ":theater_manager:ownerID", playerID)
	writeData(playerID .. ":theater_manager:controlID", controlID)
	writeData(theaterID .. ":theater_manager:controlID", controlID)
	writeData(theaterID .. ":theater_manager:cellID", cellID)

	return pControl
end

-- Get's the current control object using either a theater object or player object
function TheaterManagerScreenPlay:getControl(pObject)
	if (pObject == nil) then
		return nil
	end

	local controlID = readData(SceneObject(pObject):getObjectID() .. ":theater_manager:controlID")

	return getSceneObject(controlID)
end

-- Cleans up the control object by destroying it and removing any stored data
function TheaterManagerScreenPlay:cleanupControl(pControl)
	if (pControl == nil) then
		return
	end

	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")
	local theaterID = readData(controlID .. ":theater_manager:theaterID")

	deleteData(controlID .. ":theater_manager:theaterID")
	deleteData(controlID .. ":theater_manager:ownerID")
	deleteData(playerID .. ":theater_manager:controlID")
	deleteData(theaterID .. ":theater_manager:controlID")
	deleteData(theaterID .. ":theater_manager:cellID")

	SceneObject(pControl):destroyObjectFromWorld()
end

-- Start's a player's audition
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
	local playerID = SceneObject(pPlayer):getObjectID()

	local pControl = self:spawnControl(pPlayer)

	if (pControl == nil) then
		printf("Error in TheaterManagerScreenPlay:startAudition(), unable to create control object.\n")
		return
	end

	local controlID = SceneObject(pControl):getObjectID()

	writeData(theaterID .. ":theater_manager:show_running", controlID)

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
	writeData(controlID .. ":theater_manager:auditionAreaID", areaID)
	writeData(areaID .. ":ownerID", playerID)
	createObserver(ENTEREDAREA, "TheaterManagerScreenPlay", "notifyEnteredAuditionArea", pAuditionArea)
	createObserver(EXITEDAREA, "TheaterManagerScreenPlay", "notifyExitedAuditionArea", pAuditionArea)

	CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:audition_time_remaining")
	createEvent(30 * 1000, "TheaterManagerScreenPlay", "beginAudition", pControl)
end

-- Spawns the judges for a player's audition
function TheaterManagerScreenPlay:spawnJudges(pTheater)
	local theaterID = SceneObject(pTheater):getObjectID()

	local pCell = BuildingObject(pTheater):getNamedCell("theater")

	if (pCell == nil) then
		printf("Error in TheaterManagerScreenPlay:spawnJudges(), unable to find main theater cell.\n")
		return
	end

	local cellID = SceneObject(pCell):getObjectID()
	local planetName = SceneObject(pTheater):getZoneName()

	local pControl = self:getControl(pTheater)

	if (pControl == nil) then
		printf("Error in TheaterManagerScreenPlay:spawnJudges(), unable to find control object.\n")
		return
	end

	local controlID = SceneObject(pControl):getObjectID()

	local pObject = spawnSceneObject(planetName, "object/tangible/furniture/modern/dining_table_modern_style_01.iff", 0.61, 2.13, 53.7, cellID, 0)
	if (pObject ~= nil) then
		writeData(controlID .. ":theater_manager:judgeTableID", SceneObject(pObject):getObjectID())
	end

	pObject = spawnSceneObject(planetName, "object/tangible/furniture/modern/chair_modern_style_01.iff", -0.95, 2.13, 51.69, cellID, 0)
	if (pObject ~= nil) then
		writeData(controlID .. ":theater_manager:judgeChair1ID", SceneObject(pObject):getObjectID())
	end

	pObject = spawnSceneObject(planetName, "object/tangible/furniture/modern/chair_modern_style_01.iff", 0.56, 2.13, 51.69, cellID, 0)
	if (pObject ~= nil) then
		writeData(controlID .. ":theater_manager:judgeChair2ID", SceneObject(pObject):getObjectID())
	end

	pObject = spawnSceneObject(planetName, "object/tangible/furniture/modern/chair_modern_style_01.iff", 2.07, 2.13, 51.69, cellID, 0)
	if (pObject ~= nil) then
		writeData(controlID .. ":theater_manager:judgeChair3ID", SceneObject(pObject):getObjectID())
	end

	local pJudge = spawnMobile(planetName, "judge", 0, -0.95, 2.13, 51.85, 0, cellID)
	if (pJudge ~= nil) then
		CreatureObject(pJudge):setState(STATESITTINGONCHAIR)
		writeData(controlID .. ":theater_manager:judge1ID", CreatureObject(pJudge):getObjectID())
	end

	pJudge = spawnMobile(planetName, "judge", 0, 0.56, 2.13, 51.85, 0, cellID)
	if (pJudge ~= nil) then
		CreatureObject(pJudge):setState(STATESITTINGONCHAIR)
		writeData(controlID .. ":theater_manager:judge2ID", CreatureObject(pJudge):getObjectID())
	end

	pJudge = spawnMobile(planetName, "judge", 0, 2.07, 2.13, 51.85, 0, cellID)
	if (pJudge ~= nil) then
		CreatureObject(pJudge):setState(STATESITTINGONCHAIR)
		writeData(controlID .. ":theater_manager:judge3ID", CreatureObject(pJudge):getObjectID())
	end
end

-- Observer function to monitor a player entering the audition area
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

-- Observer function to monitor a player exiting the audition area
function TheaterManagerScreenPlay:notifyExitedAuditionArea(pActiveArea, pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local areaOwnerID = readData(SceneObject(pActiveArea):getObjectID() .. ":ownerID")

	if (playerID == areaOwnerID) then
		writeData(playerID .. ":theater_manager:inAuditionArea", 0)

		if (readData(playerID .. ":theater_manager:auditionPhase") ~= 0) then
			local controlID = readData(playerID .. ":theater_manager:controlID")
			local pControl = getSceneObject(controlID)
			if (pControl ~= nil) then
				self:failAudition(pControl, "fail_left_audition_area")
			end
			return 1
		end
	end

	return 0
end

-- Start's the audition progress for a player through the control object
function TheaterManagerScreenPlay:beginAudition(pControl)
	local playerID = readData(SceneObject(pControl):getObjectID() .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		return
	end

	if (readData(playerID .. ":theater_manager:inAuditionArea") == 0) then
		self:failAudition(pControl, "fail_left_audition_area")
	else
		CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:audition_begin")
		writeData(playerID .. ":theater_manager:auditionPhase", 1)
		createEvent(5 * 1000, "TheaterManagerScreenPlay", "runAuditionPhase", pControl)
	end
end

-- Runs the next phase of a player's audition
function TheaterManagerScreenPlay:runAuditionPhase(pControl)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		return
	end

	if (self:isOnFailureTimer(pPlayer)) then
		return
	end

	local phase = readData(playerID .. ":theater_manager:auditionPhase")
	local judgeID = readData(controlID .. ":theater_manager:judge" .. getRandomNumber(3) .. "ID")
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
		createEvent(self.auditionHeartbeat, "TheaterManagerScreenPlay", "checkPerformanceStatus", pControl)

		local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:audition_step_" .. phase)
		messageString:setTO(performanceName)
		spatialChat(pJudge, messageString:_getObject())

	elseif (phase == 2 or phase == 3 or phase == 5 or phase == 6) then
		expectedPerformance = self:getExpectedPerformance(pPlayer, 3)
		writeData(playerID .. ":theater_manager:expectedPerformance", expectedPerformance)
		writeData(playerID .. ":theater_manager:performanceCompleted", 0)

		createObserver(FLOURISH, "TheaterManagerScreenPlay", "notifyFlourishObserver", pPlayer)
		createEvent(self.auditionHeartbeat, "TheaterManagerScreenPlay", "checkPerformanceStatus", pControl)

		local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:audition_step_" .. phase)
		messageString:setDI(expectedPerformance)
		spatialChat(pJudge, messageString:_getObject())

	elseif (phase == 7) then
		self:completeAudition(pControl)
	end
end

-- Picks a randomized performance for a player in their audition
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

-- Checks if the player is a valid entertainer capable of talking to the theater manager
function TheaterManagerScreenPlay:isValidEntertainer(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):hasSkill("social_entertainer_music_02") or CreatureObject(pPlayer):hasSkill("social_entertainer_dance_02")
end

-- Checks if the player's current performance is the expected performance
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

-- Fails a player's audition and sends the fail reason, setting the step to failure and cleaning up the audition
function TheaterManagerScreenPlay:failAudition(pControl, reason)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	self:auditionCleanup(pControl)
	createEvent(2 * 1000, "TheaterManagerScreenPlay", "auditionJudgeCleanup", pControl)

	if (pPlayer ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:" .. reason)
		self:setFailedStep(pPlayer)
	end
end

-- Cleans up the audition objects and data, drops the player's observers and removes the control object
function TheaterManagerScreenPlay:auditionCleanup(pControl)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")
	local theaterID = readData(controlID .. ":theater_manager:theaterID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer ~= nil) then
		dropObserver(STARTENTERTAIN, pPlayer)
		dropObserver(CHANGEENTERTAIN, pPlayer)
		dropObserver(FLOURISH, pPlayer)
	end

	deleteData(theaterID .. ":theater_manager:show_running")

	local auditionAreaID = readData(controlID .. ":theater_manager:auditionAreaID")
	local pAuditionArea = getSceneObject(auditionAreaID)

	if (pAuditionArea ~= nil) then
		SceneObject(pAuditionArea):destroyObjectFromWorld()
	end

	self:cleanupControl(pControl)

	deleteData(playerID .. ":theater_manager:auditionPhase")
	deleteData(playerID .. ":theater_manager:expectedPerformance")
	deleteData(playerID .. ":theater_manager:performanceCompleted")
	deleteData(playerID .. ":theater_manager:inAuditionArea")
end

-- Cleans up the audition's judges and scene objects, removing stored data
function TheaterManagerScreenPlay:auditionJudgeCleanup(pControl)
	local controlID = SceneObject(pControl):getObjectID()

	for i = 1, 3, 1 do
		local judgeID = readData(controlID .. ":theater_manager:judge" .. i .. "ID")
		local pJudge = getSceneObject(judgeID)
		if (pJudge ~= nil) then
			SceneObject(pJudge):destroyObjectFromWorld()
		end
		deleteData(controlID .. ":theater_manager:judge" .. i .. "ID")
	end

	local judgeTableID = readData(controlID .. ":theater_manager:judgeTableID")
	local pObject = getSceneObject(judgeTableID)

	if (pObject ~= nil) then
		SceneObject(pObject):destroyObjectFromWorld()
	end
	deleteData(controlID .. ":theater_manager:judgeTableID")

	for i = 1, 3, 1 do
		local chairID = readData(controlID .. ":theater_manager:judgeChair" .. i .. "ID")
		local pChair = getSceneObject(chairID)
		if (pChair ~= nil) then
			SceneObject(pChair):destroyObjectFromWorld()
		end
		deleteData(controlID .. ":theater_manager:judgeChair" .. i .. "ID")
	end
end

-- Gets the performance key using the performance table
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

-- Checks if the player has completed the performance needed for the current audition step
function TheaterManagerScreenPlay:checkPerformanceStatus(pControl)
	local playerID = readData(SceneObject(pControl):getObjectID() .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil or self:isOnFailureTimer(pPlayer)) then
		return
	end

	local performanceCompleted = readData(playerID .. ":theater_manager:performanceCompleted")

	if (performanceCompleted == 0) then
		self:failAudition(pControl, "fail_audition")
		return 0
	end

	local phase = readData(playerID .. ":theater_manager:auditionPhase")
	writeData(playerID .. ":theater_manager:auditionPhase", phase + 1)

	self:runAuditionPhase(pControl)
end

-- Observer function triggered by the player doing a performance, checks if its expected in audition
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

-- Observer function triggered by the player flourishing, checks if its expected in audition
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

-- Completes the player's audition, calls cleanup
function TheaterManagerScreenPlay:completeAudition(pControl)
	local playerID = readData(SceneObject(pControl):getObjectID() .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer ~= nil) then
		self:completeCurrentStep(pPlayer)
		CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:succeed_audition")
	end


	self:auditionCleanup(pControl)
	createEvent(5 * 1000, "TheaterManagerScreenPlay", "auditionJudgeCleanup", pControl)
end

-- Sends payout to player
function TheaterManagerScreenPlay:doPayout(pPlayer, amount)
	CreatureObject(pPlayer):addCashCredits(amount, true)
	local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:payout")
	messageString:setDI(amount)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

-- Get's the theater building the player is in
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

-- Get's the ID of the theater building
function TheaterManagerScreenPlay:getTheaterID(pPlayer)
	local pTheater = self:getTheaterBuilding(pPlayer)

	if (pTheater == nil) then
		return 0
	end

	return SceneObject(pTheater):getObjectID()
end

-- Start's the player's promotion step, creates observers and resets data
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

-- Gets the required promotions for the player's current step
function TheaterManagerScreenPlay:getRequiredPromotions(step)
	if (step == 5) then
		return self.requiredPromotions[1]
	elseif (step == 10) then
		return self.requiredPromotions[2]
	elseif (step == 15) then
		return self.requiredPromotions[3]
	end

	return 0
end

-- Sets the player's currently completed promotions
function TheaterManagerScreenPlay:setCurrentPromotions(pPlayer, promotions)
	writeScreenPlayData(pPlayer, "theaterManager", "currentPromotions", promotions)
end

-- Clears the player's completed promotions
function TheaterManagerScreenPlay:eraseCurrentPromotions(pPlayer)
	deleteScreenPlayData(pPlayer, "theaterManager", "currentPromotions")
end

-- Gets the count of the player's completed promotions
function TheaterManagerScreenPlay:getCurrentPromotions(pPlayer)
	local curPromos = readScreenPlayData(pPlayer, "theaterManager", "currentPromotions")

	if (curPromos == nil or curPromos == "") then
		curPromos = 0
	end

	return tonumber(curPromos)
end

-- Observer function triggered by someone watching the player perform
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

	if (currentStep == 10) then
		popStep = 2
	elseif (currentStep == 15) then
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

-- Gets a table of players that the performer has entertained
function TheaterManagerScreenPlay:getPlayersEntertainedList(pPlayer)
	local list = readScreenPlayData(pPlayer, "theaterManager", "currentPromotionList")

	if (list == nil or list == "") then
		return nil
	end

	return self:splitString(list, ",")
end

-- Writes a player to the performer's entertained list
function TheaterManagerScreenPlay:writeToPlayersEntertainedList(pPlayer, playerID)
	local list = readScreenPlayData(pPlayer, "theaterManager", "currentPromotionList")

	if (list == nil or list == "") then
		list = playerID
	else
		list = list .. "," .. playerID
	end

	writeScreenPlayData(pPlayer, "theaterManager", "currentPromotionList", list)
end

-- Clear's a performers entertained list
function TheaterManagerScreenPlay:resetPlayersEntertainedList(pPlayer)
	deleteScreenPlayData(pPlayer, "theaterManager", "currentPromotionList")
end

-- Checks if a player is already in the performer's entertained list
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

-- Checks if the performer has done enough promotion for their current step
function TheaterManagerScreenPlay:hasPromotedEnough(pPlayer)
	local currentStep = self:getCurrentStep(pPlayer)
	local requiredPromotions = self:getRequiredPromotions(currentStep)
	local currentPromotions = self:getCurrentPromotions(pPlayer)

	return requiredPromotions == currentPromotions
end

-- Completes the player's current promotion phase, clearing the entertained list and count
function TheaterManagerScreenPlay:completePromotionPhase(pPlayer)
	self:resetPlayersEntertainedList(pPlayer)
	self:eraseCurrentPromotions(pPlayer)
	self:completeCurrentStep(pPlayer)
end

-- Function that splits a comma delimited list into a table
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

-- Begins the process of a player's performance
function TheaterManagerScreenPlay:beginPerformance(pPlayer)
	local currentStep = self:getCurrentStep(pPlayer)

	local pControl = self:spawnControl(pPlayer)

	if (pControl == nil) then
		printf("Error in TheaterManagerScreenPlay:beginPerformance(), unable to create control object.\n")
		return
	end

	local controlID = SceneObject(pControl):getObjectID()

	local theaterID = readData(controlID .. ":theater_manager:theaterID")

	local pTheater = getSceneObject(theaterID)

	if (pTheater == nil) then
		printf("Error in TheaterManagerScreenPlay:beginPerformance(), unable to get theater building object.\n")
		return
	end

	local pCell = BuildingObject(pTheater):getNamedCell("theater")

	if (pCell == nil) then
		printf("Error in TheaterManagerScreenPlay:beginPerformance(), unable to find main theater cell.\n")
		return
	end

	writeData(theaterID .. ":theater_manager:show_running", controlID)

	self:determineAudienceInterests(pPlayer)

	local areaX = SceneObject(pCell):getWorldPositionX() + 0
	local areaY = SceneObject(pCell):getWorldPositionY() + 51
	local areaZ = getTerrainHeight(pCell, areaX, areaY) + 2

	local pPerformanceArea = spawnActiveArea(SceneObject(pCell):getZoneName(), "object/active_area.iff", areaX, areaZ, areaY, 10, 0)

	if (pPerformanceArea == nil) then
		printf("Error in TheaterManagerScreenPlay:beginPerformance, unable to create activeArea.\n")
		return
	end

	local areaID = SceneObject(pPerformanceArea):getObjectID()
	writeData(controlID .. ":theater_manager:performanceAreaID", areaID)
	writeData(areaID .. ":ownerID", SceneObject(pPlayer):getObjectID())

	createObserver(ENTEREDAREA, "TheaterManagerScreenPlay", "notifyEnteredPerformanceArea", pPerformanceArea)
	createObserver(EXITEDAREA, "TheaterManagerScreenPlay", "notifyExitedPerformanceArea", pPerformanceArea)


	createEvent(1 * 1000, "TheaterManagerScreenPlay", "spawnAudienceWave", pControl)
	createEvent(1 * 1000, "TheaterManagerScreenPlay", "handlePerformanceCountdown", pControl)
	createEvent(self:getPerformCountdownLength(currentStep) * 1000, "TheaterManagerScreenPlay", "handleStartPerformance", pControl)
	writeData(controlID .. ":theater_manager:countdownTime", self:getPerformCountdownLength(currentStep))
end

-- Handles the countdown before the player's performance begins
function TheaterManagerScreenPlay:handlePerformanceCountdown(pControl)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		return
	end

	local countdownLeft = readData(controlID .. ":theater_manager:countdownTime")

	local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:time_remaining")
	messageString:setDI(countdownLeft)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

	countdownLeft = countdownLeft - 30

	if (countdownLeft >= 30) then
		writeData(controlID .. ":theater_manager:countdownTime", countdownLeft)
		createEvent(30 * 1000, "TheaterManagerScreenPlay", "handlePerformanceCountdown", pControl)
	end
end

-- Spawns a wave of audience members
function TheaterManagerScreenPlay:spawnAudienceWave(pControl)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		return
	end

	local currentStep = self:getCurrentStep(pPlayer)
	local audienceSize = self:getPerformanceAudienceSize(currentStep)

	local pTheater = self:getTheaterBuilding(pPlayer)

	if (pTheater == nil) then
		printf("Error in TheaterManagerScreenPlay:spawnAudienceWave(), unable to get theater building object.\n")
		return
	end

	local pCell = BuildingObject(pTheater):getNamedCell("theater")

	if (pCell == nil) then
		printf("Error in TheaterManagerScreenPlay:spawnAudienceWave(), unable to find main theater cell.\n")
		return
	end

	local cellID = SceneObject(pCell):getObjectID()

	local planetName = SceneObject(pTheater):getZoneName()
	local audienceSpawned = readData(controlID .. ":theater_manager:audienceSpawned")

	if (audienceSpawned == nil) then
		audienceSpawned = 0
	end

	local seatTotal = table.getn(theaterManagerSeatingChart)
	for i = 1, 5, 1 do
		local isOccupied = true
		local randomSeat = 0

		while (isOccupied) do
			randomSeat = getRandomNumber(1, seatTotal)

			if (readData(controlID .. ":theater_manager:seat_" .. randomSeat) == 0) then
				isOccupied = false
			end
		end

		local data = theaterManagerSeatingChart[randomSeat]
		local pMember = spawnMobile(planetName, "audience_member", 0, data[1], data[2], data[3], data[4], cellID)

		if (pMember ~= nil) then
			CreatureObject(pMember):setState(STATESITTINGONCHAIR)
			writeData(controlID .. ":theater_manager:seat_" .. randomSeat, SceneObject(pMember):getObjectID())
			self:setupAudienceMember(pMember, pPlayer, pTheater)
		end
	end

	audienceSpawned = audienceSpawned + 5

	local leftToSpawn = audienceSize - audienceSpawned

	if (leftToSpawn > 0) then
		writeData(controlID .. ":theater_manager:audienceSpawned", audienceSpawned)
		createEvent(10 * 1000, "TheaterManagerScreenPlay", "spawnAudienceWave", pControl)
	else
		deleteData(controlID .. ":theater_manager:audienceSpawned")
	end
end

-- Gets the max size of a performance's audience using the current step
function TheaterManagerScreenPlay:getPerformanceAudienceSize(currentStep)
	if (currentStep == 7) then
		return self.performanceAudienceSize[1]
	elseif (currentStep == 12) then
		return self.performanceAudienceSize[2]
	elseif (currentStep == 17) then
		return self.performanceAudienceSize[3]
	end
end

-- Gets the length in seconds of the player's performance
function TheaterManagerScreenPlay:getPerformanceLength(currentStep)
	if (currentStep == 7) then
		return self.performanceLength[1]
	elseif (currentStep == 12) then
		return self.performanceLength[2]
	elseif (currentStep == 17) then
		return self.performanceLength[3]
	end
end

-- Gets the countdown length in seconds before a player's performance begins
function TheaterManagerScreenPlay:getPerformCountdownLength(currentStep)
	-- These values must be in multiples of 30
	if (currentStep == 7) then
		return self.performanceCountdownLength[1]
	elseif (currentStep == 12) then
		return self.performanceCountdownLength[2]
	elseif (currentStep == 17) then
		return self.performanceCountdownLength[3]
	end
end

-- Cleans up the performance audience after a performance ends
function TheaterManagerScreenPlay:cleanupAudience(pControl)
	local controlID = SceneObject(pControl):getObjectID()

	local seatTotal = table.getn(theaterManagerSeatingChart)

	for i = 1, seatTotal, 1 do
		local memberID = readData(controlID .. ":theater_manager:seat_" .. i)

		if (memberID ~= 0) then
			local pMember = getSceneObject(memberID)

			if (pMember ~= nil) then
				deleteStringData(SceneObject(pMember):getObjectID() .. ":theater_manager:convoResponse")
				deleteStringData(SceneObject(pMember):getObjectID() .. ":theater_manager:convoResponseTO")
				SceneObject(pMember):destroyObjectFromWorld()
			end

			deleteData(controlID .. ":theater_manager:seat_" .. i)
		end
	end
end

-- Sets up the convo and data for a spawned audience member
function TheaterManagerScreenPlay:setupAudienceMember(pNpc, pPlayer, pTheater)
	local controlID = readData(SceneObject(pPlayer):getObjectID() .. ":theater_manager:controlID")
	local randChance = getRandomNumber(1,100)
	local npcID = SceneObject(pNpc):getObjectID()

	if (randChance > 40) then
		writeStringData(npcID .. ":theater_manager:convoResponse", "neutral_" .. getRandomNumber(0, 40))
		return
	end

	local curSeries = self:getCurrentSeries(pPlayer)

	local suffix
	if (curSeries == 1) then
		suffix = "_d"
	else
		suffix = "_m"
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	if (randChance <= 5) then
		local interest = self:getRandomInterest(4, pPlayer, controlID)

		if (interest == nil) then
			writeStringData(npcID .. ":theater_manager:convoResponse", "neutral_" .. getRandomNumber(0, 40))
			return
		else
			local rand = getRandomNumber(1,5)
			writeStringData(npcID .. ":theater_manager:convoResponse", "negative_" .. rand .. "_f")
			writeStringData(npcID .. ":theater_manager:convoResponseTO", tostring(interest))
		end
	elseif (randChance > 5 and randChance <= 10) then
		local interest = self:getRandomInterest(2, pPlayer, controlID)

		if (interest == nil) then
			writeStringData(npcID .. ":theater_manager:convoResponse", "neutral_" .. getRandomNumber(0, 40))
			return
		else
			local rand = getRandomNumber(1,5)
			writeStringData(npcID .. ":theater_manager:convoResponse", "negative_" .. rand .. suffix)
			writeStringData(npcID .. ":theater_manager:convoResponseTO", interest)
		end
	elseif (randChance > 10 and randChance <= 25) then
		local interest = self:getRandomInterest(3, pPlayer, controlID)

		if (interest == nil) then
			writeStringData(npcID .. ":theater_manager:convoResponse", "neutral_" .. getRandomNumber(0, 40))
			return
		else
			local rand = getRandomNumber(1,5)
			writeStringData(npcID .. ":theater_manager:convoResponse", "positive_" .. rand .. "_f")
			writeStringData(npcID .. ":theater_manager:convoResponseTO", tostring(interest))
		end
	else
		local interest = self:getRandomInterest(1, pPlayer, controlID)

		if (interest == nil) then
			writeStringData(npcID .. ":theater_manager:convoResponse", "neutral_" .. getRandomNumber(0, 40))
			return
		else
			local rand = getRandomNumber(1,5)
			writeStringData(npcID .. ":theater_manager:convoResponse", "positive_" .. rand .. suffix)
			writeStringData(npcID .. ":theater_manager:convoResponseTO", interest)
		end
	end
end

-- Determines the audience interests for a player's performance
function TheaterManagerScreenPlay:determineAudienceInterests(pPlayer)
	local controlID = readData(SceneObject(pPlayer):getObjectID() .. ":theater_manager:controlID")

	local curSeries = self:getCurrentSeries(pPlayer)
	local curStep = self:getCurrentStep(pPlayer)

	local interestTable = self.audienceInterests[curStep]
	local performTable

	if (curSeries == 0) then
		printf("Error in TheaterManagerScreenPlay:determineAudienceInterests(), invalid series type.\n")
		return
	elseif (curSeries == 1)	then
		performTable = self.dances
	else
		performTable = self.songs
	end

	for i = 1, interestTable[1], 1 do
		writeData(controlID .. ":theater_manager:rating:" .. performTable[getRandomNumber(1, table.getn(performTable))], 10)
	end

	for i = 1, interestTable[2], 1 do
		writeData(controlID .. ":theater_manager:rating:" .. performTable[getRandomNumber(1, table.getn(performTable))], -2)
	end

	for i = 1, interestTable[3], 1 do
		writeData(controlID .. ":theater_manager:rating:flourish_" .. getRandomNumber(1, self.flourishes), 10)
	end

	for i = 1, interestTable[4], 1 do
		writeData(controlID .. ":theater_manager:rating:flourish_" .. getRandomNumber(1, self.flourishes), -2)
	end
end

-- Gets a random interest that was previously generated for the player
function TheaterManagerScreenPlay:getRandomInterest(type, pPlayer, controlID)
	local curSeries = self:getCurrentSeries(pPlayer)
	local performTable

	if (curSeries == 0) then
		printf("Error in TheaterManagerScreenPlay:getRandomInterest(), invalid series type.\n")
		return
	elseif (curSeries == 1)	then
		performTable = self.dances
	else
		performTable = self.songs
	end

	local choices = { }
	if (type == 1) then
		for i = 1, table.getn(performTable), 1 do
			if (readData(controlID .. ":theater_manager:rating:" .. performTable[i]) == 10) then
				table.insert(choices, performTable[i])
			end
		end
	elseif (type == 2) then
		for i = 1, table.getn(performTable), 1 do
			if (readData(controlID .. ":theater_manager:rating:" .. performTable[i]) == -2) then
				table.insert(choices, performTable[i])
			end
		end
	elseif (type == 3) then
		for i = 1, self.flourishes, 1 do
			if (readData(controlID .. ":theater_manager:rating:flourish_" .. i) == 10) then
				table.insert(choices, i)
			end
		end
	elseif (type == 4) then
		for i = 1, self.flourishes, 1 do
			if (readData(controlID .. ":theater_manager:rating:flourish_" .. i) == -2) then
				table.insert(choices, i)
			end
		end
	end

	if (table.getn(choices) == 0) then
		return nil
	else
		return choices[getRandomNumber(1,table.getn(choices))]
	end
end

-- Start's the actual performance for a player after the countdown ends
function TheaterManagerScreenPlay:handleStartPerformance(pControl)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		return
	end

	if (readData(playerID .. ":theater_manager:inPerformanceArea") ~= 1) then
		self:failPerformance(pControl, "fail_not_in_area")
		return
	end

	local pTheater = self:getTheaterBuilding(pPlayer)

	if (pTheater == nil) then
		printf("Error in TheaterManagerScreenPlay:handleStartPerformance(), unable to get theater building object.\n")
		return
	end

	local theaterID = SceneObject(pTheater):getObjectID()

	writeData(theaterID .. ":theater_manager:show_running", controlID)

	local curStep = self:getCurrentStep(pPlayer)

	if (not CreatureObject(pPlayer):isDancing() and not CreatureObject(pPlayer):isPlayingMusic()) then
		writeData(controlID .. ":theater_manager:not_performing", 1)
	end

	local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:performance_begin")
	messageString:setDI(self:getPerformanceLength(curStep))
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

	createObserver(FLOURISH, "TheaterManagerScreenPlay", "notifyPerformFlourishObserver", pPlayer)

	createEvent(self.performanceHeartbeat, "TheaterManagerScreenPlay", "doPerformanceHeartbeat", pControl)
	createEvent(self:getPerformanceLength(curStep) * 1000, "TheaterManagerScreenPlay", "endPerformance", pControl)
end

-- Observer function when player performs a flourish during a performance
function TheaterManagerScreenPlay:notifyPerformFlourishObserver(pPlayer, pPlayer2, flourishID)
	if pPlayer == nil then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local controlID = readData(playerID .. ":theater_manager:controlID")

	local rating = readData(controlID .. ":theater_manager:rating:flourish_" .. flourishID)

	if (rating == nil or rating == 0) then
		rating = self.performanceRatings.default
	end

	local satisfactionLevel = readData(controlID .. ":theater_manager:satisfactionLevel")

	if (satisfactionLevel == nil) then
		satisfactionLevel = 0
	end

	local perHeartbeat = readData(controlID .. ":theater_manager:performedFlourishes")

	if (perHeartbeat == nil) then
		perHeartbeat = 0
	end

	perHeartbeat = perHeartbeat + 1

	if (perHeartbeat > 2) then
		return 0
	end

	satisfactionLevel = satisfactionLevel + rating
	rating = rating - 1

	if (rating > 0 and rating < self.performanceRatings.minPositive) then
		rating = self.performanceRatings.minPositive
	elseif (rating < 0 and rating < self.performanceRatings.minNegative) then
		rating = self.performanceRatings.minNegative
	end

	writeData(controlID .. ":theater_manager:rating:flourish_" .. flourishID, rating)
	writeData(controlID .. ":theater_manager:satisfactionLevel", satisfactionLevel)
	writeData(controlID .. ":theater_manager:performedFlourishes", perHeartbeat)
	return 0
end

-- Heartbeat function to update satisfaction level and ratings every 15 seconds
function TheaterManagerScreenPlay:doPerformanceHeartbeat(pControl)
	local controlID = SceneObject(pControl):getObjectID()

	if (readData(controlID .. ":theater_manager:show_ended") == 1) then
		return
	end

	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		self:failPerformance(pControl, "fail_not_in_area")
		return
	end

	if (not CreatureObject(pPlayer):isDancing() and not CreatureObject(pPlayer):isPlayingMusic()) then
		if (readData(controlID .. ":theater_manager:not_performing") == 1) then
			self:failPerformance(pControl, "fail_not_playing")
		else
			writeData(controlID .. ":theater_manager:not_performing", 1)
		end
		return
	end
	deleteData(controlID .. ":theater_manager:not_performing")

	local curPerformance = CreatureObject(pPlayer):getPerformanceName()

	local rating = readData(controlID .. ":theater_manager:rating:" .. curPerformance)

	if (rating == nil or rating == 0) then
		rating = self.performanceRatings.default
	end

	local satisfactionLevel = readData(controlID .. ":theater_manager:satisfactionLevel")

	if (satisfactionLevel == nil) then
		satisfactionLevel = 0
	end

	satisfactionLevel = satisfactionLevel + rating
	rating = rating - 1

	if (rating > 0 and rating < self.performanceRatings.minPositive) then
		rating = self.performanceRatings.minPositive
	elseif (rating < 0 and rating < self.performanceRatings.minNegative) then
		rating = self.performanceRatings.minNegative
	end

	writeData(controlID .. ":theater_manager:rating:" .. curPerformance, rating)
	writeData(controlID .. ":theater_manager:satisfactionLevel", satisfactionLevel)

	self:doAudienceReaction(pControl)

	if (readData(controlID .. ":theater_manager:performedFlourishes") ~= nil) then

		deleteData(controlID .. ":theater_manager:performedFlourishes")
	end

	createEvent(self.performanceHeartbeat, "TheaterManagerScreenPlay", "doPerformanceHeartbeat", pControl)
end

-- Do audience reaction based on current satisfaction level
function TheaterManagerScreenPlay:doAudienceReaction(pControl)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		self:failPerformance(pControl, "fail_not_in_area")
		return
	end

	local curStep = self:getCurrentStep(pPlayer)

	local threshold = self.performanceThresholds[curStep]
	local satisfaction = readData(controlID .. ":theater_manager:satisfactionLevel")
	local rating = 100 * (satisfaction / threshold)

	local reactString

	if (rating > 125) then
		reactString = "@quest/crowd_pleaser/system_messages:reaction_1"
	elseif (rating > 100) then
		reactString = "@quest/crowd_pleaser/system_messages:reaction_2"
	elseif (rating > 75) then
		reactString = "@quest/crowd_pleaser/system_messages:reaction_3"
	elseif (rating > 50) then
		reactString = "@quest/crowd_pleaser/system_messages:reaction_3_5"
	elseif (rating > 25) then
		reactString = "@quest/crowd_pleaser/system_messages:reaction_4"
	elseif (rating > 0) then
		reactString = "@quest/crowd_pleaser/system_messages:reaction_5"
	else
		reactString = "@quest/crowd_pleaser/system_messages:reaction_6"
	end

	local messageString = LuaStringIdChatParameter("@quest/crowd_pleaser/system_messages:audience_reaction")
	messageString:setTO(reactString)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

-- Do audience reaction based on current satisfaction level
function TheaterManagerScreenPlay:doFinalAudienceReaction(pControl)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		return
	end

	local curStep = self:getCurrentStep(pPlayer)

	local threshold = self.performanceThresholds[curStep]
	local satisfaction = readData(controlID .. ":theater_manager:satisfactionLevel")
	local rating = 100 * (satisfaction / threshold)

	local reactEffect

	if (rating > 100) then
		reactEffect = "clienteffect/perform_cheer.cef"
	elseif (rating > 75) then
		reactEffect = "clienteffect/perform_clap.cef"
	elseif (rating > 25) then
		reactEffect = "clienteffect/perform_crickets.cef"
	else
		reactEffect = "clienteffect/perform_boo.cef"
	end

	playClientEffectLoc(playerID, reactEffect, SceneObject(pPlayer):getZoneName(), 0.16, 1.2, 36.74, SceneObject(pPlayer):getParentID())

end

-- Observer function when player enters a performance area
function TheaterManagerScreenPlay:notifyEnteredPerformanceArea(pActiveArea, pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local areaOwnerID = readData(SceneObject(pActiveArea):getObjectID() .. ":ownerID")

	if (playerID == areaOwnerID) then
		writeData(playerID .. ":theater_manager:inPerformanceArea", 1)
	end

	return 0
end

-- Observer function when player exits a performance area
function TheaterManagerScreenPlay:notifyExitedPerformanceArea(pActiveArea, pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local areaOwnerID = readData(SceneObject(pActiveArea):getObjectID() .. ":ownerID")

	if (playerID == areaOwnerID) then
		writeData(playerID .. ":theater_manager:inPerformanceArea", 0)

		if (readData(playerID .. ":theater_manager:performanceStarted") ~= 0) then
			local controlID = readData(playerID .. ":theater_manager:controlID")
			local pControl = getSceneObject(controlID)
			if (pControl ~= nil) then
				self:failPerformance(pControl, "fail_left_performance_area")
			end
			return 1
		end
	end

	return 0
end

-- Fails a players performance with reason, cleans up performance
function TheaterManagerScreenPlay:failPerformance(pControl, reason)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	createEvent(20 * 1000, "TheaterManagerScreenPlay", "performanceCleanup", pControl)

	if (pPlayer ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:" .. reason)
		self:setFailedStep(pPlayer)
	end

	writeData(controlID .. ":theater_manager:show_ended", 1)
end

-- Ends a performance, determines if player succeeded or failed
function TheaterManagerScreenPlay:endPerformance(pControl)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		self:failPerformance(pControl, "fail_not_in_area")
		return
	end

	local curStep = self:getCurrentStep(pPlayer)

	local threshold = self.performanceThresholds[curStep]

	local satisfactionLevel = readData(controlID .. ":theater_manager:satisfactionLevel")
	self:doFinalAudienceReaction(pControl)

	if (satisfactionLevel >= threshold) then
		self:succeedPerformance(pControl)
	else
		self:failPerformance(pControl, "fail_not_satisfied")
	end

end

-- Succeeds a performance called by function determining success
function TheaterManagerScreenPlay:succeedPerformance(pControl)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")

	local pPlayer = getSceneObject(playerID)

	createEvent(20 * 1000, "TheaterManagerScreenPlay", "performanceCleanup", pControl)

	if (pPlayer ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/crowd_pleaser/system_messages:succeed_performance")
		self:completeCurrentStep(pPlayer)
	end

	writeData(controlID .. ":theater_manager:show_ended", 1)
end

-- Cleans up performance after ending
function TheaterManagerScreenPlay:performanceCleanup(pControl)
	local controlID = SceneObject(pControl):getObjectID()
	local playerID = readData(controlID .. ":theater_manager:ownerID")
	local theaterID = readData(controlID .. ":theater_manager:theaterID")

	for i = 1, table.getn(self.songs), 1 do
		deleteData(controlID .. ":theater_manager:rating:" .. self.songs[i])
	end

	for i = 1, table.getn(self.dances), 1 do
		deleteData(controlID .. ":theater_manager:rating:" .. self.dances[i])
	end

	for i = 1, self.flourishes, 1 do
		deleteData(controlID .. ":theater_manager:rating:flourish_" .. i)
	end

	deleteData(playerID .. ":theater_manager:inPerformanceArea")
	deleteData(playerID .. ":theater_manager:performanceStarted")
	deleteData(theaterID .. ":theater_manager:show_running")
	deleteData(controlID .. ":theater_manager:audienceSpawned")
	deleteData(controlID .. ":theater_manager:countdownTime")
	deleteData(controlID .. ":theater_manager:not_performing")
	deleteData(controlID .. ":theater_manager:satisfactionLevel")
	deleteData(controlID .. ":theater_manager:performedFlourishes")
	deleteData(controlID .. ":theater_manager:show_ended")

	self:cleanupAudience(pControl)
	self:cleanupControl(pControl)
end
