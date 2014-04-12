nym_droideka = Creature:new {
	objectName = "@mob/creature_names:nym_droideka_strong",
	socialGroup = "nym",
	pvpFaction = "nym",
	faction = "nym",
	level = 45,
	chanceHit = 0.47,
	damageMin = 360,
	damageMax = 430,
	baseXp = 4461,
	baseHAM = 9900,
	baseHAMmax = 12100,
	armor = 1,
	resists = {30,45,25,25,40,-1,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/droideka.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4500000},
				{group = "wearables_uncommon", chance = 2000000},
				{group = "nyms_common", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 3500000
		}
	},
	defaultAttack = "creaturerangedattack",
	defaultWeapon = "object/weapon/ranged/droid/droid_droideka_ranged.iff",
}

CreatureTemplates:addCreatureTemplate(nym_droideka, "nym_droideka")