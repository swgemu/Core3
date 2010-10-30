deranged_mantigrue = Creature:new {
	objectName = "deranged mantigrue",
	socialGroup = "Mantigrue",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.440000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4279,
	baseHAM = 9800,
	baseHAMmax = 9800,
	armor = 0,
	resists = {50,45,70,-1,70,70,70,70,-1},
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
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(deranged_mantigrue, "deranged_mantigrue")