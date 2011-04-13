adult_pygmy_torton = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_adult",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.310000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {20,20,0,0,0,-1,-1,100,-1},
	meatType = "meat_carnivore",
	meatAmount = 600,
	hideType = "hide_wooly",
	hideAmount = 400,
	boneType = "bone_mammal",
	boneAmount = 600,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/torton.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(adult_pygmy_torton, "adult_pygmy_torton")