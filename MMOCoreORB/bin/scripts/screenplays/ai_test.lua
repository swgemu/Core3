AITest = ScreenPlay:new {
	screenplayName = "AITest",
	planet = "creature_test",

	location = {0, 0, 0},

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
	local x = loc[1]
	local y = loc[3]
	local z = getWorldFloor(x, y, self.planet)

	local pMobile = spawnMobile(self.planet, "gondula_worker", -1, x, z, y, 0, 0)

	if (pMobile ~= nil) then
		AiAgent(pMobile):addCreatureFlag(AI_STATIONARY)
	end
end