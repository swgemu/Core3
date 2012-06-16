dwarf_gronda = Creature:new {
	objectName = "@mob/creature_names:dwarf_gronda",
	socialGroup = "gronda",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {20,20,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 280,
	hideType = "hide_leathery",
	hideAmount = 170,
	boneType = "bone_mammal",
	boneAmount = 90,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/dwarf_gronda.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dwarf_gronda, "dwarf_gronda")