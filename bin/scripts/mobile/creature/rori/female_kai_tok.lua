female_kai_tok = Creature:new {
	objectName = "@mob/creature_names:female_kai_tok",
	socialGroup = "Kai Tok",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.290000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 609,
	baseHAM = 1300,
	baseHAMmax = 1300,
	armor = 0,
	resists = {0,15,0,0,0,0,0,-1,-1},
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
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_kai_tok, "female_kai_tok")