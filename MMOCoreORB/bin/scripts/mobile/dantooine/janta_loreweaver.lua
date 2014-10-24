janta_loreweaver = Creature:new {
	objectName = "@mob/creature_names:janta_loreweaver",
	socialGroup = "janta_tribe",
	pvpFaction = "janta_tribe",
	faction = "janta_tribe",
	level = 55,
	chanceHit = 0.6,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5373,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {-1,45,-1,0,0,70,0,-1,-1},
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
		"object/mobile/dantari_male.iff",
		"object/mobile/dantari_female.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5500000},
				{group = "janta_common", chance = 1500000},
				{group = "loot_kit_parts", chance = 3000000}
			},
			lootChance = 2000000
		}
	},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = merge(pikemanmaster,fencermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(janta_loreweaver, "janta_loreweaver")
