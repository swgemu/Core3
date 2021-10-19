dz70_crafted = Creature:new {
	objectName = "@droid_name:dz_70_fugitive_tracker_crafted",
	socialGroup = "",
	faction = "",
	level = 4,
	mobType = MOB_DROID,
	chanceHit = 0.24,
	damageMin = 112,
	damageMax = 118,
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
		"object/creature/npc/droid/crafted/dz_70_fugitive_tracker_droid.iff"
	},
	lootGroups = {},
	defaultAttack = "attack",

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "droid_probot_ranged",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
}

CreatureTemplates:addCreatureTemplate(dz70_crafted, "dz70_crafted")
