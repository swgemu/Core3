naboo_dread_pirate = Creature:new {
	objectName = "@mob/creature_names:naboo_dread_pirate",
	socialGroup = "naboo_pirate",
	pvpFaction = "naboo_pirate",
	faction = "naboo_pirate",
	level = 22,
	chanceHit = 0.350000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2006,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {0,0,0,0,0,-1,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = { "object/mobile/dressed_criminal_pirate_human_male_01.iff" },
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 2000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000}
			},
			lootChance = 3200000
		}					
	},
	weapons = {"pirate_weapons_heavy"},
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(naboo_dread_pirate, "naboo_dread_pirate")
