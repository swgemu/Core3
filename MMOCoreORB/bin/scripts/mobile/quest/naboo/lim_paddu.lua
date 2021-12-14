lim_paddu = Creature:new {
	objectName = "@mob/creature_names:gungan_priest",
	customName = "Lim Paddu",
	socialGroup = "gungan",
	mobType = MOB_NPC,
	faction = "gungan",
	level = 16,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {15,15,15,15,15,15,15,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/gungan_s02_male.iff"},
	conversationTemplate = "pooja_naberrie_mission_target_convotemplate",

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "rebel_weapons_medium",
	secondaryWeapon = "unarmed",
  	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlernovice,marksmannovice),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(lim_paddu, "lim_paddu")
