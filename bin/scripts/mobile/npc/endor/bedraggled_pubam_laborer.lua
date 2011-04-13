bedraggled_pubam_laborer = Creature:new {
	objectName = "@mob/creature_names:bedraggled_pubam_laborer",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {0,0,0,40,40,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(bedraggled_pubam_laborer, "bedraggled_pubam_laborer")