imperial_second_lieutenant = Creature:new {
	objectName = "@mob/creature_names:imperial_second_lieutenant",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1805,
	baseHAM = 5000,
	baseHAMmax = 6100,
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_lieutenant_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 3600000},
				{group = "rifles", chance = 300000},
				{group = "pistols", chance = 300000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000}
			},
			lootChance = 4000000
		}						
	},
	weapons = {"imperial_weapons_medium"},
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(imperial_second_lieutenant, "imperial_second_lieutenant")