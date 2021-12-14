rancor = Creature:new {
	objectName = "@mob/creature_names:rancor",
	socialGroup = "rancor",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 50,
	chanceHit = 0.5,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4916,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {130,130,-1,160,160,160,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 877,
	boneType = "bone_mammal",
	boneAmount = 777,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/rancor_hue.iff",
	lootGroups = {
		{
			groups = {
				{group = "rancor_common", chance = 4000000},
				{group = "armor_all", chance = 2000000},
				{group = "weapons_all", chance = 2500000},
				{group = "wearables_all", chance = 1500000}
			},
			lootChance = 2000000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"stunattack",""}, {"intimidationattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(rancor, "rancor")
