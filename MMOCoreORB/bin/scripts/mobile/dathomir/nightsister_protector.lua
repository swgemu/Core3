nightsister_protector = Creature:new {
	objectName = "@mob/creature_names:nightsister_protector",
	socialGroup = "nightsister",
	pvpFaction = "nightsister",
	faction = "nightsister",
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_nightsister_protector.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_select", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "nightsister_common", chance = 6500000},
				{group = "armor_attachments", chance = 550000},
				{group = "clothing_attachments", chance = 550000},
				{group = "melee_baton", chance = 750000},
				{group = "melee_two_handed", chance = 750000}
			},
			lootChance = 5900000
		}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = merge(tkamaster,brawlermaster,fencermaster,forcepowermaster)
}

CreatureTemplates:addCreatureTemplate(nightsister_protector, "nightsister_protector")
