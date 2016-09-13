megan_drlar_missions =
	{
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "salvager_quest_megan", npcName = "a Salvage Worker" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "scavenger", npcName = "" },
				{ npcTemplate = "scavenger", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 75 }
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "scavenger_quest_megan", npcName = "Scavenger Thief" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "scavenger", npcName = "" },
				{ npcTemplate = "scavenger", npcName = "" }
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/megan_drlar_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 100 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "scavenger_quest_megan2", npcName = "Scavenger Leader" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "scavenger", npcName = "" },
				{ npcTemplate = "scavenger", npcName = "" },
				{ npcTemplate = "scavenger", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "credits", amount = 150 },
			}
		}
	}

npcMapMeganDrlar =
	{
		{
			spawnData = { npcTemplate = "megan_drlar", x = 5855.7, z = 32.6, y = -336.5, direction = -144, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/yavin/yavin_salvagecamp_megan_drlar",
			missions = megan_drlar_missions
		},
	}

MeganDrlar = ThemeParkLogic:new {
	npcMap = npcMapMeganDrlar,
	className = "MeganDrlar",
	screenPlayState = "megan_drlar_tasks",
	planetName = "yavin4",
	distance = 700
}

registerScreenPlay("MeganDrlar", true)

megan_drlar_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = MeganDrlar
}
megan_drlar_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = MeganDrlar
}
