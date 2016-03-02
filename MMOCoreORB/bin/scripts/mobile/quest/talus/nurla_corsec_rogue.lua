nurla_corsec_rogue = Creature:new {
	objectName = "@mob/creature_names:corsec_rogue",
	socialGroup = "corsec",
	faction = "corsec",
	level = 17,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = KILLER + PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dressed_mercenary_weak_hum_m.iff",
			"object/mobile/dressed_mercenary_weak_rod_m.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "corsec_weapons", chance = 2500000},
				{group = "wearables_common", chance = 2000000},
				{group = "tailor_components", chance = 1500000}
			}
		}
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(nurla_corsec_rogue, "nurla_corsec_rogue")
