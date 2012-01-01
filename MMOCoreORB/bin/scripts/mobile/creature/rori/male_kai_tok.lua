male_kai_tok = Creature:new {
	objectName = "@mob/creature_names:male_kai_tok",
	socialGroup = "Kai Tok",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {15,5,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 25,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kai_tok.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_green"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(male_kai_tok, "male_kai_tok")