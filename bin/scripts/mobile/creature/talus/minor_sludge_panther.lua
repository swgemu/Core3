minor_sludge_panther = Creature:new {
	objectName = "@mob/creature_names:minor_sludge_panther",
	socialGroup = "Sludge Panth.",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.280000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 900,
	baseHAMmax = 900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 20,
	hideType = "hide_leathery",
	hideAmount = 27,
	boneType = "bone_mammal",
	boneAmount = 27,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/minor_sludge_panther.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(minor_sludge_panther, "minor_sludge_panther")