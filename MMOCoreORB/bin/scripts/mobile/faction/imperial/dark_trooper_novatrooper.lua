dark_trooper_novatrooper = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_dark_trooper_novatrooper",
	socialGroup = "imperial",
	faction = "imperial",
	mobType = MOB_ANDROID,
	level = 200,
	chanceHit = 18,
	damageMin = 1270,
	damageMax = 2250,
	baseXp = 21700,
	baseHAM = 208000,
	baseHAMmax = 254000,
	armor = 2,
	resists = {95,85,80,30,0,0,30,45,-1},--kinetic,energy,blast,heat,cold,electric,acid,stun,ls
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER + NOINTIMIDATE + NODOT,
	optionsBitmask = AIENABLED,
	diet = NONE,
	scale = 1.3,

	templates = {"object/mobile/dressed_stormtrooper_black_black.iff"},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "imperial_carbine",
	secondaryWeapon = "stormtrooper_sword",
	thrownWeapon = "thrown_weapons",

	conversationTemplate = "",
	reactionStf = "@npc_reaction/stormtrooper",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(carbineermaster,marksmanmaster),
	secondaryAttacks = merge(fencermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(dark_trooper_novatrooper, "dark_trooper_novatrooper")
