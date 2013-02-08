carnivorous_nuna = Creature:new {
	objectName = "@mob/creature_names:carnivorous_nuna",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {15,15,15,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/nuna_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(carnivorous_nuna, "carnivorous_nuna")