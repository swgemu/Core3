warren_scientist = Creature:new {
	objectName = "@mob/creature_names:warren_scientist",
	socialGroup = "warren_scientist",
	pvpFaction = "",
	faction = "",
	level = 36,
	chanceHit = 0.420000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3460,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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

	templates = {
		"object/mobile/warren_scientist_s01.iff",
		"object/mobile/warren_scientist_s02.iff",
		"object/mobile/warren_scientist_s03.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4500000},
				{group = "tailor_components", chance = 1000000},
				{group = "armor_attachments", chance = 1500000},
				{group = "clothing_attachments", chance = 1500000},
				{group = "wearables_common", chance = 1500000}
			},
			lootChance = 4800000
		}			
	},
	weapons = {},
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(warren_scientist, "warren_scientist")
