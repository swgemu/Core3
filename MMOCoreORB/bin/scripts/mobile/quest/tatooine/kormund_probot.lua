kormund_probot = Creature:new {
	objectName = "@droid_name:imperial_probot_base",
	socialGroup = "imperial",
	faction = "imperial",
	mobType = MOB_DROID,
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 0,
	baseHAM = 700,
	baseHAMmax = 900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/probot.iff"},
	lootGroups = {},
	conversationTemplate = "",

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "droid_probot_ranged",
	secondaryWeapon = "unarmed",
	defaultAttack = "attack"
}

CreatureTemplates:addCreatureTemplate(kormund_probot, "kormund_probot")