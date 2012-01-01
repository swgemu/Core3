dwarf_eopie = Creature:new {
	objectName = "@mob/creature_names:dwarf_eopie",
	socialGroup = "Eopie",
	pvpFaction = "",
	faction = "",
	level = 3,
	chanceHit = 0.23,
	damageMin = 35,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 90,
	baseHAMmax = 110,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 230,
	hideType = "hide_leathery",
	hideAmount = 180,
	boneType = "bone_mammal",
	boneAmount = 110,
	milk = 1,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dwarf_eopie.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dwarf_eopie, "dwarf_eopie")