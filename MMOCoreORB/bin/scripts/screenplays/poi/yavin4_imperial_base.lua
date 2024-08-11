Yavin4ImperialBaseScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	planet = "yavin4",

	mobiles = {
		{"at_st", 720, 4028.7, 37.0, -6349.5, 175, 0, ""},
		
		{"stormtrooper", 300, 4025.1, 18.6, -6509.2, 180, 0, ""},
		{"stormtrooper", 300, 4021.6, 18.8, -6509.2, 180, 0, ""},
	
		{"stormtrooper_bombardier", 300, 4013.6, 38.1, -6324.8, 90, 0, ""},
		{"stormtrooper_sniper", 300, 4000.6, 36.9, -6289.3, 90, 0, ""},
		{"imperial_colonel", 300, 4051.7, 36.9, -6255.1, 90, 0, ""},
		{"stormtrooper", 300, 4051.7, 36.9, -6258.6, 0, 0, ""},
		{"stormtrooper", 300, 4008.7, 36.9, -6215.6, 180, 0, ""},
		{"stormtrooper", 300, 4004.8, 36.9, -6251.1, 0, 0, ""},
		{"stormtrooper", 300, 4052.7, 36.9, -6214.8, -180, 0, ""},
	
		{"commoner_technician", 300, 4001.0, 36.9, -6229.8, -75, 0, ""},
		{"commoner", 300, 3993.0, 36.9, -6269.1, 45, 0, ""},
		{"commoner_old", 300, 3996.7, 36.9, -6270.0, 0, 0, ""},
		{"commoner", 300, 3997.0, 36.9, -6267.2, -135, 0, ""},
		{"pilot", 300, 4050.0, 36.9, -6226.2, -35, 0, ""},
		{"pilot", 300, 4038.4, 36.9, -6244.6, -163, 0, ""},
	
		{"stormtrooper_medic", 300, 4.0, 0, 2.2, 90, 8735498, ""},
		{"haymir_rendundi", 300, 0, 0, -5.6, 0, 8735497, ""},
	
		{"imperial_medic", 300, 4.9, 0, 1.5, 90, 8735519, ""},
		{"imperial_trooper", 300, 3.7, 0, 3.8, -90, 8735521, ""},
		{"alozen", 300, 0.003, 0.125, -5.558, 0, 8735518, ""},
		{"barlow", 60, 4028.91, 37, -6201.62, 150, 0, "npc_imperial"}
	}

}

registerScreenPlay("Yavin4ImperialBaseScreenPlay", true)

function Yavin4ImperialBaseScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
	end
end

function Yavin4ImperialBaseScreenPlay:spawnMobiles()
	local mobiles = self.mobiles

	for i = 1, #mobiles, 1 do
		local mob = mobiles[i]

		-- {template, respawn, x, z, y, direction, cell, mood},
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