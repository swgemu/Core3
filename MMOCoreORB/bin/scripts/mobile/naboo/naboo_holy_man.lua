naboo_holy_man = Creature:new {
	objectName = "@mob/creature_names:naboo_holy_man",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "naboo",
	faction = "naboo",
	level = 5,
	chanceHit = 0.250000,
	damageMin = 45,
	damageMax = 50,
	baseXp = 85,
	baseHAM = 135,
	baseHAMmax = 165,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_naboo_holy_man.iff",
		"object/mobile/dressed_commoner_naboo_human_female_08.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 2000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000}
			}
		}
	},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/fancy",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(naboo_holy_man, "naboo_holy_man")
