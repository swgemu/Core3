deranged_mantigrue = Creature:new {
	objectName = "@mob/creature_names:deranged_mantigrue",
	socialGroup = "mantigrue",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4279,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {150,145,170,-1,170,170,170,170,-1},
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
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(deranged_mantigrue, "deranged_mantigrue")
