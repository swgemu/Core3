meatlump_buffoon = Creature:new {
  objectName = "@mob/creature_names:meatlump_buffoon",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  socialGroup = "meatlump",
  faction = "meatlump",
  level = 5,
  chanceHit = 0.250000,
  damageMin = 45,
  damageMax = 50,
  baseXp = 85,
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
  creatureBitmask = HERD,
  diet = HERBIVORE,

  templates = {"thug"},
  lootGroups = {
    {
      groups = {
        {group = "junk", chance = 2900000},
        {group = "loot_kit_parts", chance = 1500000},
        {group = "color_crystals", chance = 100000},
        {group = "tailor_components", chance = 500000},
        {group = "meatlump_common", chance = 5000000}
      }
    }
  },
  weapons = {"pirate_weapons_light"},
  reactionStf = "@npc_reaction/slang",
  attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(meatlump_buffoon, "meatlump_buffoon")
