mercenary_commander = Creature:new {
	objectName = "@mob/creature_names:mercenary_commander",
	socialGroup = "lok_mercenaries",
	pvpFaction = "lok_mercenaries",
	faction = "lok_mercenaries",
	level = 42,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4188,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {45,55,30,30,30,30,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_mercenary_commander_hum_m.iff",
		"object/mobile/dressed_mercenary_commander_nikto_m.iff",
		"object/mobile/dressed_mercenary_commander_wee_m.iff",
		"object/mobile/dressed_mercenary_commander_zab_m.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3000000},
				{group = "wearables_common", chance = 1500000},
				{group = "wearables_uncommon", chance = 500000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "heavy_weapons", chance = 2000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(commandomaster,marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(mercenary_commander, "mercenary_commander")
