bull_rancor = Creature:new {
	objectName = "@mob/creature_names:bull_rancor",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 65,
	chanceHit = 0.600000,
	damageMin = 455,
	damageMax = 620,
	baseXp = 6288,
	baseHAM = 12500,
	baseHAMmax = 12500,
	armor = 0,
	resists = {35,60,0,80,80,80,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 900,
	boneType = "bone_mammal",
	boneAmount = 850,
	milk = 0,
	tamingChance = 0.010000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/bull_rancor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareadisease",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bull_rancor, "bull_rancor")