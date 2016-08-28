gavyn_sykes_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "zim_zam_blattis", npcName = "Zim Zam Blattis" }
			},
			secondarySpawns = {},
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
				{ npcTemplate = "large_berzerk_ikopi", npcName = "Large Berzerk Ikopi" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		},
		{
			missionType = "escort",
			primarySpawns =
			{
				{ npcTemplate = "haf_mandrox", npcName = "Haf Mandrox" }
			},
			secondarySpawns = {
				{ npcTemplate = "gungan_thug", npcName = "Gungan Thug" },
				{ npcTemplate = "gungan_thug", npcName = "Gungan Thug" },
				{ npcTemplate = "gungan_thug", npcName = "Gungan Thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 150 }
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "gungan_leader", npcName = "Gungan Leader" }
			},
			secondarySpawns = {
				{ npcTemplate = "gungan_thug", npcName = "Gungan Thug" },
				{ npcTemplate = "gungan_thug", npcName = "Gungan Thug" },
				{ npcTemplate = "gungan_thug", npcName = "Gungan Thug" }
			},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 200 }
			}
		}
	}

npcMapGavynSykes =
	{
		{
			spawnData = { npcTemplate = "gavyn_sykes", x = 8.5, z = 0.6, y = 66.7, direction = 110, cellID = 2125382, position = STAND },
			worldPosition = { x = 1419.1, y = 2761.7 },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/gavyn_sykes",
			missions = gavyn_sykes_missions
		},
	}

GavynSykes = ThemeParkLogic:new {
	npcMap = npcMapGavynSykes,
	className = "GavynSykes",
	screenPlayState = "gavyn_sykes_task",
	planetName = "naboo",
	distance = 800,
}

registerScreenPlay("GavynSykes", true)

gavyn_sykes_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = GavynSykes
}
gavyn_sykes_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = GavynSykes
}
