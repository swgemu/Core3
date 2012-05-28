kunga_shaman = Creature:new {
	objectName = "@mob/creature_names:kunga_shaman",
	socialGroup = "kunga_tribe",
	pvpFaction = "kunga_tribe",
	faction = "kunga_tribe",
	level = 57,
	chanceHit = 0.55,
	damageMin = 450,
	damageMax = 610,
	baseXp = 5555,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {10,10,10,40,40,-1,-1,10,-1},
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
	creatureBitmask = PACK + HERD + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dantari_male.iff",
		"object/mobile/dantari_female.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3000000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 500000}
			},
			lootChance = 3500000
		}	
	},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(kunga_shaman, "kunga_shaman")
