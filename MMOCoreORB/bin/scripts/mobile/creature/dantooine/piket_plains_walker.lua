piket_plains_walker = Creature:new {
	objectName = "@mob/creature_names:piket_plains_walker",
	socialGroup = "Picket",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.400000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3188,
	baseHAM = 9700,
	baseHAMmax = 9700,
	armor = 0,
	resists = {40,0,0,0,0,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.200000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/piket_plains_walker.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(piket_plains_walker, "piket_plains_walker")