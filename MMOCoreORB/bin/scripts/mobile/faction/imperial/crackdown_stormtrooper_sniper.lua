crackdown_stormtrooper_sniper = Creature:new {
	objectName = "@mob/creature_names:crackdown_stormtrooper_sniper",
	randomNameType = NAME_STORMTROOPER_TAG,
	socialGroup = "imperial",
	faction = "imperial",
	level = 1,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 45,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {0,0,40,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_stormtrooper_sniper_m.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7550000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
                {group = "melee_weapons", chance = 550000},
                {group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "stormtrooper_common", chance = 100000}
			},
			lootChance = 2800000
		}						
	},
	weapons = {"st_sniper_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_stormtrooper_sniper, "crackdown_stormtrooper_sniper")