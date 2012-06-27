weequay_thug = Creature:new {
	objectName = "@mob/creature_names:weequay_thug",
	socialGroup = "weequay",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 356,
	baseHAM = 675,
	baseHAMmax = 825,
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_weequay_thug.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 6000000},
				{group = "tailor_components", chance = 5500000},
				{group = "loot_kit_parts", chance = 1500000}
			},
			lootChance = 2200000
		}				
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(weequay_thug, "weequay_thug")