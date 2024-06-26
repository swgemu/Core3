rogue_falumpaset = Creature:new {
	objectName = "@mob/creature_names:rogue_falumpaset",
	socialGroup = "self",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 18,
	chanceHit = 0.32,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,110,5,-1,-1,-1,5,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 190,
	hideType = "hide_leathery",
	hideAmount = 110,
	boneType = "bone_mammal",
	boneAmount = 80,
	milkType = "milk_wild",
	milk = 100,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/falumpaset_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.1,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_large_toxicgreen.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"stunattack",""} },
	secondaryAttacks = { {"stunattack",""} }
}

CreatureTemplates:addCreatureTemplate(rogue_falumpaset, "rogue_falumpaset")
