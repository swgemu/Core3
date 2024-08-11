Yavin4LaborOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "Yavin4LaborOutpostScreenPlay",

	planet = "yavin4",

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old"},
	stationaryNpcs = {"bodyguard", "bounty_hunter", "businessman", "chiss_female", "chiss_male", "commoner_technician", "explorer", "fringer", "gambler", "medic", "mercenary", "miner",  "pilot", "scientist", "slicer"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, 7.3, 0.6, -6.7, -149, 3035379, "npc_standing_drinking"}, {1, 5.8, 0.6, -6.2, -141, 3035379, "angry"}, {1, -6.8, 0.6, 6.3, 179, 3035377, "npc_sitting_chair"}, {1, -6.8, 0.6, 5.0, 1, 3035377, "happy"},
		{1, -6.1, 0.6, -3.8, -102, 3035374, "sad"}, {1, -6.1, 0.6, -4.8, -10, 3035374, "npc_consoling"},
	},

	mobiles = {
		{"eker", 60, -3.9, 0.6, 1.2, -144, 3035372, ""},
		{"aqzow", 60, 1.9, 0.6, 1.7, 40, 3035376, ""}
	}
}

registerScreenPlay("Yavin4LaborOutpostScreenPlay", true)

function Yavin4LaborOutpostScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnStationaryMobiles()
	end
end

function Yavin4LaborOutpostScreenPlay:spawnMobiles()
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
