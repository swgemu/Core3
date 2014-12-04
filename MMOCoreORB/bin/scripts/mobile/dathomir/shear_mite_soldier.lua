shear_mite_soldier = Creature:new {
	objectName = "@mob/creature_names:shear_mite_soilder",
	socialGroup = "shear_mite",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 5500,
	armor = 0,
	resists = {125,125,10,10,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 12,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/shear_mite_soldier.iff"},
	controlDeviceTemplate = "object/intangible/pet/shear_mite_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"mildpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(shear_mite_soldier, "shear_mite_soldier")
