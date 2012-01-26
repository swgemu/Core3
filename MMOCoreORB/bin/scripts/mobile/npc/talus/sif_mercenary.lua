sif_mercenary = Creature:new {
	objectName = "@mob/creature_names:trandoshan_sif",
	socialGroup = "Sif",
	pvpFaction = "Sif",
	faction = "",
	level = 36,
	chanceHit = 0.42,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3642,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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

	templates = {},
	lootgroups = {},
	weapons = {"sif_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(sif_mercenary, "sif_mercenary")