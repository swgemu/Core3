roba_pack_leader = Creature:new {
	objectName = "roba pack leader",
	socialGroup = "Roba",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3005,
	baseHAM = 9000,
	baseHAMmax = 9000,
	armor = 0,
	resists = {0,0,0,60,-1,60,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/roba.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(roba_pack_leader, "roba_pack_leader")