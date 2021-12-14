warren_imperial_officer = Creature:new {
	objectName = "@mob/creature_names:warren_imperial_officer",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "warren_imperial",
	faction = "",
	level = 27,
	chanceHit = 0.37,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2730,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {25,25,0,-1,-1,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/warren_imperial_officer_s01.iff",
		"object/mobile/warren_imperial_officer_s02.iff",
		"object/mobile/warren_imperial_officer_s03.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6200000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "imperial_officer_common", chance = 450000},
				{group = "wearables_common", chance = 1000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "imperial_weapons_medium",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlermaster,marksmanmaster,carbineermaster,riflemanmaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(warren_imperial_officer, "warren_imperial_officer")
