TalusImperialOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TalusImperialOutpostScreenPlay",

	planet = "talus",

	mobiles = {
		{"imperial_recruiter", 1, -2192, 20.0, 2269, -50, 0, ""},
		{"at_st", 300, -2167.8, 20.0, 2411.1, -8, 0, ""},
		{"stormtrooper", 300, -2194.6, 20.0, 2344.9, 179, 0, ""},
		{"stormtrooper", 300, -2187.9, 20.0, 2344.9, 179, 0, ""},
		{"stormtrooper", 300, -2178.9, 20.0, 2344.9, 179, 0, ""},
		{"stormtrooper", 300, -2172.1, 20.0, 2344.9, 179, 0, ""},
		{"stormtrooper", 300, -2170.5, 20.0, 2331.4, -90, 0, ""},
		{"stormtrooper", 300, -2170.5, 20.0, 2324.4, -90, 0, ""},
		{"stormtrooper", 300, -2170.5, 20.0, 2314.3, -90, 0, ""},
		{"stormtrooper", 300, -2170.5, 20.0, 2307.7, -90, 0, ""},
		{"stormtrooper", 300, -2170.5, 20.0, 2297.5, -90, 0, ""},
		{"stormtrooper", 300, -2170.5, 20.0, 2290.6, -90, 0, ""},
		{"stormtrooper", 300, -2170.5, 20.0, 2280.4, -90, 0, ""},
		{"stormtrooper", 300, -2170.5, 20.0, 2273.6, -90, 0, ""},
		{"stormtrooper", 300, -2180.1, 20.0, 2272.0, 1, 0, ""},
		{"stormtrooper", 300, -2195.5, 20.0, 2248.0, 120, 0, ""},
		{"stormtrooper", 300, -2197.5, 20.0, 2249.0, 120, 0, ""},
		{"stormtrooper", 300, -2199.5, 20.0, 2250.0, 120, 0, ""},
		{"stormtrooper", 300, -2196.5, 20.0, 2246.0, 120, 0, ""},
		{"stormtrooper", 300, -2198.5, 20.0, 2247.0, 120, 0, ""},
		{"stormtrooper", 300, -2200.5, 20.0, 2248.0, 120, 0, ""},
		{"stormtrooper_squad_leader", 300, -2193.4, 20.0, 2245.4, 120, 0, ""},
		{"stormtrooper_rifleman", 300, -2206.0, 20.0, 2282.0, -70, 0, ""},
		{"stormtrooper_rifleman", 300, -2205.0, 20.0, 2320.1, -127, 0, ""},
		{"imperial_private", 300, -2219.4, 20.0, 2299.2, -24, 0, ""},
		{"stormtrooper_sniper", 300, -2193.5, 20.0, 2267.2, -15, 0, ""},
		{"at_st", 300, -2198.2, 20.0, 2299.8, 0, 0, ""},
		{"stormtrooper_bombardier", 300, -2195.2, 20.0, 2295.2, 0, 0, ""},
		{"stormtrooper_bombardier", 300, -2201.2, 20.0, 2295.2, 0, 0, ""},

		{"hakassha_sireen", 300, 0.1, 0.1, -6.0, 0, 4965433, "neutral"},
		{"prisk_kith_vys", 300, -3.8, 0.1, -5.0, 39, 4965436, "neutral"}
	}
}

registerScreenPlay("TalusImperialOutpostScreenPlay", true)

function TalusImperialOutpostScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
	end
end

function TalusImperialOutpostScreenPlay:spawnMobiles()
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
