ig_assassin_droid = Creature:new {
	objectName = "@mob/creature_names:ig_assassin_droid",
	socialGroup = "",
	faction = "",
	mobType = MOB_ANDROID,
	level = 21,
	chanceHit = 0.33,
	damageMin = 220,
	damageMax = 230,
	baseXp = 1803,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {125,125,5,5,5,-1,5,-1,-1},
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
	creatureBitmask = KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = NONE,

	templates = {"object/mobile/ig_assassin_droid.iff"},
	lootGroups = {
	     {
			groups = {
				{group = "lok_droid_tier_1", chance = 10000000}
			}
		}
	},
	conversationTemplate = "",
	defaultWeapon = "object/weapon/ranged/droid/droid_droideka_ranged.iff",
	defaultAttack = "attack"
}

CreatureTemplates:addCreatureTemplate(ig_assassin_droid, "ig_assassin_droid")
