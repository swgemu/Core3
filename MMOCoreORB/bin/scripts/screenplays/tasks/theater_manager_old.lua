local ObjectManager = require("managers.object.object_manager")

TheaterManagerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "TheaterManagerScreenPlay"
}

THEATER_MANAGER_ENABLED = 0

local AUDITION_COUNTDOWN_TIME = 30 * 1000 -- 30 seconds
local PROMOTION_ONE_REQUIRED = 2
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
		writeData("theater_manager:show_performer", player:getObjectID())

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
		local pAuditionArea = spawnActiveArea("naboo", "object/active_area.iff", -5791.9, 8.1, 4235.9, 7, 0)
		ObjectManager.withActiveArea(pAuditionArea, function(auditionArea)
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
	if not SceneObject(pPlayer):isCreatureObject() then
		return 0
	end

	return ObjectManager.withActiveArea(pActiveArea, function(activeArea)
		return ObjectManager.withCreatureObject(pPlayer, function(player)
			local playerID = player:getObjectID()
			local areaOwnerID = readData(activeArea:getObjectID() .. ":ownerID")
			if (playerID == areaOwnerID) then
				writeData(player:getObjectID() .. ":inAuditionArea", 1)
				return 0
			end

			return 0
		end)
	end)
end

function TheaterManagerScreenPlay:notifyExitedAuditionArea(pActiveArea, pPlayer)
	if not SceneObject(pPlayer):isCreatureObject() then
		return 0
	end

	return ObjectManager.withActiveArea(pActiveArea, function(activeArea)
		return ObjectManager.withCreatureObject(pPlayer, function(player)
			local playerID = player:getObjectID()
			local areaOwnerID = readData(activeArea:getObjectID() .. ":ownerID")
			if (playerID == areaOwnerID) then
				writeData(player:getObjectID() .. ":inAuditionArea", 0)
				if (readData(player:getObjectID() .. ":auditionPhase") ~= nil and readData(player:getObjectID() .. ":auditionPhase") ~= 0) then
					self:failAudition(pPlayer, "fail_left_audition_area")
					return 1
				end
			end

			return 0
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
			createEvent(getRandomNumber(8,12) * 1000, "TheaterManagerScreenPlay", "runAuditionPhase", pPlayer)
		end
	end)
end

function TheaterManagerScreenPlay:runAuditionPhase(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local phase = readData(player:getObjectID() .. ":auditionPhase")
		local judgeID = readData(player:getObjectID() .. ":judge" .. getRandomNumber(3) .. "ID")
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
			createEvent(getRandomNumber(8,15) * 1000, "TheaterManagerScreenPlay", "checkPerformanceStatus", pPlayer)
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
			createEvent(getRandomNumber(8,15) * 1000, "TheaterManagerScreenPlay", "checkPerformanceStatus", pPlayer)
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
	if not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local auditionType = readData(player:getObjectID() .. ":auditionType")
		local expectedPerformance = readData(player:getObjectID() .. ":expectedPerformance")
		if (self:isExpectedPerformance(pPlayer, expectedPerformance, auditionType) == true) then
			writeData(player:getObjectID() .. ":performanceCompleted", 1)
			dropObserver(STARTENTERTAIN, pPlayer)
			dropObserver(CHANGEENTERTAIN, pPlayer)
		end
	end)

	return 0
end

function TheaterManagerScreenPlay:notifyFlourishObserver(pPlayer, pPlayer2, flourishID)
	if not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local auditionType = readData(player:getObjectID() .. ":auditionType")
		local expectedPerformance = readData(player:getObjectID() .. ":expectedPerformance")
		if (flourishID == expectedPerformance) then
			writeData(player:getObjectID() .. ":performanceCompleted", 1)
			return 1
		end

		return 0
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
				local performanceName = AUDITION_DANCES[getRandomNumber(table.getn(AUDITION_DANCES))]
				if (playerObject:hasAbility("startDance+" .. performanceName) == true and (currentPerformance == nil or performanceName ~= currentPerformance)) then
					performance = self:getPerformanceKey(1, performanceName)
				end
			end
			return performance
		elseif (type == 2) then
			while performance == nil do
				local performanceName = AUDITION_SONGS[getRandomNumber(table.getn(AUDITION_SONGS))]
				if (playerObject:hasAbility("startMusic+" .. performanceName) == true and (currentPerformance == nil or performanceName ~= currentPerformance)) then
					performance = self:getPerformanceKey(2, performanceName)
				end
			end
			return performance
		elseif (type == "flourish") then
			return getRandomNumber(AUDITION_FLOURISHES)
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
			TheaterManagerScreenPlay:completeStep(pPlayer, "dance", 1)
			self:setCurrentSeries(pPlayer, "dance")
		elseif (auditionType == 2) then
			TheaterManagerScreenPlay:completeStep(pPlayer, "music", 1)
			self:setCurrentSeries(pPlayer, "music")
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

function TheaterManagerScreenPlay:getCurrentStep(pPlayer, series)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local state = "theater_manager_" .. series
		if (player:hasScreenPlayState(64, state)) then return 8 -- Completed
		elseif (player:hasScreenPlayState(32, state)) then return 7 -- Show 3
		elseif (player:hasScreenPlayState(16, state)) then return 6 -- Promo 3
		elseif (player:hasScreenPlayState(8, state)) then return 5 -- Show 2
		elseif (player:hasScreenPlayState(4, state)) then return 4 -- Promo 2
		elseif (player:hasScreenPlayState(2, state)) then return 3 -- Show 1
		elseif (player:hasScreenPlayState(1, state)) then return 2 -- Promo 1
		elseif (not player:hasScreenPlayState(1, state)) then return 1 -- Audition
		else return 0
		end
	end)
end

function TheaterManagerScreenPlay:completeStep(pPlayer, series, step)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local state = "theater_manager_" .. series
		if (step == 8) then player:setScreenPlayState(128, state) -- Completed
		elseif (step == 7) then player:setScreenPlayState(64, state) -- Show 3
		elseif (step == 6) then player:setScreenPlayState(32, state) -- Promo 3
		elseif (step == 5) then player:setScreenPlayState(16, state) -- Show 2
		elseif (step == 4) then player:setScreenPlayState(8, state) -- Promo 2
		elseif (step == 3) then player:setScreenPlayState(4, state) -- Show 1
		elseif (step == 2) then player:setScreenPlayState(2, state) -- Promo 1
		elseif (step == 1) then player:setScreenPlayState(1, state) -- Audition
		else
			printf("Invalid step sent to TheaterManagerScreenPlay:completeStep\n")
		end
	end)
end

function TheaterManagerScreenPlay:getCurrentSeries(pPlayer)
	return readScreenPlayData(pPlayer, "theaterManager", "currentSeries")
end

function TheaterManagerScreenPlay:resetCurrentSeries(pPlayer)
	return writeScreenPlayData(pPlayer, "theaterManager", "currentSeries", 0)
end

function TheaterManagerScreenPlay:setCurrentSeries(pPlayer, series)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		setQuestStatus(player:getObjectID() .. ":theater_manager:currentSeries", series)
	end)
end

function TheaterManagerScreenPlay:setCurrentPromotions(pPlayer, promotions)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		setQuestStatus(player:getObjectID() .. ":theater_manager:currentPromotions", promotions)
	end)
end

function TheaterManagerScreenPlay:eraseCurrentPromotions(pPlayer, promotions)
	printf("eraseCurrentPromotions triggered\n")
	ObjectManager.withCreatureObject(pPlayer, function(player)
		removeQuestStatus(player:getObjectID() .. ":theater_manager:currentPromotions")
	end)
end

function TheaterManagerScreenPlay:doPayout(pPlayer, amount)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		player:addCashCredits(amount, true)
		player:sendSystemMessage("You have received " .. amount .. " credits from the theater manager.")
	end)
end

function TheaterManagerScreenPlay:getCurrentPromotions(pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local promotions = getQuestStatus(player:getObjectID() .. ":theater_manager:currentPromotions")
		if (promotions ~= nil) then
			return tonumber(promotions)
		else
			return nil
		end
	end)
end

function TheaterManagerScreenPlay:getPlayersEntertainedList(pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local list = getQuestStatus(player:getObjectID() .. ":theater_manager:playersEntertained")
		if (list == nil) then
			return { }
		end
		return self:splitString(list, ",")
	end)
end

function TheaterManagerScreenPlay:writeToPlayersEntertainedList(pPlayer, playerID)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local list = getQuestStatus(player:getObjectID() .. ":theater_manager:playersEntertained")
		if (list == nil or list == "") then
			list = playerID
		else
			list = list .. "," .. playerID
		end
		setQuestStatus(player:getObjectID() .. ":theater_manager:playersEntertained", list)
	end)
end

function TheaterManagerScreenPlay:resetPlayersEntertainedList(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		setQuestStatus(player:getObjectID() .. ":theater_manager:playersEntertained", "")
	end)
end

function TheaterManagerScreenPlay:isInPlayersEntertainedList(pPlayer, playerID)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local playersEntertained = getQuestStatus(player:getObjectID() .. ":theater_manager:playersEntertained")
		if (playersEntertained == nil or playersEntertained == "") then
			return false
		end

		local list = self:splitString(playersEntertained, ",")
		for i = 1, table.getn(list), 1 do
			if tonumber(list[i]) == playerID then
				return true
			end
		end
		return false
	end)
end

function TheaterManagerScreenPlay:hasPromotedEnough(pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local series = self:getCurrentSeries(pPlayer)
		local currentStep = self:getCurrentStep(pPlayer, series)
		local requiredPromotions = self:getRequiredPromotions(currentStep)
		local currentPromotions = self:getCurrentPromotions(pPlayer)
		return (requiredPromotions == currentPromotions)
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

function TheaterManagerScreenPlay:getRequiredPromotions(step)
	if (step == 2) then
		return PROMOTION_ONE_REQUIRED
	elseif (step == 4) then
		return PROMOTION_TWO_REQUIRED
	elseif (step == 6) then
		return PROMOTION_THREE_REQUIRED
	end
end

function TheaterManagerScreenPlay:startPromotion(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		dropObserver(WASWATCHED, pPlayer)
		dropObserver(WASLISTENEDTO, pPlayer)
		local series = self:getCurrentSeries(pPlayer)
		local currentStep = self:getCurrentStep(pPlayer, series)
		local requiredPromotions = self:getRequiredPromotions(currentStep)
		self:eraseCurrentPromotions(pPlayer)
		self:setCurrentPromotions(pPlayer, 0)
		player:sendSystemMessage("You must entertain " .. requiredPromotions .. " players to acquire the next popularity rank.")
		if (self:getCurrentSeries(pPlayer) == "music") then
			createObserver(WASLISTENEDTO, "TheaterManagerScreenPlay", "notifyPromotionObserver", pPlayer, 1)
		elseif (self:getCurrentSeries(pPlayer) == "dance") then
			createObserver(WASWATCHED, "TheaterManagerScreenPlay", "notifyPromotionObserver", pPlayer, 1)
		end
	end)
end

function TheaterManagerScreenPlay:completePromotionPhase(pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local series = self:getCurrentSeries(pPlayer)
		local currentStep = self:getCurrentStep(pPlayer, series)
		self:resetPlayersEntertainedList(pPlayer)
		self:eraseCurrentPromotions(pPlayer)
		self:completeStep(pPlayer, series, currentStep)
	end)
end

function TheaterManagerScreenPlay:notifyPromotionObserver(pPlayer, pEntertained)
	if not SceneObject(pPlayer):isCreatureObject() or not SceneObject(pEntertained):isCreatureObject() then
		return 0
	end

	return ObjectManager.withCreatureObject(pPlayer, function(player)
		return ObjectManager.withCreatureObject(pEntertained, function(entertainedPlayer)
			local series = self:getCurrentSeries(pPlayer)
			local currentStep = self:getCurrentStep(pPlayer, series)
			local requiredPromotions = self:getRequiredPromotions(currentStep)
			local currentPromotions = self:getCurrentPromotions(pPlayer)

			if (currentPromotions == requiredPromotions or self:isInPlayersEntertainedList(pPlayer, entertainedPlayer:getObjectID()) == true) then
				return 0
			end

			self:setCurrentPromotions(pPlayer, currentPromotions + 1)
			currentPromotions = self:getCurrentPromotions(pPlayer)
			self:writeToPlayersEntertainedList(pPlayer, entertainedPlayer:getObjectID())

			if (requiredPromotions == currentPromotions) then
				player:sendSystemMessage("@quest/crowd_pleaser/system_messages:popularity_" .. (currentStep - 1) .. "_complete")
			else
				if (currentStep == 2) then
					player:sendSystemMessage("You are entertaining " .. entertainedPlayer:getFirstName() .. ". You must entertain " .. (requiredPromotions - currentPromotions) .. " more people to achieve Popularity Rank One.")
				elseif (currentStep == 4) then
					player:sendSystemMessage("You are entertaining " .. entertainedPlayer:getFirstName() .. ". You must entertain " .. (requiredPromotions - currentPromotions) .. " more people to achieve Popularity Rank Two.")
				elseif (currentStep == 6) then
					player:sendSystemMessage("You are entertaining " .. entertainedPlayer:getFirstName() .. ". You must entertain " .. (requiredPromotions - currentPromotions) .. " more people to achieve Popularity Rank Three.")
				end
			end

			return 0
		end)
	end)
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

registerScreenPlay("TheaterManagerScreenPlay", true)

theater_manager_conv_handler = TheaterManagerConvoHandler:new {
	themePark = TheaterManager
}
