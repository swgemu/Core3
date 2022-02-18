CorelliaBelaVistalScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CorelliaBelaVistalScreenPlay",

	planet = "corellia",

	gcwMobs = {
		{"dark_trooper", 6749.3, 315, -5684, 231.007, 0, "", true},
		{"dark_trooper", 6718.1, 328.537, -5869.6, 186.005, 0, "", true},
		{"imperial_noncom", 6663.8, 330, -5913.3, 134.004, 0, "", true},
		{"scout_trooper", 6832.36, 314.758, -5811.93, 312.353, 0, ""},
		{"storm_commando", 6752.1, 315, -5823.5, 273.008, 0, ""},
		{"storm_commando", 6648.54, 330, -5939.32, 280.874, 0, ""},
		{"stormtrooper", 6852.9, 315, -5826.9, 140.004, 0, ""},
		{"stormtrooper", 6837.4, 315, -5774, 260.008, 0, ""},
		{"stormtrooper", 6819.9, 315, -5720.1, 220.006, 0, "", true},
		{"stormtrooper", 6748.9, 315, -5665.2, 279.008, 0, "", true},
		{"stormtrooper", 6855, 315, -5609.3, 280.008, 0, "", true},
		{"stormtrooper", 6685.7, 330, -5943.3, 222.007, 0, "", true},
		{"stormtrooper", 6708, 328.7, -5869.7, 166.005, 0, ""},
		{"stormtrooper_rifleman", 6845.3, 315, -5826.8, 130.004, 0, "", true},
		{"stormtrooper_bombardier", 6646.02, 330, -5931.59, 357.677, 0, "", true},
		{"stormtrooper_bombardier", 6644.26, 330, -5937.08, 5.98245, 0, ""},
		{"stormtrooper_bombardier", 6649.56, 330, -5935.6, 128.564, 0, ""},
		{"stormtrooper_captain", 6854.5, 315, -5696.6, 87, 0, "npc_imperial", true},
		{"stormtrooper_squad_leader", 6650.38, 330, -5938.43, 280.869, 0, "npc_imperial"},
		{"specialist_noncom", 6830.18, 314.823, -5816.91, 187.167, 0, "npc_imperial", true},
		{"imperial_army_captain", 6820.49, 315, -5743.53, 353.468, 0, "npc_imperial"},
		{"imperial_army_captain", 6832.21, 315, -5811.19, 189.637, 0, "npc_imperial"},
		{"imperial_sergeant", 6712.78, 315, -5810.38, 112.467, 0, "npc_imperial", true},
		{"imperial_sergeant", 6795.21, 315, -5702.92, 63.9209, 0, "npc_imperial", true},
		{"imperial_sergeant", 6823.92, 315, -5597.88, 121.846, 0, "npc_imperial", true},
		{"imperial_sergeant_major", 6908.17, 330, -5608.54, 27.4568, 0, "npc_imperial", true},
		{"imperial_staff_sergeant", 6909.29, 330, -5606.48, 204.967, 0, "npc_imperial"},
		{"stormtrooper", 6727.1, 315, -5809.9, 165, 0, "npc_imperial", true},
		{"stormtrooper", 6707.89, 315, -5814.25, 131.647, 0, "npc_imperial"},
		{"stormtrooper", 6794.42, 315, -5696.6, 90.5594, 0, "npc_imperial"},
		{"stormtrooper", 6826.7, 315, -5820.68, 309.206, 0, "npc_imperial"},
		{"stormtrooper", 6825.35, 315, -5620.37, 277.216, 0, "npc_imperial", true},
		{"stormtrooper", 6842.92, 315, -5604.11, 56.0358, 0, "npc_imperial"},
		{"stormtrooper", 6852, 315, -5831.51, 128.695, 0, "npc_imperial"},
		{"stormtrooper", 6837.95, 315, -5806.84, 302.784, 0, "npc_imperial"},
	},

	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "explorer_patrol", "noble_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"r4_1", "r4", 6715, 330, -5903, 0, 0, "", false},
		{"r2_1", "r2", 6859, 315, -5706, 0, 0, "", false},
		{"cll8_1", "cll8_binary_load_lifter", 6826, 315, -5778, 0, 0, "", false},

		--NPCs
		{"npc_1", "patrolNpc", 6846, 315, -5588, 54, 0, "", false},
		{"npc_2", "patrolNpc", 6829, 315, -5626, 119, 0, "", false},
		{"npc_3", "patrolNpc", 6755, 314, -5625, 139, 0, "", false},
		{"npc_4", "patrolNpc", 6740, 315, -5674, 168, 0, "", false},
		{"npc_5", "patrolNpc", 6761, 315, -5695, 3, 0, "", false},
		{"npc_6", "patrolNpc", 6829, 315, -5745, 171, 0, "", false},
		{"npc_7", "patrolNpc", 6808, 315, -5779, 282, 0, "", false},
		{"npc_8", "patrolNpc", 6829, 315, -5813, 319, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}

		r4_1 = {{6715, 330, -5903, 0, false}, {6693, 330, -5920, 0, false}, {6690, 330, -5906, 0, false}, {6647, 330, -5905, 0, false}},
		r2_1 = {{6858, 315, -5688, 0, false}, {6859, 315, -5700, 0, true}, {6816, 315, -5699, 0, false}, {6861, 315, -5700, 0, false}, {6859, 315, -5740, 0, true}},
		cll8_1 = {{6826, 315, -5807, 0, false}, {6825, 315, -5725, 0, false}, {6769, 315, -5725, 0, false}, {6770, 315, -5736, 0, false}, {6817, 315, -5735, 0, false}},

		npc_1 = {{6846, 315, -5588, 0, true}, {6847, 315, -5617, 0, true}, {6808, 315, -5616, 0, false}, {6830, 315, -5599, 0, true}, {6833.8, 315, -5580.4, 0, true}},
		npc_2 = {{6829, 315, -5745, 0, false}, {6818, 314, -5620, 0, false}, {6779, 314, -5620, 0, true}, {6818, 314, -5620, 0, true}},
		npc_3 = {{6755, 314, -5625, 0, false}, {6731, 315, -5588, 0, true}, {6702, 315, -5583, 0, true}, {6699, 315, -5567, 0, true}, {6723, 315, -5567, 0, false}, {6731, 315, 0, true}},
		npc_4 = {{6740, 315, -5674, 0, true}, {6742, 315, -5697, 0, true}, {6714, 315, -5692, 0, false}, {6742, 315, -5697, 0, true}},
		npc_5 = {{6761, 315, -5695, 0, true}, {6761, 315, -5731, 0, true}, {6795, 315, -5732, 0, true}, {6761, 315, -5731, 0, true}},
		npc_6 = {{6829, 315, -5745, 0, true}, {6828, 315, -5799, 0, true}},
		npc_7 = {{6808, 315, -5779, 0, true}, {6764, 315, -5779, 0, true}, {6778, 315, -5774, 0, true}, {6792, 315, -5783, 0, true}},
		npc_8 = {{6829, 315, -5813, 0, true}, {6794, 315, -5805, 0, true}, {6736, 315, -5816, 0, true}, {6778, 315, -5813, 0, true}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old"},
	stationaryNpcs = {"artisan", "bodyguard", "bothan_diplomat", "bounty_hunter", "businessman", "commoner_technician", "contractor", "entertainer", "explorer", "farmer", "farmer_rancher", "fringer", "gambler", "info_broker", "medic", "mercenary", "miner", "noble", "official", "pilot", "rancher", "scientist", "slicer"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, 6823.1, 315, -5610.5, 225, 0, "conversation"},
		{1, 6821.55, 314.999, -5611.9, 50, 0, "conversation"},
		{1, 6834.25, 315, -5577.61, 150, 0, ""},
		{1, 6896.18, 330, -5577.91, 290, 0, ""},
		{1, 6867.23, 315, -5758.29, 338, 0, ""},
		{1, 6810.15, 315, -5699.05, 137, 0, ""},
		{1, 6798.04, 315, -5731.94, 270, 0, ""},
		{1, 6724.41, 330, -5909.35, 213, 0, ""},
	},

	mobiles = {
		--Cloning Facility
		{"surgical_droid_21b",60,3.1,0.1,11.5,0,2365903, "neutral"},

		--Cantina
		{"noble", 60, 5.80982, -0.894992, -5.41349, 248.205, 3375355, ""},
		{"businessman", 60, -10.2935, -0.895782, 7.13264, 339.313, 3375355, ""},

		--Guild Hall 6857 -5783
		{"businessman", 60, 3.32, 1.13306, -8.49, 228.007, 2365769, ""},
		{"brawler", 300, -14.01, 1.13306, -8.53, 120.004, 2365770, ""},
		{"trainer_brawler", 0, -11, 1.13306, -14,0, 2365770, ""},
		{"trainer_marksman", 0, 0, 1.13306, -14, 0, 2365769, ""},

		--Guild Hall regular
		{"artisan",60,4.7,2.3,10.4,-4,2365923, "npc_use_terminal_high"},
		{"contractor",60,-8.8,1.7,-14.5,45,2365931, "npc_sitting_table_eating"},
		{"businessman",60,-5.7,1.8,-14.7,-39,2365931, "npc_sitting_chair"},

		--Hotel
		{"noble",60,18.4,1.6,12.3,180,2365808, "neutral"},
		{"bartender",60,21.2,1.6,12.3,180,2365808, "entertained"},
		{"entertainer",60,19.6,1.3,5.8,83,2365808, "happy"},
		{"sullustan_male",60,21.0,1.3,6.1,-96,2365808, "npc_sitting_chair"},
		{"commoner_technician",60,-6.7,1.0,19.5,-125,2365805, "npc_use_terminal_high"},
		{"mouse_droid",60,-6.4,1.0,16.5,103,2365806, "neutral"},

		--Outside

		{"criminal", 300, 6871.34, 315, -5753.42, 355.947, 0, ""},
		{"corsec_trooper", 360, 6847.6, 315, -5838.6, -1, 0, ""},
		{"corsec_trooper", 360, 6852.5, 315, -5838.8, -24, 0, ""},
		{"corsec_trooper", 360, 6855.7, 315, -5837.1, -34, 0, ""},
		{"corsec_trooper", 360, 6860.3, 315, -5833.9, -57, 0, ""},
		{"imperial_recruiter", 60,6718.8,315.0,-5804.6,-174,0, ""},

		--Misc
		{"informant_npc_lvl_1", 0, 20.9951, -0.894992, 21.3608, 100, 3375357, ""},
		{"informant_npc_lvl_1", 0, 6687, 315, -5594, 0, 0, ""},
		{"informant_npc_lvl_1", 0, 6733, 314.9, -5609, 90, 0, ""},
		{"informant_npc_lvl_1", 0, 6832, 315, -5545, 270, 0, ""},
		{"informant_npc_lvl_1", 0, 6901, 330, -5606, 0, 0, ""},
		{"informant_npc_lvl_2", 0, 6775, 315, -5487, 150, 0, ""},
		{"informant_npc_lvl_2", 0, 6876, 330, -5466, 0, 0, ""},
		{"informant_npc_lvl_3", 0, 6860, 315, -5761, 45 ,0, ""},

		--Trainers
		{"trainer_architect", 0, 11, 1.13306, -14, 0, 2365800, ""},
		{"trainer_armorsmith", 0, -12, 1.1, 5, 180, 2365799, ""},
		{"trainer_artisan", 0, 0, 1.13306, -14, 0, 2365947, ""},
		{"trainer_droidengineer", 0, -11, 1.13306, -14, 0, 2365802, ""},
		{"trainer_merchant", 0, 12, 1.13306, 6, 180, 2365798, ""},
		{"trainer_scout", 0, -12, 1.13306, 5.5, 180, 2365767, ""},
		{"trainer_weaponsmith", 0, -2.5, 1.13306, -8.4, 91, 2365801, ""},
		{"junk_dealer", 0, -14.2, 1.1, 2.7, 103, 2365767, ""},

		--Outside Trainers
		{"trainer_artisan", 0, 6755.99, 314.994, -5655.01, 269, 0, ""},
		{"trainer_entertainer", 0, 6829, 330, -5429, 184, 0, ""},
		{"trainer_marksman", 0,6770,315,-5714,-100,0, ""},
		{"trainer_scout", 0, 6737.85, 315, -5491.3, 31, 0, ""},
		{"trainer_scout",  0, 6724, 315, -5682, 0, 0, ""},

		{"bartender",60,8.54,-0.894992,0.14,87.0026,3375355, "neutral"},
		{"businessman",60,-6.56842,-0.894996,21.9012,135.001,3375361, "conversation"},
		{"contractor",60,-5.46842,-0.894996,21.9012,180.003,3375361, "conversation"},
		{"bounty_hunter",60,21.6023,-0.894996,-18.5913,360.011,3375356, "conversation"},
		{"comm_operator",60,-42.3991,0.105009,-24.3411,360.011,3375367, "conversation"},
		{"commoner",60,-42.3991,0.105009,-23.2411,180.016,3375367, "conversation"},
		{"info_broker",60,21.6023,-0.894996,-17.4913,180.012,3375356, "conversation"},
		{"medic",60,-43.4991,0.105009,-23.2411,135.007,3375367, "conversation"},
		{"mercenary",300,-5.46842,-0.894998,20.8012,0,3375361, "conversation"},
		{"junk_malik", 0, 6969.06, 330, -5588.66, 105, 0, ""},
		{"junk_dealer", 0, 6756.79, 315, -5779.1, 96, 0, ""}
	}
}

registerScreenPlay("CorelliaBelaVistalScreenPlay", true)

function CorelliaBelaVistalScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnSceneObjects()
		self:spawnStationaryMobiles()
		self:spawnPatrolMobiles()
		self:spawnGcwMobiles()
	end
end

function CorelliaBelaVistalScreenPlay:spawnSceneObjects()
	--Guild Hall regular
	spawnSceneObject("corellia", "object/tangible/loot/simple_kit/paint_cartridge.iff", 5.3, 2.3, 10.2, 2365923, math.rad(-19) )
	--Hotel
	spawnSceneObject("corellia", "object/static/structure/general/droid_r4_powerdown.iff", 6.0, 1.0, 20.2, 2365805, math.rad(143) )
end

function CorelliaBelaVistalScreenPlay:spawnMobiles()
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

	local pNpc = spawnMobile("corellia", "junk_dealer", 0, 6840.98, 315, -5630.49, -47, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerFineryConvoTemplate")
	end
end
