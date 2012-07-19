senior_specforce_lieutenant = Creature:new {
	objectName = "@mob/creature_names:senior_specforce_lieutenant",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {15,15,0,0,0,-1,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {
		{
	        groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 5700000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
                {group = "melee_weapons", chance = 1000000},
                {group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000}
			},
			lootChance = 3000000
		}	
	},
	weapons = {"imperial_weapons_heavy"},
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(senior_specforce_lieutenant, "senior_specforce_lieutenant")