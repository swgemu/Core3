gcwLaunchEvent = ScreenPlay:new {

		spawnLocs = {
			--{ -1280, 0, -3590, "tatooine", FACTIONIMPERIAL }, -- Bestine
			--{ -150, 28, -4720, "corellia", FACTIONIMPERIAL } ,-- Coronet
			{ -4897, 6, 4106, "naboo", FACTIONIMPERIAL }, -- Theed
		--{ 110, 52, -5342, "tatooine", FACTIONREBEL }, -- Anchorhead
		--{ 6902, 330, -5550, "corellia", FACTIONREBEL },-- Bela Vistal
		--{ 4812, 4, -470, "naboo", FACTIONREBEL }, -- Moenia
		},

		eventTimer = { 1 * 60 * 60 * 1000, 3 * 60 * 60 * 1000 },
}

registerScreenPlay("gcwLaunchEvent", true)

function gcwLaunchEvent:start()
	createEvent(self:getEventTimer(), "gcwLaunchEvent", "startEvent", nil, "")
end

function gcwLaunchEvent:getEventTimer()
	return getRandomNumber(self.eventTimer[1], self.eventTimer[2])
end

function gcwLaunchEvent:startEvent()
	local eventLoc = self:getEventLocation()
	printf("1\n")

	if (eventLoc == nil) then
		createEvent(self:getEventTimer(), "gcwLaunchEvent", "startEvent", nil, "")
		return
	end
	printf("2\n")
	writeData("gcwLaunchEvent:faction", eventLoc[5])
	writeData("gcwLaunchEvent:dialogNumber", getRandomNumber(1,3))

	local shuttleTemplate = "object/creature/npc/theme_park/lambda_shuttle.iff"
	local shuttleName = "Lambda"
	printf("3\n")
	if (eventLoc[5] == FACTIONREBEL) then
		shuttleTemplate = "object/creature/npc/theme_park/player_shuttle.iff"
		shuttleName = "Shuttle"
	end
	printf("spawning template " .. shuttleTemplate .. "\n")
	local pShuttle = spawnSceneObject(eventLoc[4], shuttleTemplate, eventLoc[1], eventLoc[2], eventLoc[3], 0, math.rad(179))

	createEvent(1000, "gcwLaunchEvent", "setupShuttle", pShuttle, "")
end

function gcwLaunchEvent:setupShuttle(pShuttle)
	if (pShuttle == nil) then
		printf("setupShuttle nil\n")
		createEvent(self:getEventTimer(), "gcwLaunchEvent", "startEvent", nil, "")
		return
	end
	printf("setupShuttle 1\n")
	writeData("gcwLaunchEvent:shuttleID", SceneObject(pShuttle):getObjectID())
	local faction = readData("gcwLaunchEvent:faction")
	printf("Faction: " .. faction .. "\n")
	local shuttleName = "Lambda"

	if (faction == FACTIONREBEL) then
		CreatureObject(pShuttle):setPosture(PRONE)
		shuttleName = "Shuttle"
	end

	CreatureObject(pShuttle):setCustomObjectName(shuttleName)

	createEvent(3000, "gcwLaunchEvent", "landShuttle", pShuttle, "")
end

function gcwLaunchEvent:landShuttle(pShuttle)
	if (pShuttle == nil) then
		createEvent(self:getEventTimer(), "gcwLaunchEvent", "startEvent", nil, "")
		return
	end

	local faction = readData("gcwLaunchEvent:faction")

	local landingTime = 18 * 1000

	if (faction == FACTIONREBEL) then
		printf("landing reb shuttle\n")
		CreatureObject(pShuttle):setPosture(UPRIGHT)
		landingTime = 23 * 1000
	else
		printf("landing imp shuttle\n")
		CreatureObject(pShuttle):setPosture(PRONE)
	end

	createEvent(landingTime, "gcwLaunchEvent", "spawnMobs", pShuttle, "")
end

function gcwLaunchEvent:spawnMobs(pShuttle)
	if (pShuttle == nil) then
		printf("spawnMobs shuttle nil\n")
		createEvent(self:getEventTimer(), "gcwLaunchEvent", "startEvent", nil, "")
		return
	end

	local posX = SceneObject(pShuttle):getWorldPositionX()
	local posZ = SceneObject(pShuttle):getWorldPositionZ()
	local posY = SceneObject(pShuttle):getWorldPositionY()
	local zoneName = SceneObject(pShuttle):getZoneName()

	local faction = readData("gcwLaunchEvent:faction")

	local mobileTemplate = "elite_novatrooper_commander"

	if (faction == FACTIONREBEL) then
		mobileTemplate = "fbase_rebel_heavy_trooper"
	end

	for i = 1, 5, 1 do
		--local pMobile = spawnEventMobile(zoneName, "elite_novatrooper_commander", 100, posX, posZ, posY, 0, 0)

		if (pMobile ~= nil) then
			writeData("gcwLaunchEvent:mobile" .. i, SceneObject(pMobile):getObjectID())
		end
	end

	createEvent(20 * 1000, "gcwLaunchEvent", "spawnCelebrity", pShuttle, "")
end

function gcwLaunchEvent:spawnCelebrity(pShuttle)
	if (pShuttle == nil) then
		printf("spawnCeleb shuttle nil\n")
		self:destroyMobs()
		self:destroyShuttle()
		createEvent(self:getEventTimer(), "gcwLaunchEvent", "startEvent", nil, "")
		return
	end

	local faction = readData("gcwLaunchEvent:faction")
	local celebTemplate = "darth_vader"
	local musicTemplate = "sound/music_emperor_theme_stereo.snd"

	if (faction == FACTIONREBEL) then
		celebTemplate = "leia_organa"
		musicTemplate = "sound/music_leia_theme_stereo.snd"
	end

	local posX = SceneObject(pShuttle):getWorldPositionX()
	local posZ = SceneObject(pShuttle):getWorldPositionZ()
	local posY = SceneObject(pShuttle):getWorldPositionY()
	local zoneName = SceneObject(pShuttle):getZoneName()

	local pMobile = spawnMobile(zoneName, celebTemplate, 0, posX, posZ, posY, 179, 0)

	createEvent(1000, "gcwLaunchEvent", "setupCelebrity", pMobile, "")
end

function gcwLaunchEvent:setupCelebrity(pMobile)
	local shuttleID = readData("gcwLaunchEvent:shuttleID")
	local pShuttle = getSceneObject(shuttleID)

	if (pMobile == nil or pShuttle == nil) then
		self:destroyMobs()
		self:destroyShuttle()
		createEvent(self:getEventTimer(), "gcwLaunchEvent", "startEvent", nil, "")
		return
	end

	writeData("gcwLaunchEvent:celebrityID", SceneObject(pMobile):getObjectID())

	local playerTable = SceneObject(pShuttle):getPlayersInRange(100)

	local faction = readData("gcwLaunchEvent:faction")
	local musicTemplate = "sound/music_emperor_theme_stereo.snd"

	if (faction == FACTIONREBEL) then
		musicTemplate = "sound/music_leia_theme_stereo.snd"
	end

	for i = 1, #playerTable, 1 do
		local pPlayer = playerTable[i]

		if (pPlayer ~= nil) then
			CreatureObject(pPlayer):playMusicMessage(musicTemplate)
		end
	end

	CreatureObject(pMobile):clearOptionBit(CONVERSABLE)
	createObserver(DESTINATIONREACHED, "gcwLaunchEvent", "destinationReached", pMobile)

	AiAgent(pMobile):setAiTemplate("manualescortwalk") -- Don't move unless patrol point is added to list, walking speed
	AiAgent(pMobile):setFollowState(4) -- Patrolling

	createEvent(1000, "gcwLaunchEvent", "moveToPoint", pMobile, "speech")
end

function gcwLaunchEvent:moveToPoint(pMobile, pointName)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	local shuttleID = readData("gcwLaunchEvent:shuttleID")
	local pShuttle = getSceneObject(shuttleID)

	if (pShuttle == nil) then
		return
	end

	printf("moving to " .. pointName .. "\n")

	writeStringData(SceneObject(pMobile):getObjectID() .. ":nextPoint", pointName)

	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	local posX = SceneObject(pShuttle):getWorldPositionX()
	local posZ = SceneObject(pShuttle):getWorldPositionZ()
	local posY = SceneObject(pShuttle):getWorldPositionY() - 15

	if (pointName == "speech") then
		posY = posY - 15
		AiAgent(pMobile):setHomeLocation(posX, posZ, posY, 0)
		printf("Speech block " .. SceneObject(pShuttle):getWorldPositionX() .. " " .. SceneObject(pShuttle):getWorldPositionZ() .. " " .. SceneObject(pShuttle):getWorldPositionY() - 25 .. "\n")
		AiAgent(pMobile):setNextPosition(posX, posZ, posY, 0)
	else
		printf("else block\n")
		AiAgent(pMobile):setHomeLocation(posX, posZ, posY, 0)
		AiAgent(pMobile):setNextPosition(posX, posZ, posY, 0)
	end

	printf("exec\n")
	AiAgent(pMobile):executeBehavior()
end

function gcwLaunchEvent:destinationReached(pMobile)
	printf("destinationReached\n")
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return 1
	end

	local mobileID = SceneObject(pMobile):getObjectID()

	local pointName = readStringData(mobileID .. ":nextPoint")
	deleteStringData(mobileID .. ":nextPoint")

	if (pointName == "speech") then
		createEvent(1000, "gcwLaunchEvent", "doSpeech", pMobile, "")
	else
		createEvent(1000, "gcwLaunchEvent", "endEvent", pMobile, "")
	end

	return 0
end

function gcwLaunchEvent:doSpeech(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return 1
	end

	local speechStep = readData("gcwLaunchEvent:speechStep")
	local speechType = 0

	if (speechStep == 0) then
		speechStep = 1
	elseif (speechStep == 11) then
		self:moveToPoint(pMobile, "shuttle")
		return
	end

	local faction = readData("gcwLaunchEvent:faction")
	local speechAnims = { "", "", "pound_fist_palm", "", "force_push", "", "force_choke", "", "", "point_forward" }

	if (faction == FACTIONREBEL) then
		speechType = 1
		speechAnims = { "", "", "point_right", "", "pound_fist_palm", "", "nod_head_once", "", "", "point_forward" }
	end

	local dialogNum = readData("gcwLaunchEvent:dialogNumber")

	spatialChat(pMobile, "@gcwlaunchevent:dialogue_" .. speechType .. "_" .. dialogNum .. "_" .. speechStep)

	if (speechAnims[speechStep] ~= "") then
		CreatureObject(pMobile):doAnimation(speechAnims[speechStep])
	end

	writeData("gcwLaunchEvent:speechStep", speechStep + 1)
	createEvent(10* 1000, "gcwLaunchEvent", "doSpeech", pMobile, "")
end

function gcwLaunchEvent:endEvent(pMobile)
	self:destroyMobs()

	local faction = readData("gcwLaunchEvent:faction")

	local takeoffTime = 18 * 1000

	if (faction == FACTIONREBEL) then
		CreatureObject(pShuttle):setPosture(UPRIGHT)
		takeoffTime = 23 * 1000
	else
		CreatureObject(pShuttle):setPosture(PRONE)
	end

	createEvent(takeoffTime, "gcwLaunchEvent", "destroyShuttle", nil, "")
end

function gcwLaunchEvent:destroyShuttle()
	printLuaError("Destroying shuttle\n")
	local shuttleID = readData("gcwLaunchEvent:shuttleID")
	local pShuttle = getSceneObject(shuttleID)

	if (pShuttle ~= nil) then
		SceneObject(pShuttle):destroyObjectFromWorld()
	end

	deleteData("gcwLaunchEvent:shuttleID")
end

function gcwLaunchEvent:destroyMobs()
	printLuaError("Destroying mobs\n")
	for i = 1, 5, 1 do
		local mobileID = readData("gcwLaunchEvent:mobile" .. i)
		local pMobile = getSceneObject(mobileID)

		if (pMobile ~= nil and not CreatureObject(pMobile):isDead()) then
			if (CreatureObject(pMobile):isInCombat()) then
				createEvent(30 * 1000, "gcwLaunchEvent", "destroyMobile", pMobile, "")
			else
				SceneObject(pMobile):destroyObjectFromWorld()
			end
		end

		deleteData("gcwLaunchEvent:mobile" .. i)
	end

	local celebID = readData("gcwLaunchEvent:celebrityID")
	local pMobile = getSceneObject(mobileID)

	if (pMobile ~= nil) then
		SceneObject(pMobile):destroyObjectFromWorld()
	end

	deleteData("gcwLaunchEvent:celebrityID")
end

function gcwLaunchEvent:destroyMobile(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	if (CreatureObject(pMobile):isInCombat()) then
		createEvent(30 * 1000, "gcwLaunchEvent", "destroyMobile", pMobile, "")
		return
	end

	SceneObject(pMobile):destroyObjectFromWorld()
end

function gcwLaunchEvent:getEventLocation()
	for i = 1, 20, 1 do
		local randLoc = getRandomNumber(1, #self.spawnLocs)
		local eventLoc = self.spawnLocs[randLoc]

		if (isZoneEnabled(eventLoc[4])) then
			return eventLoc
		end
	end

	return nil
end
