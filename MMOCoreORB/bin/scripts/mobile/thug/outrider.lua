outrider = Creature:new {
	objectName = "@mob/creature_names:lost_aqualish_outrider",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "wilder",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_commoner_tatooine_nikto_male_01.iff",
		"object/mobile/dressed_commoner_tatooine_nikto_male_02.iff",
		"object/mobile/dressed_commoner_tatooine_nikto_male_03.iff",
		"object/mobile/dressed_commoner_tatooine_nikto_male_04.iff",
		"object/mobile/dressed_commoner_tatooine_nikto_male_05.iff",
		"object/mobile/dressed_commoner_tatooine_nikto_male_06.iff",
		"object/mobile/dressed_commoner_tatooine_nikto_male_07.iff",
		"object/mobile/dressed_commoner_tatooine_nikto_male_08.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 3000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
			}
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/townperson",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(outrider, "outrider")
