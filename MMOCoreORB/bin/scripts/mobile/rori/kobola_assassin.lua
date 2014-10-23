kobola_assassin = Creature:new {
	objectName = "@mob/creature_names:kobola_assassin",
	socialGroup = "kobola",
	pvpFaction = "kobola",
	faction = "kobola",
	level = 18,
	chanceHit = 0.32,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1426,
	baseHAM = 2500,
	baseHAMmax = 3200,
	armor = 0,
	resists = {20,10,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_kobola_assassin_zabrak_male_01.iff",
		"object/mobile/dressed_kobola_assassin_zabrak_female_01.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 2400000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "kobola_common", chance = 3600000}
			},
			lootChance = 2500000
		}					
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(kobola_assassin, "kobola_assassin")
