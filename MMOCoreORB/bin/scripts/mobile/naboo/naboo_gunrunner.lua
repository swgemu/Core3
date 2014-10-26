naboo_gunrunner = Creature:new {
	objectName = "@mob/creature_names:naboo_gunrunner",
	socialGroup = "naboo_pirate",
	pvpFaction = "naboo_pirate",
	faction = "naboo_pirate",
	level = 11,
	chanceHit = 0.290000,
	damageMin = 120,
	damageMax = 130,
	baseXp = 356,
	baseHAM = 1000,
	baseHAMmax = 1200,
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
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_naboo_gunrunner.iff"},
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
	weapons = {"ranged_weapons"},
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(naboo_gunrunner, "naboo_gunrunner")
