singing_mountain_clan_guardian = Creature:new {
	objectName = "@mob/creature_names:singing_mtn_clan_guardian",
	socialGroup = "Mtn. Clan",
	pvpFaction = "Mtn. Clan",
	faction = "",
	level = 156,
	chanceHit = 8.5,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 14789,
	baseHAM = 81000,
	baseHAMmax = 99000,
	armor = 1,
	resists = {100,20,20,100,100,100,100,100,-1},
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

	templates = {"object/mobile/dressed_dathomir_sing_mt_clan_guardian.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_select", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "melee_weapons", chance = 2500000},
				{group = "armor_attachments", chance = 550000},
				{group = "clothing_attachments", chance = 550000},
				{group = "pistols", chance = 2750000},
				{group = "rifles", chance = 2750000}
			},
			lootChance = 4800000
		}			
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_guardian, "singing_mountain_clan_guardian")