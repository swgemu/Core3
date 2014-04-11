slaver = Creature:new {
	objectName = "@mob/creature_names:slaver",
	socialGroup = "slaver",
	pvpFaction = "",
	faction = "",
	level = 4,
	chanceHit = 0.240000,
	damageMin = 40,
	damageMax = 45,
	baseXp = 85,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_slaver.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 2500000},
				{group = "wearables_common", chance = 2000000},
				{group = "pistols", chance = 2000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 2000000}
			},
			lootChance = 2000000
		}			
	},
	weapons = {"pirate_weapons_light"},
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(slaver, "slaver")
