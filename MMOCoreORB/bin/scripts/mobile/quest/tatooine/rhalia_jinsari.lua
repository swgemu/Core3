rhalia_jinsari = Creature:new {
	objectName = "",
	customName = "Rhalia Jinsari",
	socialGroup = "",
	faction = "",
	level = 30,
	chanceHit = 1,
	damageMin = 200,
	damageMax = 500,
	baseXp = 500,
	baseHAM = 7000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {20,20,10,10,10,10,10,-1,-1},
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
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_bounty_hunter_zabrak_female_01.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 7000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000}
			},
			lootChance = 2200000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(rhalia_jinsari, "rhalia_jinsari")
