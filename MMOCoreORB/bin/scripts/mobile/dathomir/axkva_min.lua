axkva_min = Creature:new {
	objectName = "@mob/creature_names:axkva_min",
	socialGroup = "nightsister",
	pvpFaction = "nightsister",
	faction = "nightsister",
	level = 302,
	chanceHit = 30,
	damageMin = 1645,
	damageMax = 3000,
	baseXp = 28549,
	baseHAM = 385000,
	baseHAMmax = 471000,
	armor = 3,
	resists = {100,95,95,100,100,100,100,100,-1},
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
	creatureBitmask = PACK + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_nightsister_axkva.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_premium", chance = 900000},
				{group = "nightsister_common", chance = 5000000},
				{group = "pistols", chance = 1500000},
				{group = "rifles", chance = 1500000},
				{group = "armor_attachments", chance = 550000},
				{group = "clothing_attachments", chance = 550000}
			},
			lootChance = 8000000
		},
		{
			groups = {
				{group = "axkva_min", chance = 10000000},
			},
			lootChance = 6500000
		}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(axkva_min, "axkva_min")