tusken_raid_leader = Creature:new {
	objectName = "@mob/creature_names:tusken_raid_leader",
	socialGroup = "tusken_raider",
	pvpFaction = "tusken_raider",
	faction = "tusken_raider",
	level = 49,
	chanceHit = 0.49,
	damageMin = 390,
	damageMax = 490,
	baseXp = 4825,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {35,25,0,60,-1,30,0,-1,-1},
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
				{group = "junk", chance = 5000000},
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
	attacks = merge(marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(tusken_raid_leader, "tusken_raid_leader")
