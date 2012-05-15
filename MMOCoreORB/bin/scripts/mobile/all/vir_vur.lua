vir_vur = Creature:new {
	objectName = "@mob/creature_names:vir_vur",
	socialGroup = "vir_vur",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 292,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 4,
	milk = 0,
	tamingChance = 0.25,
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

CreatureTemplates:addCreatureTemplate(vir_vur, "vir_vur")