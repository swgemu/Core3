diminutive_bounding_jax = Creature:new {
	objectName = "@mob/creature_names:jax_bounding_dwarf",
	socialGroup = "jax",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 7,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 187,
	baseHAM = 68,
	baseHAMmax = 83,
	armor = 0,
	resists = {110,110,-1,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 25,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bearded_jax_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/bearded_jax_hue.iff",
	scale = 0.75,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = {},
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(diminutive_bounding_jax, "diminutive_bounding_jax")
