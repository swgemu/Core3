rebel_first_mate = Creature:new {
	objectName = "@mob/creature_names:corvette_rebel_mate",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 86,
	chanceHit = 0.85,
	damageMin = 570,
	damageMax = 850,
	baseXp = 8223,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 0,
	resists = {45,35,0,0,30,30,80,65,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_rebel_first_lieutenant_bothan_male_01.iff"},
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
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(rebel_first_mate, "rebel_first_mate")