imperial_staff_sergeant = Creature:new {
	objectName = "@mob/creature_names:imperial_staff_sergeant",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 17,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 112,
	baseHAM = 3500,
	baseHAMmax = 4300,
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

	templates = {"object/mobile/dressed_imperial_soldier_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 3600000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 4000000
		}					
	},
	weapons = {"imperial_weapons_medium"},
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(imperial_staff_sergeant, "imperial_staff_sergeant")