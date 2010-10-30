kimogila_hatchling = Creature:new {
	objectName = "kimogila hatchling",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.330000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {0,0,0,55,0,0,100,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 700,
	hideType = "hide_leathery",
	hideAmount = 625,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kimogila_hatchling.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kimogila_hatchling, "kimogila_hatchling")