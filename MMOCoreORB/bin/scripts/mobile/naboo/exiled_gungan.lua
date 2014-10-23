exiled_gungan = Creature:new {
	objectName = "@mob/creature_names:mordran_gungan_exile",
	socialGroup = "borvo",
	pvpFaction = "borvo",
	faction = "borvo",
	level = 40,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3915,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/gungan_outcast.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2400000},
				{group = "wearables_common", chance = 2000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "composite_armor", chance = 1000000},
				{group = "melee_two_handed", chance = 1000000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000},
			},
			lootChance = 2500000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(exiled_gungan, "exiled_gungan")
