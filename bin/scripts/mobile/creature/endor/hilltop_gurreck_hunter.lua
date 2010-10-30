hilltop_gurreck_hunter = Creature:new {
	objectName = "@mob/creature_names:hilltop_gurreck_hunter",
	socialGroup = "Gurreck",
	pvpFaction = "",
	faction = "",
	level = 41,
	chanceHit = 0.420000,
	damageMin = 340,
	damageMax = 390,
	baseXp = 4006,
	baseHAM = 9600,
	baseHAMmax = 9600,
	armor = 0,
	resists = {50,65,0,0,0,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/gurreck.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(hilltop_gurreck_hunter, "hilltop_gurreck_hunter")