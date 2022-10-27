AITest = ScreenPlay:new {
	screenplayName = "AITest",
	planet = "creature_test",

	location = {0, 0, 0},
	numberOfSpawns = 5,
}

registerScreenPlay("AITest", false)

function AITest:start()
	if (not isZoneEnabled(self.planet)) then
		return
	end

	self:spawnMobiles()
end

function AITest:spawnMobiles()
	local loc = self.location
	local x = loc[1] + getRandomNumber(10)
	local y = loc[3] + getRandomNumber(10)
	local z = getWorldFloor(x, y, self.planet)
	local spawnNum = self.numberOfSpawns

	for i = 1, spawnNum, 1 do
		local pMobile = spawnMobile(self.planet, "relentless_purbole", -1, x, z, y, 0, 0)

		if (pMobile ~= nil) then
			--AiAgent(pMobile):addCreatureFlag(AI_STATIONARY)

			createObserver(OBJECTDESTRUCTION, "AITest", "notifyKilled", pMobile)
		end
	end
end

function AITest:spawnMobile()
	local loc = self.location
	local x = loc[1] + getRandomNumber(10)
	local y = loc[3] + getRandomNumber(10)
	local z = getWorldFloor(x, y, self.planet)

	local pMobile = spawnMobile(self.planet, "relentless_purbole", -1, x, z, y, 0, 0)

	if (pMobile ~= nil) then
		--AiAgent(pMobile):addCreatureFlag(AI_STATIONARY)

		createObserver(OBJECTDESTRUCTION, "AITest", "notifyKilled", pMobile)
	end
end

function AITest:notifyKilled(pAgent, pKiller)
	if (pAgent ~= nil) then
		self:spawnMobile()
	end

	return 1
end
