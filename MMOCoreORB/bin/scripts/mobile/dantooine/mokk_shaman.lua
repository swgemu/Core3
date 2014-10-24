mokk_shaman = Creature:new {
	objectName = "@mob/creature_names:mokk_shaman",
	socialGroup = "mokk_tribe",
	pvpFaction = "mokk_tribe",
	faction = "mokk_tribe",
	level = 60,
	chanceHit = 0.6,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5830,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {15,60,15,-1,-1,60,60,-1,-1},
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
	creatureBitmask = PACK + HERD + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dantari_female.iff",
		"object/mobile/dantari_male.iff"},
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
	attacks = merge(pikemanmaster,fencermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(mokk_shaman, "mokk_shaman")
