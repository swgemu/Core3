rebel_resistance_agitator = Creature:new {
	objectName = "@mob/creature_names:rebel_resistance_agitator",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
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
	diet = HERBIVORE,

	templates = {
		"object/mobile/selonian_female.iff",
		"object/mobile/selonian_male.iff",
		"object/mobile/bothan_female.iff",
		"object/mobile/bothan_male.iff",
		"object/mobile/aqualish_female.iff",
		"object/mobile/aqualish_male.iff"
	},
	lootGroups = {},
	weapons = {"rebel_weapons_light"},
	reactionStf = "@npc_reaction/military",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(rebel_resistance_agitator, "rebel_resistance_agitator")
