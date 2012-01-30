voracious_rasp = Creature:new {
	objectName = "@mob/creature_names:voracious_rasp",
	socialGroup = "Voracious Rasp",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.47,
	damageMin = 445,
	damageMax = 600,
	baseXp = 4006,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_avian",
	meatAmount = 60,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/plumed_rasp.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(voracious_rasp, "voracious_rasp")