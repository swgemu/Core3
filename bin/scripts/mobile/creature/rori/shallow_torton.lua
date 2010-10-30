shallow_torton = Creature:new {
	objectName = "@mob/creature_names:shallow_torton",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.320000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1257,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {0,0,0,-1,-1,-1,-1,25,-1},
	meatType = "meat_carnivore",
	meatAmount = 650,
	hideType = "hide_wooly",
	hideAmount = 575,
	boneType = "bone_mammal",
	boneAmount = 650,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/shallow_torton.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(shallow_torton, "shallow_torton")