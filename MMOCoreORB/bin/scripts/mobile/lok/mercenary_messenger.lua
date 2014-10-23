mercenary_messenger = Creature:new {
	objectName = "@mob/creature_names:mercenary_messanger",
	socialGroup = "lok_mercenaries",
	pvpFaction = "lok_mercenaries",
	faction = "lok_mercenaries",
	level = 21,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {20,0,0,0,0,0,-1,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_mercenary_messanger_hum_f.iff",
		"object/mobile/dressed_mercenary_messanger_hum_m.iff",
		"object/mobile/dressed_mercenary_messanger_rod_m.iff",
		"object/mobile/dressed_mercenary_messanger_sullustan_m.iff"
		},
	lootGroups = {
      	{
			groups = {
				{group = "junk", chance = 3000000},
				{group = "wearables_common", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "pistols", chance = 2000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(mercenary_messenger, "mercenary_messenger")
