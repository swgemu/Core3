screaming_kai_tok = Creature:new {
	objectName = "@mob/creature_names:screaming_kai_tok",
	socialGroup = "Kai Tok",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.320000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 3200,
	baseHAMmax = 3200,
	armor = 0,
	resists = {20,10,35,45,45,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 25,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kai_tok.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_green"},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(screaming_kai_tok, "screaming_kai_tok")