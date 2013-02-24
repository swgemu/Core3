deranged_mantigrue = Creature:new {
	objectName = "@mob/creature_names:deranged_mantigrue",
	socialGroup = "mantigrue",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4279,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 1,
	resists = {25,25,100,25,100,100,100,100,-1},
	meatType = "meat_carnivore",
	meatAmount = 80,
	hideType = "hide_wooly",
	hideAmount = 50,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(deranged_mantigrue, "deranged_mantigrue")
