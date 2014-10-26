desert_demon_marksman = Creature:new {
	objectName = "@mob/creature_names:desert_demon_marksman",
	socialGroup = "desert_demon",
	pvpFaction = "desert_demon",
	faction = "desert_demon",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_desert_demon_marksman.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 2500000},
				{group = "wearables_common", chance = 2000000},				
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "printer_parts", chance = 1000000},
				{group = "desert_demon_common", chance = 1500000}
			},
			lootChance = 2200000
		}				
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(desert_demon_marksman, "desert_demon_marksman")
