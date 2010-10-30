reptilian_life_stealer = Creature:new {
	objectName = "reptilian life stealer",
	socialGroup = "Reptilian Flier",
	pvpFaction = "",
	faction = "",
	level = 125,
	chanceHit = 3.250000,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 11859,
	baseHAM = 38000,
	baseHAMmax = 38000,
	armor = 0,
	resists = {0,25,5,100,100,-1,0,0,-1},
	meatType = "meat_avian",
	meatAmount = 135,
	hideType = "hide_leathery",
	hideAmount = 90,
	boneType = "bone_avian",
	boneAmount = 85,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/reptilian_flier.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(reptilian_life_stealer, "reptilian_life_stealer")