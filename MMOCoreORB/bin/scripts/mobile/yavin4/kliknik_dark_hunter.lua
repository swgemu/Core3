kliknik_dark_hunter = Creature:new {
	objectName = "@mob/creature_names:kliknik_dark_hunter",
	socialGroup = "kliknik",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 38,
	chanceHit = 0.43,
	damageMin = 350,
	damageMax = 410,
	baseXp = 3824,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {140,140,25,-1,25,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.15,
	lootGroups = {
		{
			groups = {
				{group = "kliknik_common", chance = 10000000}
			},
			lootChance = 1760000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_yellow.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"strongpoison",""}, {"intimidationattack",""} },
	secondaryAttacks = { {"strongpoison",""}, {"intimidationattack",""} },
}

CreatureTemplates:addCreatureTemplate(kliknik_dark_hunter, "kliknik_dark_hunter")
