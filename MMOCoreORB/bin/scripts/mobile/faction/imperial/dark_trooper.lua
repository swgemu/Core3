dark_trooper = Creature:new {
	objectName = "@mob/creature_names:dark_trooper",
	randomNameType = NAME_DARKTROOPER,
	randomNameTag = false,
	mobType = MOB_ANDROID,
	socialGroup = "imperial",
	faction = "imperial",
	level = 35,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3465,
	baseHAM = 9000,
	baseHAMmax = 10000,
	armor = 0,
	resists = {40,20,20,50,50,50,50,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + OVERT,
	creatureBitmask = PACK + KILLER + NOINTIMIDATE + NODOT,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.5,

	templates = {"object/mobile/dark_trooper.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 300000},
				{group = "junk", chance = 6300000},
				{group = "rifles", chance = 600000},
				{group = "holocron_dark", chance = 150000},
				{group = "holocron_light", chance = 150000},
				{group = "carbines", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "grenades_looted", chance = 1000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "imperial_carbine",
	secondaryWeapon = "stormtrooper_sword",
	conversationTemplate = "",
	reactionStf = "@npc_reaction/stormtrooper",
	personalityStf = "@hireling/hireling_stormtrooper",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(carbineermaster,marksmanmaster),
	secondaryAttacks = merge(fencermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(dark_trooper, "dark_trooper")
