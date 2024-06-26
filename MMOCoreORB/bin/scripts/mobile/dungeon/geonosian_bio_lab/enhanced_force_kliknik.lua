enhanced_force_kliknik = Creature:new {
	objectName = "",
	customName = "Force Kliknik",
	socialGroup = "geonosian_creature",
	mobType = MOB_CARNIVORE,
	faction = "",
	level = 94,
	chanceHit = 0.95,
	damageMin = 610,
	damageMax = 930,
	baseXp = 8964,
	baseHAM = 22000,
	baseHAMmax = 27000,
	armor = 2,
	resists = {35,35,0,95,-1,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 45,
	hideType = "hide_scaley",
	hideAmount = 40,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 15,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_hue.iff"},
	scale = 1.45,
	lootGroups = {
		{
			groups = {
				{group = "geo_kliknik", chance = 10000000}
			},
			lootChance = 2880000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_heavy_flame.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"stunattack",""}, {"creatureareaattack",""} },
	secondaryAttacks = { {"stunattack",""}, {"creatureareaattack",""} }
}

CreatureTemplates:addCreatureTemplate(enhanced_force_kliknik, "enhanced_force_kliknik")
