mutant_baz_nitch = Creature:new {
	objectName = "@mob/creature_names:mutant_baz_nitch",
	socialGroup = "baz_nitch",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3097,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {20,20,20,20,20,20,20,20,-1},
	meatType = "meat_wild",
	meatAmount = 30,
	hideType = "hide_leathery",
	hideAmount = 25,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mutant_baz_nitch.iff"},
	controlDeviceTemplate = "object/intangible/pet/nuna_hue.iff",
	scale = 1.15,
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_baz_nitch, "mutant_baz_nitch")
