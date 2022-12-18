TatooineMosTaikeScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineMosTaikeScreenPlay",

	planet = "tatooine",

	gcwMobs = {
		{"stormtrooper", "rebel_crewman", 3732.4,5.6,2387.5,90,0, "", "", true},
		{"stormtrooper", "rebel_crewman", 3732.2,5.5,2382.8,90,0, "", "", true},
		{"stormtrooper", "rebel_trooper", 3759.3,8.4,2309.4,180,0, "", "", true},
		{"stormtrooper", "rebel_trooper", 3788.5,8.4,2309.9,180,0, "", "", true},
		{"scout_trooper", "rebel_scout", 3792.3,11.6,2379.2,180,0, "", "", true},
		{"stormtrooper_sniper", "rebel_resistance_separatist", 3813.2,16.1,2315.6,-137,0, "", ""},
		{"stormtrooper_bombardier", "rebel_surface_marshall", 3855.6,27.5,2325.3,-50,0, "", ""},
		{"assault_trooper_squad_leader", "alliance_intelligence_case_officer", 3858.4,27.5,2328.6,-50,0, "", "", true},
		{"assault_trooper", "rebel_major_general", 3951.7,53.5,2265.1,-114,0, "", "", true},
		{"mos_taike_cantina_owner", "mos_taike_cantina_owner_rebel", 9.6,0.4,-0.6,23,1154122, "conversation", "conversation"},
		{"mos_taike_veteran_guard", "mos_taike_veteran_guard_rebel", 3775.0,8.6,2369.7,0,0, "npc_accusing", "calm"},
	},


	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old", "commoner_tatooine"},
	stationaryNpcs = {"artisan", "brawler", "bodyguard", "bothan_diplomat", "bounty_hunter", "businessman", "chiss_female", "commoner_technician", "contractor", "criminal", "entertainer", "explorer", "farmer", "farmer_rancher", "fringer",
			"gambler", "info_broker", "medic", "mercenary", "miner", "noble", "official", "patron_ithorian", "pilot", "rancher", "scavenger", "scientist", "slicer", "shadowy_figure", "sullustan_male", "twilek_slave"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, 4.6, 1.0, 6.3, -107, 1154121, "npc_use_terminal_high"}, {1, 10.4, 0.4, 0.6, -150, 1154122, "npc_standing_drinking"}, {1, 9.0, 0.4, -9.8, 172, 1154122, "sad"}, {1, 1.0, 0.4, -4.7, 173, 1154122, "sad"},
		{1, 2.9, 0.4, 1.9, 90, 1154122, "npc_sitting_chair"}, {1, 5.9, 0.4, 1.8, -90, 1154122, "npc_sitting_chair"}, {1, 4.5, 0.4, 0.6, 0, 1154122, "npc_sitting_chair"}, {1, 9.1, 0.4, -5.1, 127, 1154122, ""},
		{1, 10.4, 0.4, 5.6, -158, 1154122, ""}, {1, -8.9, 1.0, 7.5, 89, 1154123, "npc_sitting_chair"}, {1, -8.9, 1.0, 6.6, 89, 1154123, "npc_sitting_chair"}, {1, 5.0, -4.0, -7.6, 46, 1154128, "npc_sitting_chair"},
		{1, -3.8, -4.0, 9.0, -45, 1154127, "npc_sitting_chair"}, {1, -4.3, -4.0, 8.7, 58, 1154127, "sad"}, {1, 1.7, 1.0, 4.8, -85, 1154123, "entertained"}, {1,  3860.7,  28.0,  2361.1,  180,  0, ""},
		{1, 4.9, -0.4, -3.8,  -150,  1400866, ""}, {1, 3.1, -0.4, -5.8, -45, 1400866, ""},
	},

	mobiles = {
		--misc
		{"r3",60,4.9,-4.0,-5.6,171,1154128,"neutral"},
		{"entertainer",120,-6.0,1.0,7.2,-96,1154123, "themepark_music_2"},
		{"informant_npc_lvl_1", 1, 3775, 8.7, 2371, 180, 0, ""},
		{"informant_npc_lvl_2", 1, 0.93374, 1.00421, 9.03511, 180, 1154123, ""},
		{"informant_npc_lvl_3", 1, -1.97807, -9.54192, 9.62469, -45, 1154131, ""},
		{"junk_dealer", 1, 3902.19, 33, 2362.52, -97, 0, ""},
		{"junk_nathan", 1, 3821.75, 17.51, 2343.11, 0, 0, ""}
	}
}

registerScreenPlay("TatooineMosTaikeScreenPlay", true)

function TatooineMosTaikeScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnStationaryMobiles()
		self:spawnSceneObjects()
		self:spawnGcwMobiles()
	end
end

function TatooineMosTaikeScreenPlay:spawnSceneObjects()

	--Tavern
	spawnSceneObject(self.planet, "object/static/structure/general/droid_r2_powerdown.iff", 5.5, 1.0, 10.3, 1154121, math.rad(180) )
	spawnSceneObject(self.planet, "object/static/structure/general/all_foodcart_s01.iff", -7.1, -4.0, -6.1, 1154126, math.rad(180) )
end

function TatooineMosTaikeScreenPlay:spawnMobiles()
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

	--thugs
	spawnMobile(self.planet, "scoundrel", 300, 3867.0, 27.5, 2307.5, -90, 0)
	spawnMobile(self.planet, "spice_fiend", 300, 3865.0, 27.5, 2307.5, 90, 0)
	spawnMobile(self.planet, "dune_stalker", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile(self.planet, "dune_stalker", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile(self.planet, "dune_stalker", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile(self.planet, "dune_stalker_scavenger", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile(self.planet, "dune_stalker_scavenger", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile(self.planet, "dune_stalker_scavenger", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile(self.planet, "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
	spawnMobile(self.planet, "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
	spawnMobile(self.planet, "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
	spawnMobile(self.planet, "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
	spawnMobile(self.planet, "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
	spawnMobile(self.planet, "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)

	--jawas
	spawnMobile(self.planet, "jawa_engineer", 300, 3971.5, 8.9, 2496.9, -97, 0)
	spawnMobile(self.planet, "jawa_engineer", 300, 3966.1, 9.1, 2502.9, 40, 0)
	spawnMobile(self.planet, "jawa_smuggler", 300, 3967.6, 9.0, 2503.3, -90, 0)
	spawnMobile(self.planet, "jawa_smuggler", 300, 3966.9, 9.1, 2504.5, -155, 0)
	spawnMobile(self.planet, "jawa_engineer", 300, 3974.4, 7.3, 2517.1, -161, 0)
	spawnMobile(self.planet, "jawa_smuggler", 300, 3980.9, 7.7, 2507.0, 25, 0)

	--creatures
	--[[
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)

	spawnMobile(self.planet, "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)
	spawnMobile(self.planet, "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)
	spawnMobile(self.planet, "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)
	spawnMobile(self.planet, "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)
	spawnMobile(self.planet, "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)
	spawnMobile(self.planet, "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)

	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)

	spawnMobile(self.planet, "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)

	spawnMobile(self.planet, "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	spawnMobile(self.planet, "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	]]
end
