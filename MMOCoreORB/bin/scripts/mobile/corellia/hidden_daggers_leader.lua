hidden_daggers_leader = Creature:new {
	objectName = "@mob/creature_names:hidden_daggers_leader",
	socialGroup = "hidden_daggers",
	pvpFaction = "hidden_daggers",
	faction = "hidden_daggers",
	level = 18,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {5,15,5,-1,-1,-1,40,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_mugger.iff",
		"object/mobile/dressed_criminal_thug_human_female_01.iff",
		"object/mobile/dressed_criminal_thug_human_female_02.iff",
		"object/mobile/dressed_criminal_thug_human_male_01.iff",
		"object/mobile/dressed_criminal_thug_human_male_02.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3300000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "hidden_dagger_common", chance = 2700000},
				{group = "wearables_all", chance = 1000000},
				
			},
			lootChance = 3000000
		}
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(hidden_daggers_leader, "hidden_daggers_leader")
