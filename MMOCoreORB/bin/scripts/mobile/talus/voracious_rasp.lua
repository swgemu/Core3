voracious_rasp = Creature:new {
	objectName = "@mob/creature_names:voracious_rasp",
	socialGroup = "rasp",
	faction = "",
	level = 40,
	chanceHit = 0.47,
	damageMin = 445,
	damageMax = 600,
	baseXp = 4006,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 1,
	resists = {0,0,-1,-1,0,-1,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 60,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/plumed_rasp.iff"},
	scale = 1.35,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"blindattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(voracious_rasp, "voracious_rasp")
