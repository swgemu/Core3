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
