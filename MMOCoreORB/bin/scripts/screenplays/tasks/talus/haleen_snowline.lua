haleen_snowline_missions =
	{
		{
			missionType = "deliver",
			primarySpawns =
			{
				{ npcTemplate = "haleen_reactionist", planetName = "talus", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "haleen_thug", planetName = "talus", npcName = "a Thug" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/haleen_snowline_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "confiscate",
			primarySpawns =
			{
				{ npcTemplate = "haleen_activist", planetName = "talus", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "haleen_reactionist2", planetName = "talus", npcName = "" },
				{ npcTemplate = "haleen_reactionist2", planetName = "talus", npcName = "" },
			},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/mission/quest_item/haleen_snowline_q2_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 40 },
			}
		}
	}

npcMapHaleenSnowline =
	{
		{
			spawnData = { planetName = "talus", npcTemplate = "haleen_snowline", x = -0.1, z = 3.12, y = 19.3, direction = 0, cellID = 6255466, position = STAND },
			worldPosition = { x = 683, y = -3152 },
			npcNumber = 1,
			stfFile = "@static_npc/talus/talus_dearic_haleen_snowline",
			missions = haleen_snowline_missions
		},
	}

HaleenSnowline = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapHaleenSnowline,
	className = "HaleenSnowline",
	screenPlayState = "haleen_snowline_quest",
	distance = 800,
	missionCompletionMessageStf = "@theme_park/messages:static_completion_message",
}

registerScreenPlay("HaleenSnowline", true)

haleen_snowline_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = HaleenSnowline
}
haleen_snowline_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = HaleenSnowline
}