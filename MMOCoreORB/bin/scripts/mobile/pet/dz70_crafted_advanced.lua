dz70_crafted_advanced = Creature:new {
	objectName = "@droid_name:dz_70_fugitive_tracker_crafted_advanced",
	socialGroup = "",
	faction = "",
	level = 4,
	chanceHit = 0.24,
	damageMin = 129,
	damageMax = 136,
	baseXp = 0,
	baseHAM = 3000,
	baseHAMmax = 3200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/creature/npc/droid/crafted/dz_70_fugitive_tracker_droid_advanced.iff"
	},
	lootGroups = {},
	defaultAttack = "attack",
	weapons = {"droid_probot_ranged"},
	conversationTemplate = "",
}

CreatureTemplates:addCreatureTemplate(dz70_crafted_advanced, "dz70_crafted_advanced")
