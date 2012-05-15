imperial_inquisitor = Creature:new {
	objectName = "@mob/creature_names:imperial_inquisitor",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 120,
	chanceHit = 4.000000,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 11296,
	baseHAM = 44000,
	baseHAMmax = 54000,
	armor = 0,
	resists = {50,50,50,0,50,0,50,50,-1},
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

	templates = {"object/mobile/dressed_imperial_inquisitor_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 3600000},
				{group = "rifles", chance = 2000000},
				{group = "pistols", chance = 2000000},
				{group = "clothing_attachments", chance = 1100000},
				{group = "armor_attachments", chance = 1100000}
			},
			lootChance = 4000000
		}				
	},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(imperial_inquisitor, "imperial_inquisitor")