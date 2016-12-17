dev_snow_merc = Creature:new {
	objectName = "@mob/creature_names:mercenary_commander",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "mercenary",
	faction = "thug",
	level = 43,
	chanceHit = 0.54,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4187,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 1,
	resists = {30,30,30,10,130,30,30,-1,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/vendor/devaronian_male.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3000000},
				{group = "wearables_common", chance = 1500000},
				{group = "wearables_uncommon", chance = 500000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "heavy_weapons", chance = 2000000}
			}
		}
	},
	weapons = {"rebel_weapons_heavy"},
	outfit = "snow_soldier_armored_outfit",
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(commandomaster,marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(dev_snow_merc, "dev_snow_merc")
