crackdown_rebel_guard_captain_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_rebel_guard_captain_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 91,
	chanceHit = 0.96,
	damageMin = 540,
	damageMax = 950,
	baseXp = 9500,
	baseHAM = 19200,
	baseHAMmax = 25800,
	armor = 1,
	resists = {0,0,140,0,0,0,0,-1,-1},
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
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_specforce_captain_moncal_female_01.iff",
		"object/mobile/dressed_rebel_specforce_captain_rodian_female_01.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 4250000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000},
				{group = "rebel_officer_common", chance = 450000},
				{group = "wearables_common", chance = 1000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "rebelRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(commandomaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_rebel_guard_captain_hard, "crackdown_rebel_guard_captain_hard")
