nym_patrol_weak = Creature:new {
	objectName = "@mob/creature_names:nym_patrol_weak",
	socialGroup = "nym",
	pvpFaction = "nym",
	faction = "nym",
	level = 33,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3370,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {35,40,25,25,40,-1,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/dressed_nym_patrol_weak_hum_f.iff", 
				"object/mobile/dressed_nym_patrol_weak_rod_m.iff",
				"object/mobile/dressed_nym_patrol_weak_nikto_m.iff",
				"object/mobile/dressed_nym_patrol_weak_hum_m.iff"},
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
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(nym_patrol_weak, "nym_patrol_weak")