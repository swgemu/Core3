AbandonedRebelBaseScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "AbandonedRebelBaseScreenPlay",

	planet = "dantooine",

	mobiles = {
		--inside perimeter near east building area
		{"rebel_commando", 400, -6656.4, 30.0, 5552.4, -1, 0, ""},
		{"rebel_commando", 400, -6661.4, 30.0, 5557.4, -1, 0, ""},
		{"rebel_commando", 400, -6651.4, 30.0, 5547.4, -1, 0, ""},
		{"rebel_commando", 400, -6663.4, 30.0, 5562.4, -1, 0, ""},

		{"rebel_recruiter", 0, -6817, 46, 5511, 174, 0, ""},

		--inside main building
		{"vrovel", 60, -1.1, 1.0, 0.5, 177, 6555560, ""},
		{"ezkiel", 60, -3.2, 1.0, 7.9, 11, 6555560, ""}
	}
}

registerScreenPlay("AbandonedRebelBaseScreenPlay", true)

function AbandonedRebelBaseScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
	end
end

function AbandonedRebelBaseScreenPlay:spawnMobiles()
	local mobiles = self.mobiles

	for i = 1, #mobiles, 1 do
		local mob = mobiles[i]

		-- {template, respawn, x, z, y, direction, cell, mood}
		local pMobile = spawnMobile(self.planet, mob[1], mob[2], mob[3], mob[4], mob[5], mob[6], mob[7])

		if (pMobile ~= nil) then
			if mob[8] ~= "" then
				CreatureObject(pMobile):setMoodString(mob[8])
			end

			AiAgent(pMobile):addObjectFlag(AI_STATIC)

			if CreatureObject(pMobile):getPvpStatusBitmask() == 0 then
				CreatureObject(pMobile):clearOptionBit(AIENABLED)
			end
		end
	end
end
