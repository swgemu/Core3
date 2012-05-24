tusken_warrior = Creature:new {
	objectName = "@mob/creature_names:tusken_warrior",
	socialGroup = "tusken_raider",
	pvpFaction = "tusken_raider",
	faction = "tusken_raider",
	level = 38,
	chanceHit = 0.43,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3824,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 0,
	resists = {45,30,25,30,-1,30,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/tusken_raider.iff"},
	lootGroups = {
		{
			groups = {
				{group = "tusken", chance = 3000000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "crystals_good", chance = 500000}
			},
			lootChance = 3500000
		}		
	},
	weapons = {"tusken_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(tusken_warrior, "tusken_warrior")
