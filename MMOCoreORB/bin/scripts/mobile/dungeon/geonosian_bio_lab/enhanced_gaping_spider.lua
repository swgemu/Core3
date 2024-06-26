enhanced_gaping_spider = Creature:new {
	objectName = "@mob/creature_names:geonosian_gaping_spider_fire",
	customName = "Fire Breathing Spider",
	socialGroup = "geonosian_creature",
	mobType = MOB_CARNIVORE,
	faction = "",
	level = 108,
	chanceHit = 2.5,
	damageMin = 715,
	damageMax = 1140,
	baseXp = 10267,
	baseHAM = 32000,
	baseHAMmax = 39000,
	armor = 2,
	resists = {150,10,-1,195,-1,10,10,10,-1},
	meatType = "meat_insect",
	meatAmount = 50,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider.iff"},
	scale = 2.5,
	lootGroups = {
		{
			groups = {
				{group = "fire_breathing_spider", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_heavy_flame.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"strongpoison",""}, {"stunattack",""} },
	secondaryAttacks = { {"strongpoison",""}, {"stunattack",""} }
}

CreatureTemplates:addCreatureTemplate(enhanced_gaping_spider, "enhanced_gaping_spider")
