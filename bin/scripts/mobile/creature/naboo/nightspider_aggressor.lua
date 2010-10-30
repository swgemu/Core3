nightspider_aggressor = Creature:new {
	objectName = "@mob/creature_names:nightspider_aggressor",
	socialGroup = "Nightspider",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.270000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 750,
	baseHAMmax = 750,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 5,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/nightspider_aggressor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(nightspider_aggressor, "nightspider_aggressor")