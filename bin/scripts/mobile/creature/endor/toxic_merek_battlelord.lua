toxic_merek_battlelord = Creature:new {
	objectName = "@mob/creature_names:toxic_merek_battlelord",
	socialGroup = "Merek",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.470000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4461,
	baseHAM = 10800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {40,-1,60,60,50,60,80,50,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/merek.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(toxic_merek_battlelord, "toxic_merek_battlelord")