erran_sif = Creature:new {
	objectName = "@mob/creature_names:erran_sif",
	socialGroup = "sif",
	pvpFaction = "sif",
	faction = "sif",
	level = 67,
	chanceHit = 0.67,
	damageMin = 480,
	damageMax = 670,
	baseXp = 6472,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {20,20,20,20,20,20,20,20,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_erran_sif.iff"},
	lootGroups = {},
	weapons = {"sif_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(erran_sif, "erran_sif")