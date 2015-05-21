ig_assassin_droid = Creature:new {
	objectName = "@mob/creature_names:ig_assassin_droid",
	socialGroup = "",
	faction = "",
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
	optionsBitmask = 0,
	diet = NONE,

	templates = {"object/mobile/ig_assassin_droid.iff"},
	lootGroups = {
	     {
			groups = {
				{group = "junk", chance = 6500000},
				{group = "nyms_common", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "tailor_components", chance = 500000}
			}
		}
	},
	conversationTemplate = "",
	defaultWeapon = "object/weapon/ranged/droid/droid_droideka_ranged.iff",
	defaultAttack = "creaturerangedattack"
}

CreatureTemplates:addCreatureTemplate(ig_assassin_droid, "ig_assassin_droid")
