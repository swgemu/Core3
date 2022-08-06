guild_management_droid = Creature:new {
	customName = "Guild Management Droid",
	randomNameType = NAME_3P0,
	randomNameTag = true,
	socialGroup = "",
	mobType = MOB_DROID,
	faction = "",
	level = 10,
	chanceHit = 1,
	damageMin = 1,
	damageMax = 1,
	baseXp = 1,
	baseHAM = 100,
	baseHAMmax = 100,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/3po_guild_management_droid.iff"},
	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
}

CreatureTemplates:addCreatureTemplate(guild_management_droid, "guild_management_droid")