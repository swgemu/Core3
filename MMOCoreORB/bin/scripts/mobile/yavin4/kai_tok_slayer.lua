kai_tok_slayer = Creature:new {
	objectName = "@mob/creature_names:kai_tok_slayer",
	socialGroup = "kai_tok",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 355,
	damageMax = 420,
	baseXp = 3551,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {45,0,0,0,0,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kai_tok_hue.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kai_tok_slayer, "kai_tok_slayer")