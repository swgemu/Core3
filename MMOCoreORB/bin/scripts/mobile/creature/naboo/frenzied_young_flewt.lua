frenzied_young_flewt = Creature:new {
	objectName = "@mob/creature_names:frenzied_young_flewt",
	socialGroup = "Flewt",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 1,
	hideType = "hide_leathery",
	hideAmount = 1,
	boneType = "bone_avian",
	boneAmount = 1,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/flewt.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(frenzied_young_flewt, "frenzied_young_flewt")