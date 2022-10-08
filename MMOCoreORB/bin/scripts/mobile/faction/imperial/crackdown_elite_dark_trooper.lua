crackdown_elite_dark_trooper = Creature:new {
	objectName = "@mob/creature_names:crackdown_elite_dark_trooper",
	randomNameType = NAME_DARKTROOPER,
	randomNameTag = false,
	mobType = MOB_ANDROID,
	socialGroup = "imperial",
	faction = "imperial",
	level = 1,
	chanceHit = 0.64,
	damageMin = 465,
	damageMax = 640,
	baseXp = 45,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {0,0,0,30,-1,30,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER + NOINTIMIDATE,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.5,
	customAiMap = "crackdown",

	templates = {"object/mobile/dark_trooper.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7650000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
                {group = "melee_weapons", chance = 550000},
                {group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000}
			},
			lootChance = 2800000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "imperial_carbine",
	secondaryWeapon = "stormtrooper_sword",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = carbineermaster,
	secondaryAttacks = fencermaster
}

CreatureTemplates:addCreatureTemplate(crackdown_elite_dark_trooper, "crackdown_elite_dark_trooper")
