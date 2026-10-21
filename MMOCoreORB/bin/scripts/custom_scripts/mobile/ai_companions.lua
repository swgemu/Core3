-- AI Companion mobile templates.
-- Player-like humanoids. pvpBitmask NONE + no faction so nobody aggros them and players
-- cannot attack them; they only fight what the AiCompanions screenplay tells them to.

local function companionTemplate(name, level, dressedTemplate, weapon)
	return Creature:new {
		objectName = "@mob/creature_names:patron_human_male_02",
		customName = name,
		socialGroup = "",
		faction = "",
		mobType = MOB_NPC,
		level = level,
		chanceHit = 0.45,
		damageMin = 180 + level * 6,
		damageMax = 260 + level * 9,
		baseXp = 0,
		baseHAM = 4000 + level * 220,
		baseHAMmax = 4600 + level * 250,
		armor = 0,
		resists = {15,15,15,15,15,15,15,15,-1},
		meatType = "",
		meatAmount = 0,
		hideType = "",
		hideAmount = 0,
		boneType = "",
		boneAmount = 0,
		milk = 0,
		tamingChance = 0,
		ferocity = 0,
		pvpBitmask = NONE,
		creatureBitmask = PACK,
		optionsBitmask = AIENABLED,
		diet = HERBIVORE,
		templates = {dressedTemplate},
		lootGroups = {},
		primaryWeapon = weapon,
		secondaryWeapon = "unarmed",
		conversationTemplate = "",
		primaryAttacks = {},
		secondaryAttacks = {}
	}
end

CreatureTemplates:addCreatureTemplate(
	companionTemplate("Kessa Vor", 38, "object/mobile/dressed_bounty_hunter_zabrak_female_01.iff", "pirate_weapons_medium"),
	"ai_companion_kessa")
CreatureTemplates:addCreatureTemplate(
	companionTemplate("Dax Morrow", 18, "object/mobile/dressed_commoner_fat_human_male_01.iff", "pirate_weapons_light"),
	"ai_companion_dax")
CreatureTemplates:addCreatureTemplate(
	companionTemplate("Jinx Telaro", 12, "object/mobile/dressed_commoner_naboo_bothan_male_01.iff", "pirate_weapons_light"),
	"ai_companion_jinx")
