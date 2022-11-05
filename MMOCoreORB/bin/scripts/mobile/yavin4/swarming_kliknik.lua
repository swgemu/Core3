swarming_kliknik = Creature:new {
	objectName = "@mob/creature_names:kliknik_swarming",
	socialGroup = "kliknik",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 10,
	chanceHit = 0.27,
	damageMin = 170,
	damageMax = 180,
	baseXp = 356,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {120,0,0,-1,0,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/kliknik_hue.iff",
	scale = 0.8,
	lootGroups = {
		{
			groups = {
				{group = "kliknik_common", chance = 10000000}
			},
			lootChance = 1200000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_large_yellow.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""} },
	secondaryAttacks = { {"posturedownattack",""} },
}

CreatureTemplates:addCreatureTemplate(swarming_kliknik, "swarming_kliknik")
