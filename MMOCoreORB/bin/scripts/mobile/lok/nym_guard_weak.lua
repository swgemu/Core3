nym_guard_weak = Creature:new {
	objectName = "@mob/creature_names:nym_guard_weak",
	socialGroup = "nym",
	pvpFaction = "nym",
	faction = "nym",
	level = 36,
	chanceHit = 0.410000,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3642,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {35,35,0,0,40,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_nym_guard_weak_hum_f.iff", 
				"object/mobile/dressed_nym_guard_weak_rod_m.iff",
				"object/mobile/dressed_nym_guard_weak_nikto_m.iff",
				"object/mobile/dressed_nym_guard_weak_hum_m.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "nyms_common", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 3500000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(nym_guard_weak, "nym_guard_weak")