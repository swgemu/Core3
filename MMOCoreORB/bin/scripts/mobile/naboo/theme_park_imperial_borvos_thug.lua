theme_park_imperial_borvos_thug = Creature:new {
	objectName = "@mob/creature_names:borvos_thug",
	socialGroup = "borvo",
	pvpFaction = "borvo",
	faction = "borvo",
	level = 18,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 4100,
	baseHAMmax = 5000,
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
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_borvos_thug.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "theme_park_loot_shipping_manifest", chance = 10000000},
			},
			lootChance = 10000000
		}				
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(theme_park_imperial_borvos_thug, "theme_park_imperial_borvos_thug")
