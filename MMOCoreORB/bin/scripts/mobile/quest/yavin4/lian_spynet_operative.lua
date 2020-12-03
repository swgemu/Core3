lian_spynet_operative = Creature:new {
	objectName = "@mob/creature_names:spynet_operative",
	socialGroup = "spynet",
	faction = "",
	level = 17,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	optionsBitmask = AIENABLED + CONVERSABLE,
	pvpBitmask = ATTACKABLE + ENEMY + AGGRESSIVE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = { "commoner" },
	lootGroups = {
		{
			groups = {
				{group = "task_loot_lian_byrne_rebel_spy_report", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "lian_byrne_mission_target_convotemplate",
	attacks = merge(marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(lian_spynet_operative, "lian_spynet_operative")
