smashball_thug = Creature:new {
  objectName = "@mob/creature_names:smashball_thug",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  socialGroup = "smashball",
  faction = "smashball",
  level = 5,
  chanceHit = 0.250000,
  damageMin = 45,
  damageMax = 50,
  baseXp = 113,
  baseHAM = 135,
  baseHAMmax = 165,
  armor = 0,
  resists = {0,0,0,0,0,0,0,-1,-1},
  meatType = "",
  meatAmount = 0,
  hideType = "",
  hideAmount = 0,
  boneType = "",
  boneAmount = 0,
  milk = 0,
  tamingChance = 0.000000,
  ferocity = 0,
  pvpBitmask = ATTACKABLE,
  creatureBitmask = PACK,
  diet = HERBIVORE,

  templates = {
    "object/mobile/dressed_gran_thug_male_01.iff",
    "object/mobile/dressed_gran_thug_male_02.iff",
    "thug"},
  lootGroups = {
    {
      groups = {
        {group = "junk", chance = 6000000},
        {group = "loot_kit_parts", chance = 2500000},
        {group = "tailor_components", chance = 1500000}
      }
    }
  },
  weapons = {"pirate_weapons_light"},
  reactionStf = "@npc_reaction/slang",
  attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(smashball_thug, "smashball_thug")
