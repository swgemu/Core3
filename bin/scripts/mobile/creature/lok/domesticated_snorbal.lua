domesticated_snorbal = Creature:new {
	objectName = "@mob/creature_names:domesticated_snorbal",
	socialGroup = "Domestic Snor.",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.390000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 3005,
	baseHAM = 9600,
	baseHAMmax = 9600,
	armor = 0,
	resists = {40,40,0,-1,-1,-1,-1,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 545,
	hideType = "hide_leathery",
	hideAmount = 440,
	boneType = "bone_mammal",
	boneAmount = 400,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/snorbal.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(domesticated_snorbal, "domesticated_snorbal")