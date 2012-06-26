kunga_warrior = Creature:new {
	objectName = "@mob/creature_names:kunga_warrior",
	socialGroup = "kunga_tribe",
	pvpFaction = "kunga_tribe",
	faction = "kunga_tribe",
	level = 70,
	chanceHit = 0.7,
	damageMin = 495,
	damageMax = 700,
	baseXp = 6655,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {25,45,-1,25,25,100,25,-1,-1},
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
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dantari_male.iff",
		"object/mobile/dantari_female.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 6000000},
				{group = "loot_kit_parts", chance = 3000000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 500000}
			},
			lootChance = 3000000
		}		
	},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(kunga_warrior, "kunga_warrior")
