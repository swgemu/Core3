mountain_vesp = Creature:new {
	objectName = "@mob/creature_names:mountain_vesp",
	socialGroup = "vesp",
	faction = "",
	level = 24,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2443,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {135,10,120,-1,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 11,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/vesp_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/vesp_hue.iff",
	scale = 0.95,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"blindattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_vesp, "mountain_vesp")
