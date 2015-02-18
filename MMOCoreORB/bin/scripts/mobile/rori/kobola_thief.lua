kobola_thief = Creature:new {
	objectName = "@mob/creature_names:kobola_thief",
	socialGroup = "kobola",
	faction = "kobola",
	level = 9,
	chanceHit = 0.27,
	damageMin = 90,
	damageMax = 110,
	baseXp = 292,
	baseHAM = 405,
	baseHAMmax = 495,
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
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_kobola_thief_rodian_female_01.iff",
		"object/mobile/dressed_kobola_thief_rodian_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2400000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "kobola_common", chance = 3600000}
			},
			lootChance = 2400000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(kobola_thief, "kobola_thief")
