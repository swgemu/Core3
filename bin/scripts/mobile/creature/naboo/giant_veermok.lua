giant_veermok = Creature:new {
	objectName = "@mob/creature_names:giant_veermok",
	socialGroup = "Veermok",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {25,20,0,-1,45,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 250,
	hideType = "hide_bristley",
	hideAmount = 200,
	boneType = "bone_mammal",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_veermok.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_veermok, "giant_veermok")