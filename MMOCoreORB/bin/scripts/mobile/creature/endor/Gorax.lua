Gorax = Creature:new {
	objectName = "Gorax",
	socialGroup = "Gorax ",
	pvpFaction = "",
	faction = "",
	level = 300,
	chanceHit = 30.000000,
	damageMin = 1645,
	damageMax = 3000,
	baseXp = 28549,
	baseHAM = 428000,
	armor = 0,
	resists = {65,45,0,0,0,0,0,0,-1},
	meatType = "meat_",
	meatAmount = 0,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareaattack",""},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(Gorax, "Gorax")
