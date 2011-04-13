mutant_rancor = Creature:new {
	objectName = "@mob/creature_names:mutant_rancor",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 75,
	chanceHit = 0.700000,
	damageMin = 495,
	damageMax = 700,
	baseXp = 7207,
	baseHAM = 13500,
	baseHAMmax = 13500,
	armor = 0,
	resists = {45,60,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 901,
	boneType = "bone_mammal",
	boneAmount = 851,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/mutant_rancor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareableeding",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_rancor, "mutant_rancor")