TatooineStaticSpawnsNorthScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("TatooineStaticSpawnsNorthScreenPlay", true)

function TatooineStaticSpawnsNorthScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function TatooineStaticSpawnsNorthScreenPlay:spawnMobiles()

	--Ruins + Bounty Hunter Camp (7045,7042)
	local pNpc = spawnMobile("tatooine", "bounty_hunter_thug", 360, 7039.0, 72.2, 7051.5, -125, 0)
	self:setMoodString(pNpc, "neutral")
	spawnMobile("tatooine", "bounty_hunter_thug", 360, 7034.1, 71.6, 7052.1, 131, 0)
	spawnMobile("tatooine", "bounty_hunter_thug", 360, 7051.6, 70.6, 7038.0, -10, 0)

	--Broken Walls (2980,6465)
	spawnMobile("tatooine", "desert_demon_bodyguard", 300, 2991.2, 46.5, 6460.1, 60, 0)
	spawnMobile("tatooine", "desert_demon_bodyguard", 300, 2990.4, 46.5, 6466.1, 90, 0)
	spawnMobile("tatooine", "desert_demon_bodyguard", 300, 2981.2, 48.1, 6465.4, -60, 0)
	spawnMobile("tatooine", "desert_demon_leader", 300, 2982.8, 47.1, 6459.2, 0, 0)
	spawnMobile("tatooine", "desert_demon_marksman", 300, 2973.7, 47.8, 6444.8, 180, 0)
	spawnMobile("tatooine", "desert_demon_brawler", 300, 2973.7, 49.0, 6454.5, 0, 0)
	spawnMobile("tatooine", "desert_demon_brawler", 300, 2969.3, 50.8, 6462.5, -30, 0)
	--Four Stone Arches (358,6568)
	--Marker + Skulls (1226,6031)
	pNpc = spawnMobile("tatooine", "twilek_slave", 60, 1226.5, 78.4, 6031.6, -114, 0)
	self:setMoodString(pNpc, "npc_sitting_ground")
	--Animal Skeleton (-2829,6057)
	spawnMobile("tatooine", "mound_mite", 300, -2829.7, 278.7, 6057.2, 33, 0)
	spawnMobile("tatooine", "mound_mite", 300, -2827.5, 277.3, 6059.7, -51, 0)

	--Skeletons on a Pole (-4824,6530)
	spawnMobile("tatooine", "tusken_death_hunter", 420, -4831.2, 27.2, 6531.9, 99, 0)
	spawnMobile("tatooine", "tusken_raid_hunter", 420, -4825.7, 26.7, 6536.0, 165, 0)
	spawnMobile("tatooine", "tusken_bantha", 300, -4842.1, 25.9, 6548.1, 135, 0)

	--Ruins + Skeletons (-5723,6483)
	spawnMobile("tatooine", "armodragon", 300, -5724.6, 23.4, 6483.3, 141, 0)
	--Skeletons (-6275,6015)
	--Escape Pod + Gravestones (-6174,5886)
	pNpc = spawnMobile("tatooine", "bounty_hunter", 60, -6175.3, 31.1, 5884.7, 100, 0)
	self:setMoodString(pNpc, "sad")

	--Krayt Skeleton (-6205,5054)
	spawnMobile("tatooine", "canyon_krayt_dragon", 1800, -6216.0, 30.8, 5033.9, 63, 0)
	spawnMobile("tatooine", "juvenile_canyon_krayt_dragon", 1500, 6213.8, 31.0, 5021.3, 63, 0)
	--Gravestones + Weeping Tree (-6196,5108)
	--Krayt Skeleton (-5808,5401)
	--Standing Stones (-5231,5233)
	spawnMobile("tatooine", "rockmite", 300, -5236.9, 51.3, 5240.4, -119, 0)

	--Broken Machinery & camp (-4698,5456)
	spawnMobile("tatooine", "weequay_thug", 300, -4692.8, 31.1, 5458.5, 45, 0)
	spawnMobile("tatooine", "weequay_zealot", 300, -4693.3, 29.8, 5465.9, 95, 0)
	spawnMobile("tatooine", "domestic_eopie", 300, -4687.1, 29.1, 5473.6, 125, 0)

	--Makeshift Camp (-4464,5784)
	spawnMobile("tatooine", "dune_stalker_scavenger", 300, -4464.7, 33.0, 5784.5, 45, 0)
	spawnMobile("tatooine", "dune_stalker_scavenger", 300, -4469.9, 33.0, 5786.4, -75, 0)

	--Alkhara camp (-1261,5463)
	spawnMobile("tatooine", "alkhara_lieutenant", 300, -1258.4, 10.7, 5464.9, 65, 0)
	spawnMobile("tatooine", "alkhara_bandit", 300, -1265.6, 10.0, 5464.7, 115, 0)
	spawnMobile("tatooine", "alkhara_bandit", 300, -1264.2, 9.8, 5459.1, 15, 0)
	--4 stone pillars (3487,4124)
	--Square Frame (6528,5522)
	--Oasis (6663,5455)
	spawnMobile("tatooine", "dwarf_nuna", 300, 6655.4, 1.1, 5468.2, 125, 0)
	spawnMobile("tatooine", "dwarf_nuna", 300, 6659.1, 1.1, 5471.5, 125, 0)
	spawnMobile("tatooine", "dwarf_nuna", 300, 6663.7, 1.1, 5475.0, 115, 0)
	spawnMobile("tatooine", "dwarf_nuna", 300, 6665.6, 1.1, 5485.4, 145, 0)
	spawnMobile("tatooine", "dwarf_nuna", 300, 6675.8, 1.1, 5473.4, 175, 0)
	spawnMobile("tatooine", "cu_pa", 300, 6677.8, 1.3, 5445.0, -45, 0)

	--Giant Krayt (5728,3784)
	spawnMobile("tatooine", "giant_canyon_krayt_dragon", 1800, 5728.5, 56.6, 3784.7, 35, 0)
	--Stone Frame (5457,2142)
	--Broken House (2315,3255)
	--Arches (-844,2704)
	--Buried Building + Flag (-2041,2593)
	pNpc = spawnMobile("tatooine", "commoner_tatooine", 60, -2044.5, 9.1, 2603.0, 160, 0)
	self:setMoodString(pNpc, "sad")
	--Buried Walls & Tents (-2294,2936)
	--Ranchers Camp (-3168,3638)
	spawnMobile("tatooine", "rancher", 300, -3165.8, 10.8, 3639.1, 39, 0)
	spawnMobile("tatooine", "domestic_eopie", 300, -3176.5, 11.3, 3643.7, 95, 0)
	spawnMobile("tatooine", "domestic_eopie", 300, -3176.5, 11.7, 3650.7, 95, 0)

	--Ruined Building + Camp (-4878,2950)
	spawnMobile("tatooine", "alkhara_bandit", 300, -4873.9, 93.4, 2945.7, 85, 0)
	spawnMobile("tatooine", "alkhara_bandit", 300, -4881.9, 94.8, 2956.5, -165, 0)
	spawnMobile("tatooine", "alkhara_bandit", 300, -4877.9, 94.6, 2951.1, -165, 0)

	--Rocks With Fire on Top (-6112,3966)
	spawnMobile("tatooine", "wonderous_cu_pa", 600, -6111.3, 190.1, 3965.6, -69, 0)

	--Krayt Skeleton (-6750,3569)
	spawnMobile("tatooine", "krayt_dragon_grand", 1800, -6718.3, 175.6, 3499.6, 80, 0)
	spawnMobile("tatooine", "krayt_dragon_grand", 1800, -6796.1, 194.0, 3514.6, 175, 0)
	spawnMobile("tatooine", "krayt_dragon_adolescent", 1800, -6789.0, 127.7, 3661.2, -104, 0)
	--Rock Pillar with Flag on top (-6449,2614)
	spawnMobile("tatooine", "volatile_scyk", 600, -6440.7, 252.2, 2610.2, -43, 0)
	--Hunter Camp (-6890,1507)
	spawnMobile("tatooine", "hunter", 300, -6893.4, 68.7, 1509.4, -86, 0)

	--Comms Dish (-5467,2138)
	spawnMobile("tatooine", "imperial_probe_drone", 300, -5461.3, 209.0, 2137.9, -124, 0)

	--Pirate Camp (-4931,1260)
	spawnMobile("tatooine", "pirate_privateer", 300, getRandomNumber(13) + -4959, 9.7, getRandomNumber(18) + 1265, getRandomNumber(360), 0)
	spawnMobile("tatooine", "pirate_privateer", 300, getRandomNumber(13) + -4959, 9.7, getRandomNumber(18) + 1265, getRandomNumber(360), 0)
	spawnMobile("tatooine", "pirate_privateer", 300, getRandomNumber(13) + -4959, 9.7, getRandomNumber(18) + 1265, getRandomNumber(360), 0)
	spawnMobile("tatooine", "pirate_privateer", 300, getRandomNumber(13) + -4959, 9.7, getRandomNumber(18) + 1265, getRandomNumber(360), 0)
	spawnMobile("tatooine", "pirate_privateer", 300, -4921.3, 10.2, 1262.1, 6, 0)

	--Debris (-2128,675)
	spawnMobile("tatooine", "scavenger", 300, -2120.7, 6.8, 683.2, -104, 0)

	--Wreckage (-1480,988)
	spawnMobile("tatooine", "scavenger", 300, -1493, 26.5, 990.2, 150, 0)

	--3 small Buildings (-170,1930)
	spawnMobile("tatooine", "tusken_commoner", 300, -169.3, 152.2, 1931.0, -122, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, -157.1, 155.8, 1930.2, -122, 0)

	local pWarrior = spawnMobile("tatooine", "tusken_warrior", 720, -189.9, 157.6, 1930.7, -90, 0)
	createObserver(OBJECTDESTRUCTION, "TatooineStaticSpawnsNorthScreenPlay", "notifyWarriorDead", pWarrior)

	--Building Ruins, Balcony and Stairs (576,353)
	spawnMobile("tatooine", "jawa", 300,579.1,160.5,355.3,179,0)
	spawnMobile("tatooine", "jawa", 300,578.9,160.5,352.9,4,0)
	spawnMobile("tatooine", "jawa", 300,596.6,153.4,340.7,-13,0)
	spawnMobile("tatooine", "jawa", 300,596.5,153.4,342.4,168,0)
	spawnMobile("tatooine", "jawa", 300,592,146.8,353.5,-1,0)
	spawnMobile("tatooine", "jawa", 300,591.9,146.8,356.3,175,0)
	spawnMobile("tatooine", "jawa", 300,603.2,141.3,363.9,174,0)
	spawnMobile("tatooine", "jawa", 300,603.4,141.3,359.2,-4,0)
	--Debris (1093,861)
	--3 Arches (1855,1465)
	--2 small buildings (5100,596)
	spawnMobile("tatooine", "ig_assassin_droid", 3600, 5090.1, 21.5, 591.3, 114, 0)
	spawnMobile("tatooine", "seeker", 600, 5102.3, 23.6, 592.6, 138, 0)
	--Building Ruins (6395,195)
	spawnMobile("tatooine", "sunstained_dune_lizard", 600, 6383.5, 64.5, 190.5, -54, 0)

end

function TatooineStaticSpawnsNorthScreenPlay:notifyWarriorDead(pWarrior, pKiller)
	if (readData("TatooineStaticSpawnsNorthScreenPlay:tusken_warlord") == 0) then
		local pWarlord = spawnMobile("tatooine", "tusken_warlord", 0, -160.3, 156.1, 1923.4, 0, 0)
		spawnMobile("tatooine", "tusken_sniper", 0, -183.2, 157.5, 1920.6, 15, 0)
		spawnMobile("tatooine", "tusken_gore_chief", 0, -159.6, 146.6, 1941.2, -55, 0)

		createObserver(OBJECTDESTRUCTION, "TatooineStaticSpawnsNorthScreenPlay", "notifyWarlordDead", pWarlord)
		writeData("TatooineStaticSpawnsNorthScreenPlay:tusken_warlord",1)
	end

	return 0
end

function TatooineStaticSpawnsNorthScreenPlay:notifyWarlordDead(pWarlord, pKiller)
	deleteData("TatooineStaticSpawnsNorthScreenPlay:tusken_warlord")

	return 1
end
