pygmy_torton_protector = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_protector",
	socialGroup = "torton",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 22,
	chanceHit = 0.33,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2219,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {125,125,5,5,5,-1,-1,145,-1},
	meatType = "meat_carnivore",
	meatAmount = 600,
	hideType = "hide_wooly",
	hideAmount = 400,
	boneType = "bone_mammal",
	boneAmount = 600,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/torton_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = .55,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"knockdownattack",""}, {"dizzyattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(pygmy_torton_protector, "pygmy_torton_protector")
