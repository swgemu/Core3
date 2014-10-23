imperial_retreat_guard = Creature:new {
	objectName = "@mob/creature_names:imperial_retreat_guard",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 72,
	chanceHit = 0.75,
	damageMin = 520,
	damageMax = 750,
	baseXp = 6931,
	baseHAM = 1200,
	baseHAMmax = 1500,
	armor = 0,
	resists = {0,0,0,0,30,-1,30,-1,-1},
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
	diet = HERBIVORE,

	templates = {"object/mobile/emperor_royal_guard.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2000000},
				{group = "wearables_common", chance = 2000000},
				{group = "wearables_uncommon", chance = 2000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "clothing_attachments", chance = 250000},
				{group = "armor_attachments", chance = 250000}
			},
			lootChance = 3200000
		}
	},
	weapons = {"imperial_weapons_medium"},
	attacks = merge(brawlermaster,marksmanmaster,riflemanmaster,carbineermaster,tkamaster)
}

CreatureTemplates:addCreatureTemplate(imperial_retreat_guard, "imperial_retreat_guard")
