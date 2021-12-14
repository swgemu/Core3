theme_park_rebel_nym_contact = Creature:new {
	objectName = "@mob/creature_names:nym_pirate_strong",
	socialGroup = "nym",
	faction = "nym",
	mobType = MOB_NPC,
	level = 26,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2730,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {25,10,25,25,25,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = INVULNERABLE + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_nym_pirate_strong_hum_f.iff", 
				"object/mobile/dressed_nym_pirate_strong_rod_m.iff",
				"object/mobile/dressed_nym_pirate_strong_nikto_m.iff",
				"object/mobile/dressed_nym_pirate_strong_hum_m.iff",
				"object/mobile/dressed_nym_pirate_strong_rod_f.iff",
				"object/mobile/dressed_nym_pirate_strong_wee_m.iff"},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "pirate_weapons_heavy",
	secondaryWeapon = "unarmed",
	conversationTemplate = "theme_park_rebel_mission_target_convotemplate",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(theme_park_rebel_nym_contact, "theme_park_rebel_nym_contact")