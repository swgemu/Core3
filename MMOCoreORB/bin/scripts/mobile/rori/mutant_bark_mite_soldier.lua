mutant_bark_mite_soldier = Creature:new {
	objectName = "@mob/creature_names:mutant_bark_mite_soldier",
	socialGroup = "mite",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.33,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {130,130,-1,120,120,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 25,
	hideType = "hide_scaley",
	hideAmount = 20,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite.iff"},
	scale = 2.5,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_bark_mite_soldier, "mutant_bark_mite_soldier")
