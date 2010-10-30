alpha_veermok = Creature:new {
	objectName = "alpha veermok",
	socialGroup = "Veermok",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1609,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {30,0,0,-1,0,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 150,
	hideType = "hide_bristley",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/alpha_veermok.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(alpha_veermok, "alpha_veermok")