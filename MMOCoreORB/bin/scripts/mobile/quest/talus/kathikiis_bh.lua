kathikiis_bh = Creature:new {
	objectName = "",
	socialGroup = "lok_mercenaries",
	faction = "lok_mercenaries",
	level = 44,
	chanceHit = 0.47,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4370,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 1,
	resists = {0,0,0,0,0,-1,0,0,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_mercenary_warlord_hum_m.iff",
		"object/mobile/dressed_mercenary_warlord_nikto_m.iff",
		"object/mobile/dressed_mercenary_warlord_wee_m.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4100000},
				{group = "tailor_components", chance = 1000000},
				{group = "color_crystals", chance = 400000},
				{group = "power_crystals", chance = 400000},
				{group = "melee_unarmed", chance = 600000},
				{group = "melee_polearm", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "rifles", chance = 600000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000},
				{group = "wearables_common", chance = 500000}
			}
		}
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,commandomaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(kathikiis_bh, "kathikiis_bh")
