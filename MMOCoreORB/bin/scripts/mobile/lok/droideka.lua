droideka = Creature:new {
	objectName = "@mob/creature_names:droideka",
	socialGroup = "droideka",
	faction = "",
	level = 39,
	chanceHit = 0.44,
	damageMin = 370,
	damageMax = 450,
	baseXp = 3824,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {30,30,30,-1,30,-1,30,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/droideka.iff"},
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
	defaultAttack = "attack",
}

CreatureTemplates:addCreatureTemplate(droideka, "droideka")
