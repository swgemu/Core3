CityScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityScreenPlay",

	planet = "",

	gcwMobs = {},
	patrolMobiles = {},
	patrolPoints = {},

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
	elseif controllingFaction == FACTIONIMPERIAL then
		npcTemplate = mobTable[1]
		x = mobTable[3]
		z = mobTable[4]
		y = mobTable[5]
		heading = mobTable[6]
		parentID = mobTable[7]
		npcMood = mobTable[8]
		scanner = mobTable[10]
	elseif controllingFaction == FACTIONREBEL then
		npcTemplate = mobTable[2]
		x = mobTable[3]
		z = mobTable[4]
		y = mobTable[5]
		heading = mobTable[6]
		parentID = mobTable[7]
		npcMood = mobTable[9]
		scanner = mobTable[10]
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
	end

	if pNpc ~= nil then
		createObserver(CREATUREDESPAWNED, self.screenplayName, "onDespawn", pNpc)
		writeData(SceneObject(pNpc):getObjectID(), num)
	end
end

function CityScreenPlay:onDespawn(pAiAgent)
	if pAiAgent == nil or not SceneObject(pAiAgent):isAiAgent() then
		printf("pAiAgent is nil or not an AiAgent")
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
	local pMobile = nil

	--{patrolPoints, template, level, x, z, y, direction, cell, mood},
	local pMobile = spawnMobile(self.planet, patrol[2], patrol[3], patrol[4], patrol[5], patrol[6], patrol[7], patrol[8], patrol[9])

	if (pMobile ~= nil and points ~= nil) then
		local pOid = SceneObject(pMobile):getObjectID()
		CreatureObject(pMobile):setPvpStatusBitmask(0)

		writeStringData(pOid .. ":patrolPoints", points)
		writeData(pOid .. ":currentLoc", 1)
		createEvent(3000, self.screenplayName, "setupMobilePatrol", pMobile, "")
	end
end

function CityScreenPlay:setupMobilePatrol(pMobile)
	createEvent(getRandomNumber(20, 40) * 1000, self.screenplayName, "mobilePatrol", pMobile, '')
	createObserver(DESTINATIONREACHED, self.screenplayName, "mobileDestinationReached", pMobile)
	AiAgent(pMobile):setAiTemplate("citypatrol")
	AiAgent(pMobile):setFollowState(4)
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
	local noDelay = currentSet[5]

	if (noDelay == 1) then
		createEvent(100, self.screenplayName, "mobilePatrol", pMobile, "")
	else
		createEvent(getRandomNumber( 30, 60) * 1000, self.screenplayName, "mobilePatrol", pMobile, "")
	end
	return 0
end

function CityScreenPlay:mobilePatrol(pMobile)
	if (pMobile == nil) then
		return
	end

	local pointSets = self.patrolPoints
	local pOid = SceneObject(pMobile):getObjectID()
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

	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	AiAgent(pMobile):setNextPosition(nextPoint[1], nextPoint[2], nextPoint[3], nextPoint[4])
	AiAgent(pMobile):executeBehavior()
end
