--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
TalusStaticSpawnsSouthScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TalusStaticSpawnsSouthScreenPlay",

	lootContainers = {


	},

	lootLevel = 14,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 700000},
				{group = "junk", chance = 7500000},
				{group = "rifles", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000}
			},
			lootChance = 8000000
		}
	},

	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("TalusStaticSpawnsSouthScreenPlay", true)

function TalusStaticSpawnsSouthScreenPlay:start()
	if (isZoneEnabled("talus")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function TalusStaticSpawnsSouthScreenPlay:spawnMobiles()

	--Flag & Ruins (-3804,-6500)
	spawnMobile("talus", "fed_dub_captain", 300, -3811.6, 1.1, -6490.9, 88, 0)
	spawnMobile("talus", "fed_dub_investigator", 300, -3802.4, 0.7, -6495.2, -175, 0)
	spawnMobile("talus", "fed_dub_investigator", 300, -3795.7, 6.0, -6474.4, 75, 0)

	--Camp (-3380,-6014)
	spawnMobile("talus", "selonian_assassin", 300, -3384.5, 38.5, -6011.6, -177, 0)
	spawnMobile("talus", "selonian_assassin", 300, -3382.9, 38.1, -6017.2, 73, 0)
	spawnMobile("talus", "selonian_raider", 300, -3375.7, 37.9, -6013.4, 90, 0)

	--Selonian Camp (145,-5583)
	spawnSceneObject("talus", "object/static/installation/mockup_power_generator_wind_style_1.iff", 153.2, 30.7, -5576.6, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/soundobject/soundobject_wind_power_generator.iff", 153.2, 30.7, -5576.6, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/static/vehicle/e3/landspeeder.iff", 130.6, 31.5, -5583.2, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/static/structure/corellia/corl_tent_large.iff", 145.15, 30.7, -5584.1, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/static/structure/corellia/corl_imprv_column_s02.iff", 137.1, 31.1, -5576.6, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/static/structure/corellia/corl_imprv_wall_4x16_s01.iff", 145.15, 30.3, -5576.6, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/static/particle/pt_flocking_glowzees.iff", 155.1, 30.4, -5585.9, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/tangible/camp/camp_lantern_s3.iff", 155.1, 30.4, -5585.9, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/tangible/camp/camp_cot_s1.iff", 142.7, 30.8, -5580.0, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/tangible/camp/camp_cot_s1.iff", 142.7, 30.8, -5584.0, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/tangible/camp/camp_cot_s1.iff", 142.7, 30.8, -5588.0, 0, 1, 0, 0, 0)
	spawnSceneObject("talus", "object/tangible/camp/campfire_logs_burnt.iff", 160.0, 30.6, -5601.8, 0, 1, 0, 0, 0)

	spawnMobile("talus", "selonian_healer", 300, 135.4, 31.1, -5579.5, -140, 0)
	spawnMobile("talus", "selonian_raider", 300, 125.6, 31.4, -5593.7, -110, 0)
	spawnMobile("talus", "selonian_hunter", 300, 134.6, 31.3, -5600.1, 0, 0)
	spawnMobile("talus", "selonian_raider", 300, 147.1, 31.0, -5604.9, 90, 0)
	spawnMobile("talus", "selonian_scout", 300, 158.8, 30.7, -5604.4, 0, 0)
	spawnMobile("talus", "selonian_sentinel", 300, 159.6, 30.6, -5599.3, 160, 0)
	spawnMobile("talus", "selonian_raider", 300, 163.6, 30.9, -5602.2, -90, 0)
	spawnMobile("talus", "selonian_raider", 300, 150.1, 30.4, -5592.5, -60, 0)
	spawnMobile("talus", "selonian_warlord", 300, 142.5, 30.8, -5585.1, 140, 0)
	spawnMobile("talus", "selonian_warrior", 300, 147.3, 30.7, -5580.9, 130, 0)
	spawnMobile("talus", "selonian_warrior", 300, 158.2, 30.4, -5585.9, 90, 0)
	spawnMobile("talus", "selonian_assassin", 300, 157.5, 30.6, -5576.4, -90, 0)

	--Rebel Instalation (2378,-4984)
	spawnMobile("talus", "rebel_army_captain", 360, -4.4, 0.1, -3.5, 90, 9645417)
	spawnMobile("talus", "rebel_medic", 360, 3.7, 0.1, -3.7, -90, 9645416)
	spawnMobile("talus", "rebel_trooper", 360, 0.0, 0.1, -4.8, 0, 9645414)
	spawnMobile("talus", "rebel_trooper", 360, 3.9, 0.1, 1.6, -90, 9645415)
	spawnMobile("talus", "rebel_trooper", 360, 0.0, 0.1, 4.2, 180, 9645412)
	spawnMobile("talus", "rebel_trooper", 360, 2384.6, 125.3, -4989.8, 180, 0)
	spawnMobile("talus", "rebel_trooper", 360, 2372.8, 125.7, -4989.8, 180, 0)
	spawnMobile("talus", "rebel_trooper", 360, 2353.9, 125.4, -5004.1, -90, 0)

	--Tie Debris (4850,-4720)

	--Rebel Camp (3100,-4044)
	spawnMobile("talus", "rebel_trooper", 360, 3106.9, 65.8, -4057.9, 180, 0)
	spawnMobile("talus", "rebel_trooper", 360, 3102.9, 65.8, -4057.9, 180, 0)
	spawnMobile("talus", "rebel_trooper", 360, 3129.3, 65.6, -4043.5, 90, 0)
	spawnMobile("talus", "rebel_trooper", 360, 3129.3, 65.6, -4039.5, 90, 0)
	spawnMobile("talus", "rebel_trooper", 360, 3101.3, 65.9, -4013.7, 0, 0)
	spawnMobile("talus", "rebel_trooper", 360, 3097.3, 65.9, -4013.7, 0, 0)
	spawnMobile("talus", "specforce_technician", 360, 3107.4, 65.8, -4034.0, -135, 0)
	spawnMobile("talus", "specforce_technician", 360, 3100.7, 65.8, -4048.9, 0, 0)

	--Debris (-1011,-5092)

	--Supply Drop (-3363,-3813)

	--Small Moisture Farm (-4916,-4510)
	spawnMobile("talus", "commoner_technician", 360, -4914.8, 5.0, -4510.7, 180, 0)
	spawnMobile("talus", "commoner_technician", 360, -4919.0, 5.0, -4506.9, 160, 0)

	--Generator (-5647,-2370)
	spawnMobile("talus", "frenzied_fynock_guardian", 360, -5650.7, 76.6, -2377.3, 15, 0)
	spawnMobile("talus", "fynock", 360, -5640.7, 86.0, -2373.5, -70, 0)
	spawnMobile("talus", "fynock", 360, -5639.3, 86.0, -2364.4, -127, 0)
	spawnMobile("talus", "fynock", 360, -5647.3, 76.2, -2365.1, -166, 0)

	--Wind Generatos (-4557,-2906)

	--Campsite (-2716,-2265)
	spawnMobile("talus", "rebel_commando", 360, -2713.4, 32.9, -2263.3, 60, 0)
	spawnMobile("talus", "rebel_commando", 360, -2716.2, 32.6, -2273.2, -130, 0)

	--Broken AT-AT (-2434,-2218)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -2446.4, 35.2, -2206.6, 145, 0)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -2445.0, 34.2, -2233.7, 54, 0)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -2429.7, 36.8, -2246.8, -5, 0)
	spawnMobile("talus", "fynock", 300, -2415.8, 33.9, -2229.6, -75, 0)
	spawnMobile("talus", "jungle_fynock", 300, -2427.2, 35.0, -2208.3, -129, 0)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -2442.0, 35.3, -2199.7, 165, 0)
	spawnMobile("talus", "jungle_fynock", 300, -2445.3, 35.2, -2207.2, 130, 0)
	spawnMobile("talus", "clipped_fynock", 300, -2445.7, 35.0, -2213.1, -90, 0)
	spawnMobile("talus", "clipped_fynock", 300, -2446.1, 34.8, -2219.8, 178, 0)
	spawnMobile("talus", "fynock", 300, -2450.7, 34.8, -2221.4, -109, 0)
	spawnMobile("talus", "fynock", 300, -2450.5, 35.0, -2214.9, 102, 0)
	spawnMobile("talus", "jungle_fynock", 300, -2436.7, 34.2, -2234.0, 33, 0)
	spawnMobile("talus", "clipped_fynock", 300, -2436.8, 34.8, -2242.5, -169, 0)
	spawnMobile("talus", "jungle_fynock", 300, -2430.2, 34.2, -2240.9, 73, 0)

	--Debris (-1729,-2886)

	--Bridge (18,-2523)

	--Picnic Site (-485,-2073)
	spawnMobile("talus", "sleemo_scamp", 300, -488.0, 40.3, -2074.6, 10, 0)
	spawnMobile("talus", "sleemo_vandal", 300, -486.7, 40.1, -2070.6, 90, 0)

	--Cantina General (117,-1925) (bugged building here with no appearance)

	--Arch & Torches (1467,-2672)

	--Quarantined Building (3886,-2848)

	--Building Ruins with Camp (5190,-1735)
	spawnMobile("talus", "lost_aqualish_commando", 300, 5189.4, 30.9, -1748.9, -90, 0)
	spawnMobile("talus", "lost_aqualish_bomber", 300, 5185.5, 31.3, -1740.5, -10, 0)
	spawnMobile("talus", "lost_aqualish_commando", 300, 5194.9, 31.2, -1725.1, -110, 0)
	spawnMobile("talus", "lost_aqualish_captain", 300, 5190.0, 31.7, -1718.3, -175, 0)
	
	--Imperial House (5985,-1185)
	spawnMobile("talus", "imperial_first_lieutenant", 300, 5947.4, 0.7, -1192.1, -108, 0)
	spawnMobile("talus", "imperial_trooper", 300, 5963.3, 2.1, -1192.7, 158, 0)

	--Hunters camp (1115,-1769)
	spawnMobile("talus", "hunter", 300, 1115.0, 27.3, -1761.6, 0, 0)

	--Lost Aqualish House (17,-910)
	spawnMobile("talus", "lost_aqualish_warchief", 300, 17.7, 6.2, -912.7, -45, 0)
	spawnMobile("talus", "lost_aqualish_marksman", 300, 13.7, 5.6, -920.3, 0, 0)
	spawnMobile("talus", "lost_aqualish_lookout", 300, 6.5, 5.8, -892.6, -57, 0)

	--Ruins (-1600,-540)

	--Broken Strut (-1650,-330)

	--Fountain (-3153,-922)

	--Aakuan Awning (-3686,-553)
	spawnMobile("talus", "aakuan_defender", 300, -3686.8, 34.7, -558.9, 57, 0)
	spawnMobile("talus", "aakuan_keeper", 300, -3691.3, 34.8, -555.2, -40, 0)
	spawnMobile("talus", "aakuan_defender", 300, -3690.3, 35.0, -548.8, 67, 0)
	spawnMobile("talus", "aakuan_guardian", 300, -3683.0, 35.2, -546.9, -57, 0)

	--Pillars (-4975,-590)

	--Rock Formation (-5877,-178)

	--Antenna (-6027,-1192)

end
