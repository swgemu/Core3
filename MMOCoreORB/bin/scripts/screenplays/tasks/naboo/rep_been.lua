rep_been_missions =
	{
		{
			missionType = "retrieve",
			primarySpawns =
			{
				{ npcTemplate = "boona_tanje", npcName = "Boona Tanje" }
			},
			secondarySpawns = {},
			itemSpawns = {
				{ itemTemplate = "object/tangible/mission/quest_item/rep_been_q1_needed.iff", itemName = "" }
			},
			rewards =
			{
				{ rewardType = "credits", amount = 50 }
			}
		},
	-- Quests 2 - 4 disabled due to missing strings in string file
	--[[
	{
	missionType = "escort",
	primarySpawns =
	{
	{ npcTemplate = "reefa_been", npcName = "" }
	},
	secondarySpawns = {
	{ npcTemplate = "bandit", npcName = "" },
	{ npcTemplate = "bandit", npcName = "" },
	{ npcTemplate = "bandit", npcName = "" },
	{ npcTemplate = "bandit", npcName = "" }
	},
	itemSpawns = {},
	rewards =
	{
	{ rewardType = "credits", amount = 50 }
	}
	},
	{
	missionType = "assassinate",
	primarySpawns =
	{
	{ npcTemplate = "bandit_leader", npcName = "" }
	},
	secondarySpawns = {
	{ npcTemplate = "bandit", npcName = "" },
	{ npcTemplate = "bandit", npcName = "" },
	{ npcTemplate = "bandit", npcName = "" }
	},
	itemSpawns = {},
	rewards =
	{
	{ rewardType = "credits", amount = 75 }
	}
	},
	{
	missionType = "escort",
	primarySpawns =
	{
	{ npcTemplate = "vajoo_jinssa", npcName = "" }
	},
	secondarySpawns = {
	{ npcTemplate = "bandit", npcName = "" },
	{ npcTemplate = "bandit", npcName = "" },
	{ npcTemplate = "bandit", npcName = "" },
	{ npcTemplate = "bandit", npcName = "" }
	},
	itemSpawns = {},
	rewards =
	{
	{ rewardType = "credits", amount = 100 }
	}
	}
	--]]
	}

npcMapRepBeen =
	{
		{
			spawnData = { npcTemplate = "rep_been", x = -1955.9, z = 5.1, y = -5458.9, direction = 157, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/rep_been",
			missions = rep_been_missions
		},
	}

RepBeen = ThemeParkLogic:new {
	npcMap = npcMapRepBeen,
	className = "RepBeen",
	screenPlayState = "rep_been_task",
	planetName = "naboo"
}

registerScreenPlay("RepBeen", true)

rep_been_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = RepBeen
}
rep_been_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = RepBeen
}
