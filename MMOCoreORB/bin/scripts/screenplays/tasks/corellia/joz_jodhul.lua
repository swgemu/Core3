joz_jodhul_missions =
{
	{
		missionType = "assassinate",
		primarySpawns =
		{
			{ npcTemplate = "vornskr_quest_joz", npcName = "*The Beast*" }
		},
		secondarySpawns =
		{

		},
		staticObjects =
		{
			{ objectTemplate = "object/tangible/jedi/padawan_trials_skeleton.iff", objectName = "an executed Jedi Master's corpse" },
			{ objectTemplate = "object/tangible/jedi/padawan_trials_skeleton.iff", objectName = "an executed Jedi Padawan's corpse" },
			{ objectTemplate = "object/tangible/dungeon/poison_gas_cloud.iff", objectName = "poison remnants" },
			{ objectTemplate = "object/static/structure/general/skeleton_bith_headandbody.iff", objectName = "" },
			{ objectTemplate = "object/static/structure/general/skeleton_bith_headandbody.iff", objectName = "" },
			{ objectTemplate = "object/static/structure/general/skeleton_bith_headandbody.iff", objectName = "" }
		},
		itemSpawns =
		{

		},
		rewards =
		{
			{ rewardType = "credits", amount = 66 }
		}
	}
}

npcMapJozJodhul =
{
	{
		spawnData = { npcTemplate = "joz_jodhul", x = 764.1, z = 423.3, y = 5866.2, direction = 143, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/corellia/joz_jodhul",
		missions = joz_jodhul_missions
	},
}

JozJodhul = ThemeParkLogic:new {
	npcMap = npcMapJozJodhul,
	className = "JozJodhul",
	screenPlayState = "joz_jodhul_quest",
	planetName = "corellia",
	distance = 3066,
}

registerScreenPlay("JozJodhul", true)

joz_jodhul_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = JozJodhul
}
joz_jodhul_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = JozJodhul
}