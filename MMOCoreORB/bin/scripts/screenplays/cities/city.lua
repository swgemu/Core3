CityScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityScreenPlay",

	planet = "",

	gcwMobs = {},
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
	local npcMood = ""

	if controllingFaction == FACTIONIMPERIAL then
		npcTemplate = mobTable[1]
		npcMood = mobTable[8]
	elseif controllingFaction == FACTIONREBEL then
		npcTemplate = mobTable[2]
		npcMood = mobTable[9]
	end

	local scaling = ""
	if difficulty > 1 and creatureTemplateExists(npcTemplate .. "_hard") then
		scaling = "_hard"
	end

	pNpc = spawnMobile(self.planet, npcTemplate .. scaling, 0, mobTable[3], mobTable[4], mobTable[5], mobTable[6], mobTable[7])

	if pNpc ~= nil then
		if npcMood ~= "" then
			self:setMoodString(pNpc, npcMood)
		end
		if mobTable[10] then
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


--Patrols Implementation


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
	local pMobile = nil

	--{template, patrolPoints, level, x, z, y, direction, cell, mood},
	pMobile = spawnMobile(self.planet, patrol[1], patrol[3], patrol[4], patrol[5], patrol[6], patrol[7], patrol[8], patrol[9])

	if pMobile ~= nil then
		local pOid = SceneObject(pMobile):getObjectID()

		writeData(pOid .. ":patrolPoints", patrol[2])
		writeData(pOid .. ":currentLoc", 1)
		self:setupMobilePatrol(pMobile)
	end
end

function CityScreenPlay:setupMobilePatrol(pMobile)
	createEvent(4000, "CityScreenPlay", "mobilePatrol", pMobile, "")
	createObserver(DESTINATIONREACHED, "CityScreenPlay", "mobileDestinationReached", pMobile)
	AiAgent(pDroid):setAiTemplate("manualescortwalk")
	AiAgent(pDroid):setFollowState(4)
end

function CityScreenPlay:mobilePatrol(pMobile)
	local patrolPoint = self.patrolPoints

	if (pMobile == nil) then
		return
	end

	local pOid = SceneObject(pMobile):getObjectID()
	local patrolNum = readData(pOid .. ":patrolPoints")
	local currentLoc = readData(pOid .. ":currentLoc")
	local coordTable = patrolPoint[patrolNum]
	local nextLoc

	if (currentLoc == 1) then
		nextLoc = coordTable[2]
	elseif (currentLoc == 2 and coordTable[3] ~= nil) then
		nextLoc = patrolPoint[3]
	else
		nextLoc = patrolPoint[1]
	end

	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	AiAgent(pMobile):setNextPosition(nextLoc.x, nextLoc.z, nextLoc.y, 0)
	AiAgent(pMobile):executeBehavior()

end

function CityScreenPlay:mobileDestinationReached(pMobile)
	if (pMobile == nil) then
		return 0
	end

	local currentLoc = readData(SceneObject(pMobile):getObjectID() .. ":currentLoc")
	local pOid = SceneObject(pMobile):getObjectID()

	if (currentLoc == 1) then
		writeData(pOid .. ":currentLoc", 2)
	elseif (currentLoc == 2) then
		writeData(pOid .. ":currentLoc", 1)
	end

	createEvent(1000, "CityScreenPlay", "mobilePatrol", pMobile, "")

	return 0
end
