zeelius_kraymunder_missions =
{
	{ 
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "hermit_spider", npcName = "Hermit Spider" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 25 }
		}
	},
	{
		missionType = "escort", 
		primarySpawns = 
		{ 
			{ npcTemplate = "zeelius_partner", npcName = "Zeelius' Partner" } 
		}, 
		secondarySpawns = {
			{ npcTemplate = "gundark_rogue", npcName = "Card Player" },
			{ npcTemplate = "gundark_hooligan", npcName = "Card Player" }
}, 
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 50 }
		}
	},
}

npcMapZeeliusKraymunder = 
{ 
	{ 
		spawnData = { npcTemplate = "zeelius_kraymunder", x = -5318.6, z = 80.5, y = -2264.9, direction = 76, cellID = 0, position = STAND }, 
		npcNumber = 1,   
		stfFile = "@static_npc/rori/rori_narmle_zeelius_kraymunder", 
		missions = zeelius_kraymunder_missions 
	},
}

ZeeliusKraymunder = ThemeParkLogic:new {
	npcMap = npcMapZeeliusKraymunder,
	className = "ZeeliusKraymunder",
	screenPlayState = "zeelius_kraymunder_task",
	planetName = "rori",
	distance = 800
}

registerScreenPlay("ZeeliusKraymunder", true)

zeelius_kraymunder_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = ZeeliusKraymunder
}
zeelius_kraymunder_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = ZeeliusKraymunder
}
