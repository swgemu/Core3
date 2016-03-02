teraud_loyalist_cyborg = Creature:new {
	objectName = "@mob/creature_names:warren_teraud_loyalist_cyborg",
	socialGroup = "warren_cyborg",
	faction = "",
	level = 38,
	chanceHit = 0.43,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3824,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 0,
	resists = {40,50,0,-1,-1,-1,-1,-1,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/warren_teraud_loyalist_cyborg_s01.iff",
		"object/mobile/warren_teraud_loyalist_cyborg_s02.iff",
		"object/mobile/warren_teraud_loyalist_cyborg_s03.iff",
		"object/mobile/warren_teraud_loyalist_cyborg_s04.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4500000},
				{group = "loot_kit_parts", chance = 3000000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 500000},
				{group = "wearables_common", chance = 1500000}
				
			}
		}	
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(teraud_loyalist_cyborg, "teraud_loyalist_cyborg")
