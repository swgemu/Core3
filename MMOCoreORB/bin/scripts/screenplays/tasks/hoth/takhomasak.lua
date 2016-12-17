carboniteBase =
	{
		type = "destructible",
		buildingTemplate = "object/building/military/pirate_warehouse.iff",
		terminal = { template = "object/tangible/terminal/terminal_destructible_building.iff", vectorCellID = 3, x = 0, z = 0.3, y = -6.0 },
		childNpcs =
		{
			{ npcTemplate = "bothan_bh_tak2chiss", npcName = "Anachsko", vectorCellID = 3, x = 0, z = 0.3, y = -3.0 }
		}
	}
--ADD NEE MISSIONS TO CONNECT THIS? and then copy paste everything for IMP mirror version!
takhomasak_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "bothan_bh_tak", npcName = "a scared Bothan" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "chiss_imp_snow_agent", npcName = "an Imperial Hoth Agent" },
				{ npcTemplate = "dev_snow_merc", npcName = "a Hoth Hunter" },
				{ npcTemplate = "dev_snow_merc", npcName = "a Hoth Hunter" },
				{ npcTemplate = "dark_trooper", npcName = "" }
			},
			staticObjects =
			{
				{ objectTemplate = "object/mobile/tauntaun.iff", objectName = "a stranded Taun-Taun" },
				{ objectTemplate = "object/mobile/skeleton/tauntaun.iff", objectName = ""}
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/picture_handheld_s02.iff", itemName = "a recent image of Samanda" }
			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 100 },
			}
		},
		{
			missionType = "destroy",
			buildingSpawn = carboniteBase,
			primarySpawns =
			{
				{ npcTemplate = "imperial_probe_drone", npcName = "" }
			},
			secondarySpawns =
			{

			},
			staticObjects =
			{
				{ objectTemplate = "object/tangible/furniture/decorative/foodcart.iff", objectName = "Carbonite Generator Unit" },
				{ objectTemplate = "object/tangible/furniture/decorative/corellian_flagpole.iff", objectName = "Quadrant Marker" },
				{ objectTemplate = "object/static/structure/general/streetlamp_small_style_02_on.iff", objectName = "" }
			},
			itemSpawns =
			{

			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 200 }
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "tak_quest_samanda", npcName = "Samanda" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "grassland_slice_hound", npcName = "a Hoth Hound" },
				{ npcTemplate = "grassland_slice_hound", npcName = "a Hoth Hound" },
				{ npcTemplate = "grassland_slice_hound", npcName = "a Hoth Hound" }
			},
			itemSpawns = {},
			rewards =
			{--NEE give a MAP "relic" of HOTH datadisc?? lore from wikia link- fix itemName to override??...
				{ rewardType = "faction", faction = "rebel", amount = 300 },
				{ rewardType = "item", itemTemplate = "object/tangible/loot/misc/mystical_powered_orb.iff", itemName = "an ancient holo-map of Hoth during 'The Great War'" },
				--{ rewardType = "loot",  lootGroup = "theme_park_reward_marauder_armor_boots" } EXAMPLE reference
			}
		}
	}

npcMapTakhomasak =
	{
		{
			spawnData = { npcTemplate = "takhomasak", x = 3.5, z = -0.1, y = 4.9, direction = -122, cellID = 4265614, position = STAND },
			worldPosition = { x = 4543, y = 5146 },
			npcNumber = 1,
			stfFile = "@static_npc/hoth/rebel_intro_takhomasak",--How to get this custom homemade file to OTHER PEOPLE? so they can test it in-game, since this file is on my hd
			missions = takhomasak_missions
		},
	}

Takhomasak = ThemeParkLogic:new {
	npcMap = npcMapTakhomasak,
	className = "Takhomasak",
	screenPlayState = "takhomasak_tasks",
	planetName = "talus",
	faction = FACTIONREBEL,
	distance = 900
}

registerScreenPlay("Takhomasak", true)

takhomasak_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = Takhomasak
}
takhomasak_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = Takhomasak
}
