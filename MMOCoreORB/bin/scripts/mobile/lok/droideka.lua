droideka = Creature:new {
	objectName = "@mob/creature_names:droideka",
	socialGroup = "droideka",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.47,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4461,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {30,30,30,0,30,-1,30,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE +ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
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
			},
			lootChance = 3500000
		}
	},
	--weapons = {"droid_droideka_ranged"},
	conversationTemplate = "",
	defaultWeapon = "object/weapon/ranged/droid/droid_droideka_ranged.iff",
}

CreatureTemplates:addCreatureTemplate(droideka, "droideka")