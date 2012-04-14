nightsister_rancor_tamer = Creature:new {
	objectName = "@mob/creature_names:nightsister_rancor_tamer",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 76,
	chanceHit = 0.75,
	damageMin = 520,
	damageMax = 750,
	baseXp = 7299,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {30,30,30,50,50,50,50,100,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_nightsister_rancor_tamer.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals", chance = 1000000},
				{group = "nightsister_common", chance = 6500000},
				{group = "armor_attachments", chance = 550000},
				{group = "clothing_attachments", chance = 550000},
				{group = "melee_weapons", chance = 750000},
				{group = "rifles", chance = 750000}
			},
			lootChance = 4900000
		}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nightsister_rancor_tamer, "nightsister_rancor_tamer")