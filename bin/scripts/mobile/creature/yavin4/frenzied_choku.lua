frenzied_choku = Creature:new {
	objectName = "@mob/creature_names:frenzied_choku",
	socialGroup = "Choku",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 1803,
	baseHAM = 5550,
	baseHAMmax = 5550,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 8,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/choku.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mediumdisease",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(frenzied_choku, "frenzied_choku")