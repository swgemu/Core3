vir_vur_be = Creature:new {
	objectName = "@mob/creature_names:bio_engineered_vir_vur",
	socialGroup = "vir_vur",
	pvpFaction = "",
	faction = "",
	level = 2,
	chanceHit = 0.2,
	damageMin = 30,
	damageMax = 40,
	baseXp = 30,
	baseHAM = 45,
	baseHAMmax = 55,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD + STALKER,
	optionsBitmask = 0,
	diet = HERBIVORE,

	templates = {"object/mobile/vir_vur.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(vir_vur_be, "vir_vur_be")