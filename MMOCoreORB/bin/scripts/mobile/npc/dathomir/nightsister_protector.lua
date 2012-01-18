nightsister_protector = Creature:new {
	objectName = "@mob/creature_names:nightsister_protector",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 131,
	chanceHit = 4.75,
	damageMin = 770,
	damageMax = 1250,
	baseXp = 12424,
	baseHAM = 50000,
	baseHAMmax = 61000,
	armor = 2,
	resists = {55,100,55,100,100,100,100,100,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,
	lootChance = 5900000,

	templates = {"object/mobile/dressed_dathomir_nightsister_protector.iff"},
	lootgroups = {
		{group = "nightsister_crystals_3", chance = 1000000},
		{group = "nightsister_common", chance = 6500000},
		{group = "armor_attachments", chance = 550000},
		{group = "clothing_attachments", chance = 550000},
		{group = "pistols", chance = 750000},
		{group = "rifles", chance = 750000}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nightsister_protector, "nightsister_protector")