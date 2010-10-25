enraged_kimogila = Creature:new {
	objectName = "@mob/creature_names:enraged_kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 135,
	chanceHit = 4.750000,
	damageMin = 920,
	damageMax = 1550,
	range = 0,
	baseXp = 12801,
	baseHAM = 55500,
	armor = 0,
	resists = {45,70,45,70,45,40,100,45,-1},
	meatType = "meat_carnivore",
	meatAmount = 1500,
	hideType = "hide_leathery",
	hideAmount = 1400,
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
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_kimogila, "enraged_kimogila")
