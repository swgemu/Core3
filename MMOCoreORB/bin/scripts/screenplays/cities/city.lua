CityScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityScreenPlay",

	planet = "",

	gcwMobs = {},

	combatPatrol = {},
	patrolNpcs = {},
	patrolMobiles = {},
	patrolPoints = {},

	stationaryCommoners = {},
	stationaryNpcs = {},
	stationaryMobiles = {},
}

function CityScreenPlay:spawnGcwMobiles()
	if (isZoneEnabled(self.planet)) then
		local controllingFaction = getControllingFaction(self.planet)
		local difficulty = getWinningFactionDifficultyScaling(self.planet)

		if controllingFaction == FACTIONNEUTRAL then
			controllingFaction = FACTIONIMPERIAL
		end

		for i = 1, #self.gcwMobs do
			self:spawnMob(i, controllingFaction, difficulty)
		end
	end
end

function CityScreenPlay:spawnMob(num, controllingFaction, difficulty)
	local mobsTable = self.gcwMobs

	if num <= 0 or num > #mobsTable then
		return
	end

	local mobTable = mobsTable[num]
	local pNpc = nil
	local npcTemplate = ""
	local x
	local y
	local z
	local heading
	local parentID
	local npcMood = ""
	local scanner = false

	if #mobTable < 9 then
		npcTemplate = mobTable[1]
		x = mobTable[2]
		z = mobTable[3]
		y = mobTable[4]
		heading = mobTable[5]
		parentID = mobTable[6]
		npcMood = mobTable[7]
		scanner = mobTable[8]
	else
		x = mobTable[3]
		z = mobTable[4]
		y = mobTable[5]
		heading = mobTable[6]
		parentID = mobTable[7]
		scanner = mobTable[10]
		if controllingFaction == FACTIONIMPERIAL then
			npcTemplate = mobTable[1]
			npcMood = mobTable[8]
		else
			npcTemplate = mobTable[2]
			npcMood = mobTable[9]
		end
	end

	local scaling = ""
	if difficulty > 1 and creatureTemplateExists(npcTemplate .. "_hard") then
		scaling = "_hard"
	end

	pNpc = spawnMobile(self.planet, npcTemplate .. scaling, 0, x, z, y, heading, parentID)

	if pNpc ~= nil then
		if npcMood ~= "" then
			self:setMoodString(pNpc, npcMood)
		end
		if scanner then
			local aiAgent = AiAgent(pNpc)
			aiAgent:setCreatureBit(SCANNING_FOR_CONTRABAND)
		end

		AiAgent(pNpc):addCreatureFlag(AI_STATIC)
		createObserver(CREATUREDESPAWNED, self.screenplayName, "onDespawn", pNpc)
		writeData(SceneObject(pNpc):getObjectID(), num)
	end
end

function CityScreenPlay:onDespawn(pAiAgent)
	if pAiAgent == nil or not SceneObject(pAiAgent):isAiAgent() then
		printf("pAiAgent is nil or not an AiAgent" .. "\n")
		return
	end

	local oid = SceneObject(pAiAgent):getObjectID()
	local mobNumber = readData(oid)
	deleteData(oid)

	createEvent(300000, self.screenplayName, "respawn", nil, tostring(mobNumber))

	return 1
end

function CityScreenPlay:respawn(pAiAgent, args)
	local mobNumber = tonumber(args)
	local controllingFaction = getControllingFaction(self.planet)
	local difficulty = getWinningFactionDifficultyScaling(self.planet)

	if controllingFaction == FACTIONNEUTRAL then
		controllingFaction = FACTIONIMPERIAL
	end

	self:spawnMob(mobNumber, controllingFaction, difficulty)
end

function CityScreenPlay:spawnPatrolMobiles()
	if (isZoneEnabled(self.planet)) then
		for i = 1, #self.patrolMobiles do
			self:spawnPatrol(i)
		end
	end
end

function CityScreenPlay:spawnPatrol(num)
	local patrolsTable = self.patrolMobiles

	if num <= 0 or num > #patrolsTable then
		return
	end

	local patrol = patrolsTable[num]
	local points = patrol[1]
	local template = patrol[2]
	local pMobile = nil
	local mood = patrol[8]

	if (template == "patrolNpc") then
		local patrolNpcs = self.patrolNpcs
		local templateNum = getRandomNumber(#patrolNpcs)

		template = patrolNpcs[templateNum]
	elseif (template == "combatPatrol") then
		local combatPatrol = self.combatPatrol
		local templateNum = getRandomNumber(#combatPatrol)

		template = combatPatrol[templateNum]
	end

	--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol}
	local pMobile = spawnMobile(self.planet, template, 0, patrol[3], patrol[4], patrol[5], patrol[6], patrol[7])

	if (pMobile ~= nil and points ~= nil) then
		if mood ~= "" then
			self:setMoodString(pMobile, mood)
		end

		local pOid = SceneObject(pMobile):getObjectID()

		createEvent(3000, self.screenplayName, "setupMobilePatrol", pMobile, num)
		writeStringData(pOid .. ":patrolPoints", points)
		writeData(pOid .. ":patrolNumber", num)
		writeData(pOid .. ":currentLoc", 1)
	end
end

function CityScreenPlay:setupMobilePatrol(pMobile, num)
	if (pMobile == nil) then
		return
	end

	local spawnNumber = tonumber(num)
	local combatNpc = self.patrolMobiles[spawnNumber][9]

	if combatNpc then
		createObserver(CREATUREDESPAWNED, self.screenplayName, "onDespawnPatrol", pMobile)
		return
	else
		CreatureObject(pMobile):setPvpStatusBitmask(0)
	end

	createEvent(getRandomNumber(20, 40) * 1000, self.screenplayName, "mobilePatrol", pMobile, '')
	createObserver(DESTINATIONREACHED, self.screenplayName, "mobileDestinationReached", pMobile)
end

function CityScreenPlay:onDespawnPatrol(pMobile)
	if pMobile == nil or not SceneObject(pMobile):isAiAgent() then
		printf("Combat Patrol pMobile is nil or not an AiAgent" .. "\n")
		return
	end

	local pOid = SceneObject(pMobile):getObjectID()
	local spawnNumber = readData(pOid .. ":patrolNumber")

	createEvent(300 * 1000, self.screenplayName, "patrolRespawn", nil, tostring(spawnNumber))

	dropObserver(DESTINATIONREACHED, self.screenplayName, "mobileDestinationReached", pMobile)
	deleteData(pOid .. ":patrolNumber")
	deleteData(pOid .. ":currentLoc")
	deleteStringData(pOid .. ":patrolPoints")

	return 1
end

function CityScreenPlay:patrolRespawn(pMobile, args)
	local spawnNumber = tonumber(args)

	self:spawnPatrol(spawnNumber)
end

function CityScreenPlay:mobileDestinationReached(pMobile)
	if (pMobile == nil) then
		return 0
	end

	local pOid = SceneObject(pMobile):getObjectID()
	local currentLoc = readData(pOid .. ":currentLoc")
	local mobileTable = readStringData(pOid .. ":patrolPoints")
	local pointSet = self.patrolPoints
	local pointSets = pointSet[mobileTable]
	local patrolPointCount = #pointSets

	if (currentLoc >= patrolPointCount) then
		writeData(pOid .. ":currentLoc", 1)
	else
		writeData(pOid .. ":currentLoc", currentLoc + 1)
	end

	local currentSet = pointSets[currentLoc]
	local delay = currentSet[5]

	if (delay) then
		local delayTime = getRandomNumber(30, 60)

		createEvent(delayTime * 1000, self.screenplayName, "mobilePatrol", pMobile, "")
		AiAgent(pMobile):setWait(delayTime)
	else
		createEvent(100, self.screenplayName, "mobilePatrol", pMobile, "")
	end

	return 0
end

function CityScreenPlay:mobilePatrol(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	local pOid = SceneObject(pMobile):getObjectID()

	if (AiAgent(pMobile):isInCombat()) then
		createEvent(25 * 1000, self.screenplayName, "mobilePatrol", pMobile, "")
	end

	local pointSets = self.patrolPoints
	local mobileTable = readStringData(pOid .. ":patrolPoints")
	local currentLoc = readData(pOid .. ":currentLoc")

	local pointSet = pointSets[mobileTable]
	local patrolPointCount = #pointSet
	local nextPoint

	if (currentLoc >= patrolPointCount) then
		nextPoint = pointSet[1]
	else
		nextPoint = pointSet[currentLoc + 1]
	end

	AiAgent(pMobile):setNextPosition(nextPoint[1], nextPoint[2], nextPoint[3], nextPoint[4])
end

function CityScreenPlay:spawnStationaryMobiles()
	if (isZoneEnabled(self.planet)) then
		for i = 1, #self.stationaryMobiles do
			self:spawnStationaryMobile(i)
		end
	end
end

function CityScreenPlay:spawnStationaryMobile(num)
	local stationaryTable = self.stationaryMobiles

	if num <= 0 or num > #stationaryTable then
		return
	end

	local pMobile = nil
	local mobile = stationaryTable[num]
	local stationaryTemps = nil
	local template = ""
	local mood = mobile[7]

	if (getRandomNumber(100) < 20 ) then
		stationaryTemps = self.stationaryNpcs
		local templateNum = getRandomNumber(#stationaryTemps)

		template = stationaryTemps[templateNum]
	else
		stationaryTemps = self.stationaryCommoners
		local templateNum = getRandomNumber(#stationaryTemps)

		template = stationaryTemps[templateNum]
	end

	--{respawn, x, z, y, direction, cell, mood}
	local pMobile = spawnMobile(self.planet, template, mobile[1], mobile[2], mobile[3], mobile[4], mobile[5], mobile[6])

	if (pMobile ~= nil) then
		if mood ~= "" then
			self:setMoodString(pMobile, mood)
		end

		CreatureObject(pMobile):setPvpStatusBitmask(0)

		if CreatureObject(pMobile):getOptionsBitmask() > 0 then
			CreatureObject(pMobile):clearOptionBit(AIENABLED)
		end
	end
end
