hunter = Creature:new {
	objectName = "@mob/creature_names:hunter",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "poacher",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

        templates = {
                        "object/mobile/dressed_commoner_naboo_twilek_female_02.iff",
                        "object/mobile/dressed_commoner_tatooine_devaronian_male_03.iff",
                        "object/mobile/dressed_commoner_naboo_twilek_male_01.iff",
                        "object/mobile/dressed_commoner_naboo_moncal_male_01.iff"
        },
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 7000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000}
			},
			lootChance = 2200000
		}
	},
	weapons = {"rebel_weapons_light"},
	reactionStf = "@npc_reaction/townperson",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(hunter, "hunter")
