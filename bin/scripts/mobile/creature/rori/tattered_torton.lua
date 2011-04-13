tattered_torton = Creature:new {
	objectName = "@mob/creature_names:tattered_torton",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.320000,
	damageMin = 200,
	damageMax = 210,
	baseXp = 960,
	baseHAM = 1700,
	baseHAMmax = 1700,
	armor = 0,
	resists = {0,0,0,-1,-1,-1,-1,45,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_wooly",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 1000,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/torton.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tattered_torton, "tattered_torton")