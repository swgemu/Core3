captain_hassk = Creature:new {
	objectName = "@mob/creature_names:captain_hassk",
	socialGroup = "rorgungan",
	faction = "rorgungan",
	level = 73,
	chanceHit = 0.7,
	damageMin = 495,
	damageMax = 700,
	baseXp = 7023,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {80,0,0,0,20,0,35,0,-1},
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
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/captain_hassk.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "wearables_common", chance = 500000},
				{group = "wearables_uncommon", chance = 500000}
			}
		}
	},
	weapons = {"captain_hassk_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,swordsmanmaster)
}

CreatureTemplates:addCreatureTemplate(captain_hassk, "captain_hassk")
