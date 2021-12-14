woolamander_harvester = Creature:new {
	objectName = "@mob/creature_names:woolamander_harvester",
	socialGroup = "woolamander",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 38,
	chanceHit = 0.43,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3733,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 0,
	resists = {25,25,-1,180,180,180,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 20,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/woolamander_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.1,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"creatureareaattack",""}, {"dizzyattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(woolamander_harvester, "woolamander_harvester")
