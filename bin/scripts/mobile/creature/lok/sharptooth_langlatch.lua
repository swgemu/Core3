sharptooth_langlatch = Creature:new {
	objectName = "@mob/creature_names:sharptooth_langlatch",
	socialGroup = "Langlatch",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 3200,
	baseHAMmax = 3200,
	armor = 0,
	resists = {0,15,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 16,
	hideType = "hide_wooly",
	hideAmount = 16,
	boneType = "bone_mammal",
	boneAmount = 16,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/langlatch.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sharptooth_langlatch, "sharptooth_langlatch")