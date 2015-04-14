neo_cobral_boss = Creature:new {
	objectName = "@mob/creature_names:cobral_boss",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "cobral",
	faction = "cobral",
	level = 30,
	chanceHit = 0.38,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3097,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {0,0,0,40,40,40,40,-1,-1},
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
		"object/mobile/dressed_cobral_boss_twk_female_01.iff",
		"object/mobile/dressed_cobral_boss_twk_male_01.iff"},

	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2000000},
				{group = "wearables_all", chance = 2000000},
				{group = "carbines", chance = 2000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000}
			},
			lootChance = 3200000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(neo_cobral_boss, "neo_cobral_boss")
