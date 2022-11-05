mad_angler = Creature:new {
	objectName = "@mob/creature_names:mad_angler",
	socialGroup = "angler",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 95,
	chanceHit = 0.85,
	damageMin = 820,
	damageMax = 1350,
	baseXp = 9057,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 0,
	resists = {150,150,20,-1,20,-1,-1,20,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "hide_scaley",
	hideAmount = 6,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/angler_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 1.4,
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_green.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"strongpoison",""}, {"blindattack",""} },
	secondaryAttacks = { {"strongpoison",""}, {"blindattack",""} },
}

CreatureTemplates:addCreatureTemplate(mad_angler, "mad_angler")
