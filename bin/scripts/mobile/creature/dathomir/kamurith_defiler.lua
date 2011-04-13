kamurith_defiler = Creature:new {
	objectName = "@mob/creature_names:kamurith_defiler",
	socialGroup = "Kamurith",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4916,
	baseHAM = 10700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 90,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/voritor_lizard.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(kamurith_defiler, "kamurith_defiler")