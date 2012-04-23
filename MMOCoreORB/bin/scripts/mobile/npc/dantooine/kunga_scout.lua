kunga_scout = Creature:new {
	objectName = "@mob/creature_names:kunga_scout",
	socialGroup = "kunga_tribe",
	pvpFaction = "kunga_tribe",
	faction = "kunga_tribe",
	level = 48,
	chanceHit = 0.47,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4734,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {15,35,0,-1,0,60,50,-1,-1},
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

	templates = {"object/mobile/dantari_male.iff",
		"object/mobile/dantari_female.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3500000},
				{group = "loot_kits", chance = 3500000},
				{group = "armor_attachments", chance = 1500000},
				{group = "clothing_attachments", chance = 1500000}
			},
			lootChance = 4800000
		}		
	},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(kunga_scout, "kunga_scout")
