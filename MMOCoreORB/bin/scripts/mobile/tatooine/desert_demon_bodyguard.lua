desert_demon_bodyguard = Creature:new {
	objectName = "@mob/creature_names:desert_demon_bodyguard",
	socialGroup = "desert_demon",
	pvpFaction = "desert_demon",
	faction = "desert_demon",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_desert_demon_bodyguard.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 5000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kits", chance = 4500000}
			},
			lootChance = 5500000
		}				
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(desert_demon_bodyguard, "desert_demon_bodyguard")
