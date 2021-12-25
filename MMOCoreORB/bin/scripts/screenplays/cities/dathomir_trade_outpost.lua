DathomirTradeOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DathomirTradeOutpostScreenPlay",

	planet = "dathomir",

	combatPatrol = {"commando", "commoner_technician", "mercenary", "miner", "sharpshooter"},
	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"r4_1", "r4", 620, 6, 3088, 191.123, 0, "", false},
		{"r4_2", "r4", 619.822, 6, 3097.36, 339.758, 0, "", false},
		{"r5_1", "r5", 627.744, 6, 3086.77, 278.522, 0, "", false},

		--NPCs
		{"npc_1", "combatPatrol", 559, 6, 3076, 297, 0, "", true},
		{"npc_2", "combatPatrol", 566, 6, 3070, 284, 0, "", true},
		{"npc_3", "combatPatrol", 578, 6, 3092, 253, 0, "", true},
		{"npc_4", "patrolNpc", 590, 6, 3058, 264, 0, "", false},
		{"npc_5", "patrolNpc", 577, 6, 3100, 52, 0, "", false},
		{"npc_6", "patrolNpc", 616, 6, 3056, 135.38, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		r4_1 = {{620, 6, 3085, 0, false}, {620, 6, 3065, 0, false}, {599, 6, 3058, 0, false}, {590, 6, 3080, 0, false}, {618, 6, 3089, 0, true}},
		r4_2 = {{620, 6, 3089, 0, false}, {613, 6, 3106, 0, true}, {607, 6, 3109, 0, false}, {615, 6, 3108, 0, true}, {623, 6, 3101, 0, false}, {619, 6, 3087, 0, true}},
		r5_1 = {{633, 6, 3084, 0, false}, {622, 6, 3086, 0, true}, {636, 6, 3085, 0, false}, {637, 6, 3044, 0, false}, {619, 6, 3029, 0, false}, {619, 6, 3043, 0, false}, {637, 6, 3044, 0, false}},

		npc_1 = {{559, 6, 3076, 0, true}, {536, 8, 3077, 0, true}, {546, 7, 3085, 0, true}, {556, 6, 3083, 0, true}, {538, 8, 3091, 0, true}},
		npc_2 = {{566, 6, 3070, 0, true}, {569, 6, 3085, 0, true}, {581, 6, 3071, 0, true}, {578, 6, 3072, 0, true}},
		npc_3 = {{578, 6, 3092, 0, true}, {585, 6, 3082, 0, true}, {584, 6, 3102, 0, true}, {592, 6, 3097, 0, true}},
		npc_4 = {{590, 6, 3058, 0, true}, {599, 6, 3071, 0, true}, {605, 6, 3066, 0, true}, {610, 6, 3049, 0, true}, {596, 6, 3051, 0, true}},
		npc_5 = {{577, 6, 3100, 0, true}, {568, 6, 3106, 0, true}, {563, 6, 3092, 0, true}, {556, 6, 3099, 0, true}, {590, 6, 3108, 0, true}},
		npc_6 = {{616, 6, 3056, 0, true}, {610, 6, 3065, 0, true}, {617, 6, 3072, 0, true}, {609, 6, 3052, 0, true}},
	},

	mobiles = {
		--In buildings
		{"scientist",60,5.7,0.6,-6.3,-132,6955370, "conversation"},
		{"noble", 60, 3.00888, 0.125266, -2.92449, -90, 1392894, ""},
		{"businessman", 60, 6.94935, 0.624998, 2.6394, 198.079, 6955367, ""},
		{"businessman", 60, -8.09806, 0.625, 4.31086, 153.675, 6955368, ""},
		{"nirame_sakute", 60, -2.1912, 0.624999, -6.92293, 24.0649, 6955369, ""},

		--Outside
		{"businessman", 60, 594.44, 6, 3087.13, 181.146, 0, ""},
		{"businessman", 60, 614.681, 6, 3081.65, 80.4705, 0, ""},
		{"commoner", 60, 597.6, 6, 3048.5, 135, 0, "conversation"},
		{"commoner", 60, 598.679, 6, 3046.85, 315, 0, "conversation"},
		{"commoner", 60, 621.667, 6, 3092.75, 351.148, 0, ""},
		{"scientist", 60, 623.05, 6, 3037.98, 54.874, 0, ""},
		{"informant_npc_lvl_3", 0,590,6,3091,-31,0, ""},
		{"informant_npc_lvl_3", 0,598,6,3025,180,0, ""}
	}
}

registerScreenPlay("DathomirTradeOutpostScreenPlay", true)

function DathomirTradeOutpostScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
	end
end

function DathomirTradeOutpostScreenPlay:spawnMobiles()
	local mobiles = self.mobiles

	for i = 1, #mobiles, 1 do
		local mob = mobiles[i]

		-- {template, respawn, x, z, y, direction, cell, mood}
		local pMobile = spawnMobile(self.planet, mob[1], mob[2], mob[3], mob[4], mob[5], mob[6], mob[7])

		if (pMobile ~= nil) then
			if mob[8] ~= "" then
				CreatureObject(pMobile):setMoodString(mob[8])
			end

			AiAgent(pMobile):addCreatureFlag(AI_STATIC)

			if CreatureObject(pMobile):getPvpStatusBitmask() == 0 then
				CreatureObject(pMobile):clearOptionBit(AIENABLED)
			end
		end
	end
end
