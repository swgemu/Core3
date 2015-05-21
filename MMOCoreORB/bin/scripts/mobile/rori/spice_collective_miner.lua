spice_collective_miner = Creature:new {
	objectName = "@mob/creature_names:spice_collective_miner",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "spice_collective",
	faction = "spice_collective",
	level = 9,
	chanceHit = 0.270000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_spice_collective_miner_human_female_01.iff",
		"object/mobile/dressed_spice_collective_miner_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2000000},
				{group = "wearables_common", chance = 2000000},
				{group = "melee_weapons", chance = 2000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000}
			}
		}
	},
	weapons = {"pirate_weapons_medium"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(spice_collective_miner, "spice_collective_miner")
