spice_collective_elite_guard = Creature:new {
	objectName = "@mob/creature_names:spice_collective_eliteguard",
	socialGroup = "spice_collective",
	pvpFaction = "spice_collective",
	faction = "spice_collective",
	level = 25,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2637,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {20,40,0,-1,-1,-1,-1,-1,-1},
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
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_spice_collective_eliteguard_zabrak_female_01.iff",
		"object/mobile/dressed_spice_collective_eliteguard_zabrak_male_01.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 6000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000}
			},
			lootChance = 3200000
		}			
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(spice_collective_elite_guard, "spice_collective_elite_guard")