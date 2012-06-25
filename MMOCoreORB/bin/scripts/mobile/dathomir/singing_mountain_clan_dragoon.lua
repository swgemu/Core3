singing_mountain_clan_dragoon = Creature:new {
	objectName = "@mob/creature_names:singing_mtn_clan_dragoon",
	socialGroup = "mtn_clan",
	pvpFaction = "mtn_clan",
	faction = "mtn_clan",
	level = 94,
	chanceHit = 0.95,
	damageMin = 620,
	damageMax = 950,
	baseXp = 8964,
	baseHAM = 20000,
	baseHAMmax = 25000,
	armor = 2,
	resists = {45,45,75,35,75,35,35,35,-1},
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

	templates = {"object/mobile/dressed_dathomir_sing_mt_clan_dragoon.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_quality", chance = 500000},
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
	attacks = merge(brawlermaster,pikemanmaster,forcewielder)

}

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_dragoon, "singing_mountain_clan_dragoon")