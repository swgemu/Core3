
captain_eso_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "swamp_trooper", npcName = "Squad Leader" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "recon_men_quest_eso", npcName = "" },
				{ npcTemplate = "recon_men_quest_eso", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 10 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "imperial_medic", npcName = "an Imperial Field Medic" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" }
			},
			staticObjects =
			{
				{ objectTemplate = "object/tangible/item/quest/force_sensitive/bacta_tank.iff" },
				{ objectTemplate = "object/tangible/furniture/decorative/bacta_tank.iff" },
				{ objectTemplate = "object/tangible/medicine/medpack_revive.iff" },
				{ objectTemplate = "object/tangible/camp/camp_cot_s3.iff" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 15 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "deranged_rebel_quest_eso", npcName = "a Deranged Rebel" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 20 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "scout_trooper", npcName = "Jungle Trooper" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 25 },
			}
		}
	}

npcMapCaptainEso =
	{
		{
			spawnData = { npcTemplate = "captain_eso", x = 1593.0, z = 102.0, y = 1535.1, direction = 160, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/yavin/eso",
			missions = captain_eso_missions
		},
	}

CaptainEso = ThemeParkLogic:new {
	npcMap = npcMapCaptainEso,
	className = "CaptainEso",
	screenPlayState = "captain_eso_tasks",
	planetName = "yavin4",
	distance = 700,
	faction = FACTIONREBEL
}

registerScreenPlay("CaptainEso", true)

captain_eso_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = CaptainEso
}
captain_eso_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = CaptainEso
}
