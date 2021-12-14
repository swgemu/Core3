roaming_bordok_stud = Creature:new {
	objectName = "@mob/creature_names:roaming_bordok_stud",
	socialGroup = "bordok",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 34,
	chanceHit = 0.41,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3370,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {20,-1,20,200,200,20,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 150,
	hideType = "hide_leathery",
	hideAmount = 95,
	boneType = "bone_mammal",
	boneAmount = 65,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bordok_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""}, {"dizzyattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(roaming_bordok_stud, "roaming_bordok_stud")
