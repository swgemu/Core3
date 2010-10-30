quenker_ravager = Creature:new {
	objectName = "@mob/creature_names:quenker_ravager",
	socialGroup = "Quenker",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.430000,
	damageMin = 365,
	damageMax = 440,
	baseXp = 3824,
	baseHAM = 10100,
	baseHAMmax = 10100,
	armor = 0,
	resists = {0,0,0,0,-1,-1,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/quenker.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"creatureareapoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(quenker_ravager, "quenker_ravager")