criminal_quest_zekka = Creature:new {
	objectName = "@mob/creature_names:criminal",
	socialGroup = "thug",
	faction = "thug",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_thug_bothan_male_01.iff"},
	lootGroups = {
		{
			groups = {
					{group = "task_loot_datadisc_quest_zekka", chance = 10000000}
				},
			lootChance = 10000000
		}
	},
	weapons = {},
	conversationTemplate = "blk_sun_tasks_mission_target_convotemplate",
	attacks = merge(brawlermaster, teraskasinovice)
}

CreatureTemplates:addCreatureTemplate(criminal_quest_zekka, "criminal_quest_zekka")
