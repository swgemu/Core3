official = Creature:new {
	objectName = "@mob/creature_names:official",
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

	templates = {"object/mobile/dressed_official.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2000000},
				{group = "wearables_common", chance = 2000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 4000000}
			}
		}
	},
	weapons = {"pirate_weapons_medium"},
	reactionStf = "@npc_reaction/fancy",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(official, "official")
