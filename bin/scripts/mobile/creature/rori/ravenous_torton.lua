ravenous_torton = Creature:new {
	objectName = "@mob/creature_names:ravenous_torton",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.400000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3370,
	baseHAM = 9550,
	armor = 0,
	resists = {0,0,0,-1,-1,45,45,80,-1},
	meatType = "meat_carnivore",
	meatAmount = 1300,
	hideType = "hide_wooly",
	hideAmount = 1150,
	boneType = "bone_mammal",
	boneAmount = 1300,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ravenous_torton, "ravenous_torton")
