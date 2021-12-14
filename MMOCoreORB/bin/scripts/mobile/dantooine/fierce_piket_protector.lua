fierce_piket_protector = Creature:new {
	objectName = "@mob/creature_names:fierce_piket_protector",
	socialGroup = "piket",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 45,
	chanceHit = 0.45,
	damageMin = 355,
	damageMax = 420,
	baseXp = 4461,
	baseHAM = 9800,
	baseHAMmax = 12000,
	armor = 0,
	resists = {150,155,-1,30,-1,30,30,30,-1},
	meatType = "meat_herbivore",
	meatAmount = 200,
	hideType = "hide_scaley",
	hideAmount = 120,
	boneType = "bone_mammal",
	boneAmount = 110,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/piket_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.15,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"dizzyattack",""}, {"blindattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(fierce_piket_protector, "fierce_piket_protector")
