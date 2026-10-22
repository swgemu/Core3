#!/usr/bin/env python3
"""
Regenerates the large AI companion roster deterministically.

Reads : spawn_points.json (outdoor city coordinates mined from Core3), personas_core.json (hand-written bots)
Writes: ../../MMOCoreORB/bin/scripts/custom_scripts/mobile/ai_companions_archetypes.lua
        ../../MMOCoreORB/bin/scripts/custom_scripts/screenplays/ai_companions/roster.lua
        personas.json   (core personas + generated ones; this is what sidecar.py loads)

Edit the data tables below, then run:  python3 generate_roster.py
Change SEED to get a different cast. All text must be ASCII (Lua 5.1 has no \\u escapes).
"""
import json, os, random

HERE = os.path.dirname(os.path.abspath(__file__))
SCRIPTS = os.path.join(HERE, "..", "..", "MMOCoreORB", "bin", "scripts", "custom_scripts")
SEED = 4242
CORE_KEYS = {"kessa", "dax", "jinx"}

CITY_LABEL = {
    "tatooine_mos_eisley": "Mos Eisley", "tatooine_mos_espa": "Mos Espa", "tatooine_bestine": "Bestine",
    "tatooine_mos_entha": "Mos Entha", "naboo_theed": "Theed", "naboo_keren": "Keren", "naboo_moenia": "Moenia",
    "corellia_coronet": "Coronet", "corellia_tyrena": "Tyrena", "corellia_kor_vella": "Kor Vella",
    "talus_dearic": "Dearic", "rori_narmle": "Narmle",
}

# id: count, combat level, weapon group, dressed looks, persona + chat flavour
ARCHETYPES = {
 "hunter": dict(count=12, level=36, weapon="pirate_weapons_medium", noun="bounty hunter",
  looks=["dressed_mercenary_commander_hum_m", "dressed_mercenary_destroyer_hum_f", "dressed_mercenary_commander_zab_m", "dressed_borvos_mercenary"],
  bio="Takes contracts for credits but keeps a personal code about who is fair game.",
  voice="Blunt and economical with words, dry humour, respects competence.",
  activities=["checking the bounty boards", "cleaning a blaster", "sizing up the crowd", "nursing a drink"],
  acks=dict(follow=["Lead on.", "Right behind you.", "Finally, some action."], stay=["Holding here.", "Waiting."], attack=["Target acquired.", "I've got your back."], dismiss=["Call me if you need me.", "Back to the hunt, then."]),
  fallback=["Hm.", "Sounds like a job.", "Credits first. Stories later.", "Keep your head down out there.", "Don't make me repeat myself."]),
 "trader": dict(count=10, level=12, weapon="pirate_weapons_light", noun="trader",
  looks=["dressed_businessman_human_male_01", "dressed_commoner_fat_human_male_01", "dressed_commoner_fat_human_female_01", "dressed_noble_fat_human_female_01"],
  bio="Lives for margins and rumours, and never admits to a bad deal.",
  voice="Chatty and persuasive, loves to haggle, exaggerates cheerfully.",
  activities=["haggling over prices", "counting credits", "inspecting a crate", "complaining about taxes"],
  acks=dict(follow=["Fine, but you're buying.", "Lead on, friend."], stay=["I'll mind the stock.", "Not going anywhere."], attack=["If I must!", "Hope this pays well."], dismiss=["Good doing business.", "Back to the stall."]),
  fallback=["Prices are up everywhere, I swear.", "That's worth a drink.", "I could say more, but information costs.", "Ha! You'd make a fine merchant.", "Business is never what it was."]),
 "smuggler": dict(count=10, level=20, weapon="pirate_weapons_light", noun="smuggler",
  looks=["dressed_criminal_smuggler_human_female_01", "dressed_criminal_smuggler_human_male_01", "dressed_kobola_smuggler_trandoshan_female_01", "dressed_kobola_smuggler_trandoshan_male_01"],
  bio="Runs cargo nobody should ask about, always watching the exits.",
  voice="Smooth, wary, speaks in half-hints and slang.",
  activities=["eyeing the exits", "meeting a contact", "checking a hidden compartment", "dodging a patrol"],
  acks=dict(follow=["Quietly, then.", "Sure. Keep it low-key."], stay=["I'll lie low.", "Waiting. Watching."], attack=["Make it quick.", "Now we're talking."], dismiss=["Never saw you.", "Be seeing you."]),
  fallback=["Keep your voice down.", "I know a guy. Don't ask.", "Everything has a price.", "Never trust a clean ledger.", "Funny how patrols appear when you need them gone."]),
 "scout": dict(count=10, level=24, weapon="pirate_weapons_medium", noun="wilderness scout",
  looks=["dressed_corsair_scout_hum_f", "dressed_corsair_scout_hum_m", "dressed_corsair_scout_rod_m", "dressed_corsair_scout_wee_m"],
  bio="Happier outside the walls than in them, maps the creature trails and knows where not to step.",
  voice="Calm, observant, notices details others miss.",
  activities=["studying a map", "checking supplies", "watching the horizon", "sharpening a knife"],
  acks=dict(follow=["I know the way.", "Stay close and quiet."], stay=["I'll scout nearby.", "Holding."], attack=["Contact.", "Moving in."], dismiss=["Safe travels.", "Back to the trails."]),
  fallback=["Wind's changing.", "Tracks everywhere out there.", "Good boots beat good luck.", "The wild is honest, at least.", "Watch the ridgeline."]),
 "medic": dict(count=8, level=18, weapon="pirate_weapons_light", noun="field medic",
  looks=["dressed_mercenary_medic_rodian_female_01", "dressed_mercenary_elite_medic_human_male_01", "dressed_hutt_medic2_twilek_male_01"],
  bio="Patches up anyone who pays, and some who cannot, and pretends not to care.",
  voice="Kind but brisk, clinical humour, always checking on people.",
  activities=["restocking medpacs", "checking a patient", "washing up", "reading a medical datapad"],
  acks=dict(follow=["Someone has to keep you alive.", "Right, let's go."], stay=["I'll set up here.", "Staying put."], attack=["Stay behind me.", "Try not to get hurt."], dismiss=["Look after yourself.", "Drink water."]),
  fallback=["You look tired. Sleep.", "Hydrate. Seriously.", "I've seen worse. Barely.", "Don't pick at it.", "Everyone bleeds the same colour in the end."]),
 "artisan": dict(count=10, level=10, weapon="pirate_weapons_light", noun="artisan",
  looks=["dressed_commoner_artisan_bith_male_01", "dressed_commoner_artisan_sullustan_male_01", "dressed_commoner_artisan_trandoshan_male_01", "dressed_commoner_naboo_human_female_01"],
  bio="Makes tools, trinkets and the odd weapon, and takes pride in craft over profit.",
  voice="Thoughtful, a little proud, fond of metaphors about building things.",
  activities=["working at a bench", "testing a schematic", "sorting resources", "polishing a finished piece"],
  acks=dict(follow=["Let me grab my kit.", "A change of scenery helps the ideas."], stay=["I'll keep working.", "Staying here."], attack=["I'm better with tools, but fine.", "Here goes."], dismiss=["Come back for repairs.", "Back to the bench."]),
  fallback=["Good work takes patience.", "Quality resources are hard to find.", "Measure twice, craft once.", "I once built something that actually worked.", "Everything wears out eventually."]),
 "pilot": dict(count=8, level=22, weapon="pirate_weapons_medium", noun="freelance pilot",
  looks=["dressed_corsec_pilot_human_female_01", "dressed_corsec_pilot_human_male_01"],
  bio="Lives for the stars, bored on the ground, always looking for a charter.",
  voice="Easygoing and cocky, uses flight jargon, tells tall stories.",
  activities=["checking flight plans", "tuning a flight helmet", "swapping hangar gossip", "staring at the sky"],
  acks=dict(follow=["Ground work, for once.", "Sure, why not."], stay=["I'll be in the hangar.", "Staying put."], attack=["Weapons hot.", "Let's make this quick."], dismiss=["Fly safe.", "Clear skies."]),
  fallback=["Gravity is overrated.", "I once outran a patrol cruiser. Mostly.", "Need a charter? Ask.", "Hyperspace never feels the same twice.", "I miss the cockpit."]),
 "miner": dict(count=8, level=16, weapon="pirate_weapons_light", noun="prospector",
  looks=["dressed_kobola_miner_human_female_01", "dressed_kobola_miner_human_male_01", "dressed_mand_miner_hum_01"],
  bio="Hunts rich veins and old claims, always sure the next survey will pay off.",
  voice="Gruff, patient, speaks in short stories about deposits and bad luck.",
  activities=["reading a survey", "cleaning a probe", "arguing about claims", "sampling the soil"],
  acks=dict(follow=["Might find a vein.", "Lead the way."], stay=["I'll keep digging.", "Staying put."], attack=["Pickaxe's heavy but fine.", "Let's do this."], dismiss=["Back to the claim.", "Good luck out there."]),
  fallback=["There's iron in these hills.", "Never trust a map.", "One good vein changes everything.", "Dirt tells you everything.", "Dust gets in everything."]),
 "slicer": dict(count=6, level=14, weapon="pirate_weapons_light", noun="slicer",
  looks=["dressed_criminal_slicer_human_female_01", "dressed_criminal_slicer_human_male_01"],
  bio="Makes locked things open and quiet things loud, mostly harmless, mostly.",
  voice="Quick, nerdy, jokes about firewalls and bad passwords.",
  activities=["tinkering with a terminal", "testing a lockpick", "reading a datapad", "watching the security cameras"],
  acks=dict(follow=["Adventure, fine.", "I'll bring the toolkit."], stay=["I'll stay and tinker.", "Holding."], attack=["Not my specialty!", "Distracting them!"], dismiss=["Stay encrypted.", "Back to the terminals."]),
  fallback=["Passwords are a joke.", "I only crack what's legal. Mostly.", "Everything has a back door.", "That terminal is begging to be opened.", "Don't touch that cable."]),
 "noble": dict(count=8, level=8, weapon="pirate_weapons_light", noun="minor noble",
  looks=["dressed_noble_bothan_female_01", "dressed_noble_bothan_male_01", "dressed_noble_fat_human_female_01", "dressed_herald_noble_twk_female_01"],
  bio="Born to comfort, bored by it, secretly curious about the real world outside the estate.",
  voice="Polished and a touch pompous, but warms up fast.",
  activities=["sipping tea", "reading the court gossip", "admiring the architecture", "complaining about the dust"],
  acks=dict(follow=["How thrilling. Lead on.", "An adventure! Marvelous."], stay=["I shall wait here.", "Staying. Gracefully."], attack=["Oh dear. Very well.", "Defend yourself!"], dismiss=["Do call again.", "Until next time."]),
  fallback=["How terribly rustic.", "Do you have any tea?", "I read about this in a book.", "One simply must try.", "The estate is too quiet."]),
 "farmer": dict(count=10, level=8, weapon="pirate_weapons_light", noun="homesteader",
  looks=["dressed_tatooine_moisture_farmer", "dressed_fs_village_farmer", "dressed_quest_farmer", "dressed_quest_farmer_wife"],
  bio="Works the land and loves it, wary of strangers but generous once trusted.",
  voice="Plain-spoken, practical, tells weather jokes.",
  activities=["checking the crops", "repairing a vaporator", "mending a fence", "counting the harvest"],
  acks=dict(follow=["Got time off for it.", "Lead on, then."], stay=["I'll tend things here.", "Staying."], attack=["Defending my own.", "Let's finish this."], dismiss=["Back to the farm.", "Take care now."]),
  fallback=["Rain's late again.", "Work never ends.", "Good soil is gold.", "We make do.", "Quiet life suits me."]),
}

FIRST = ("Tamsin Orrin Wren Rook Calla Brannoc Isolde Perrin Sable Marek Lyra Dorian Nessa Kellan Odessa Tobin Vesper Garrick "
 "Mirela Joss Alaric Bryn Cassia Dunstan Elara Fenn Gideon Halcyon Ivo Juno Kestrel Lorcan Maelis Nyx Oren Pia Quill Ronan Selene "
 "Thane Ulric Vera Wystan Xander Yara Zeph Arlo Bex Corin Delia Emmet Fiora Grady Hollis Imara Jarek Kira Leif Mara Nico Orla Pike "
 "Quinn Riven Sorrel Tamar Una Vik Wynn Yusef Zara Aldous Brisa Cormac Dagny Eamon Faye Gwen Hale Iris Jory Kenzo Lena Mosi Nia "
 "Oskar Petra Ravi Soren Tessa Uri Vance Wick Xia Yanni Zora Anselm Bodhi Cleo Dmitri Esme Flint Greer Hugo Ines Jules Kato Lux Milo Noor").split()
LAST = ("Vane Holloway Marsh Pike Corwin Dray Sorrel Quist Thorne Valen Ashdown Brightwater Calder Denholm Ellery Faro Garrow Harlow "
 "Ibarra Jessup Kestrel Lindqvist Mercer Nakamura Okonkwo Prowse Quillon Rask Sandoval Tarrant Underhill Voss Whitlock Yarrow Zane "
 "Abara Bexley Corrigan Dunmore Eskild Fennimore Gault Hargrove Idris Jarrow Kovacs Lyle Moreau Nolan Orsini Penhallow Rourke Stroud "
 "Tolliver Urquhart Varga Wexler Yates Zelenko").split()
ORIGINS = ["on a remote homestead", "in a crowded spaceport district", "in a mining camp", "aboard a freighter", "in a trade-guild family",
           "in a failed settlement", "in a quiet farming village", "in the shadow of a big city", "in a merchant caravan"]
QUIRKS = ["Collects odd coins from every world.", "Hums old songs without noticing.", "Claims to have a lucky charm that is clearly just a bolt.",
          "Trusts droids more than people.", "Always asks strangers what they are running from.", "Writes everything in a tiny notebook.",
          "Tells the same story slightly differently every time.", "Never sits with their back to a door.", "Has a running feud with a local vendor.",
          "Keeps a small plant alive in a crate, against all odds.", "Fiercely loyal to a favourite cantina drink.", "Loves a good rumour more than credits.",
          "Obsessed with the weather.", "Gets nostalgic about the old Republic.", "Believes the galaxy is smaller than it looks."]
GOALS = ["Wants to earn enough to buy a ship someday.", "Is saving up to open a shop.", "Hopes to find a lost relative.", "Is chasing a legendary treasure map.",
         "Wants to see every planet at least once.", "Is trying to stay out of Imperial attention.", "Hopes to join the Rebellion when it feels safe.",
         "Wants to prove themselves to a former mentor.", "Dreams of a quiet retirement.", "Is determined to master their trade."]
TICS = ["trails off mid-thought", "uses a lot of idioms", "laughs at their own jokes", "says 'well, then' a lot", "asks a lot of questions",
        "speaks in clipped sentences", "overuses 'friend'", "swears mildly in exclamations like 'blast it'"]

def lua_str(s):
    assert all(ord(c) < 128 for c in s), s
    return json.dumps(s)

def lua_list(items):
    return "{" + ", ".join(lua_str(i) for i in items) + "}"

def main():
    rng = random.Random(SEED)
    pts = json.load(open(os.path.join(HERE, "spawn_points.json")))
    core = json.load(open(os.path.join(HERE, "personas_core.json")))
    slots = [(city, p) for city, d in pts.items() for p in d["points"]]
    arch_ids = [a for a, d in ARCHETYPES.items() for _ in range(d["count"])]
    assert len(slots) == len(arch_ids), (len(slots), len(arch_ids))
    rng.shuffle(arch_ids)

    used_first = {n.lower() for n in CORE_KEYS}
    firsts = [f for f in FIRST if f.lower() not in used_first]
    assert len(set(f.lower() for f in firsts)) == len(firsts), "duplicate first names"
    rng.shuffle(firsts)
    assert len(firsts) >= len(slots), "need more first names"

    bots, personas = [], dict(core["bots"])
    for i, ((city, p), arch) in enumerate(zip(slots, arch_ids)):
        a = ARCHETYPES[arch]
        first, last = firsts[i], rng.choice(LAST)
        name = "%s %s" % (first, last)
        key = first.lower()
        look = rng.randrange(len(a["looks"]))
        bots.append(dict(key=key, arch=arch, template="ai_arch_%s_%d" % (arch, look + 1), name=name,
                         zone=pts[city]["zone"], x=p["x"], z=p["z"], y=p["y"], heading=p["heading"],
                         roam=rng.choice([6, 8, 10, 12]), level=max(3, a["level"] + rng.randint(-4, 4))))
        personas[key] = dict(
            name=name,
            bio="%s is a %s who works around %s. Grew up %s. %s %s %s" % (name, a["noun"], CITY_LABEL[city], rng.choice(ORIGINS), a["bio"], rng.choice(QUIRKS), rng.choice(GOALS)),
            voice="%s Sometimes %s." % (a["voice"], rng.choice(TICS)),
            fallback=a["fallback"])

    # sidecar personas (core + generated)
    out = dict(core)
    out["bots"] = personas
    with open(os.path.join(HERE, "personas.json"), "w", encoding="ascii") as f:
        json.dump(out, f, indent=1)

    # mobile templates, one per (archetype, look)
    lines = ["-- GENERATED by tools/ai_companions_sidecar/generate_roster.py. Do not edit by hand.",
             "-- Archetype looks for the AI companion roster (bot names are applied at spawn time).", "",
             "local function archetypeTemplate(level, dressedTemplate, weapon)", "\treturn Creature:new {",
             '\t\tobjectName = "@mob/creature_names:patron_human_male_02",', '\t\tsocialGroup = "",', '\t\tfaction = "",',
             "\t\tmobType = MOB_NPC,", "\t\tlevel = level,", "\t\tchanceHit = 0.45,", "\t\tdamageMin = 180 + level * 6,",
             "\t\tdamageMax = 260 + level * 9,", "\t\tbaseXp = 0,", "\t\tbaseHAM = 4000 + level * 220,", "\t\tbaseHAMmax = 4600 + level * 250,",
             "\t\tarmor = 0,", "\t\tresists = {15,15,15,15,15,15,15,15,-1},", '\t\tmeatType = "", meatAmount = 0, hideType = "", hideAmount = 0,',
             '\t\tboneType = "", boneAmount = 0, milk = 0, tamingChance = 0, ferocity = 0,',
             "\t\tpvpBitmask = NONE,", "\t\tcreatureBitmask = PACK,", "\t\toptionsBitmask = AIENABLED,", "\t\tdiet = HERBIVORE,",
             '\t\ttemplates = {dressedTemplate},', "\t\tlootGroups = {},", "\t\tprimaryWeapon = weapon,", '\t\tsecondaryWeapon = "unarmed",',
             '\t\tconversationTemplate = "",', "\t\tprimaryAttacks = {},", "\t\tsecondaryAttacks = {}", "\t}", "end", ""]
    for arch, a in ARCHETYPES.items():
        for n, look in enumerate(a["looks"], 1):
            lines.append('CreatureTemplates:addCreatureTemplate(archetypeTemplate(%d, %s, %s), %s)' % (
                a["level"], lua_str("object/mobile/%s.iff" % look), lua_str(a["weapon"]), lua_str("ai_arch_%s_%d" % (arch, n))))
    with open(os.path.join(SCRIPTS, "mobile", "ai_companions_archetypes.lua"), "w", encoding="ascii") as f:
        f.write("\n".join(lines) + "\n")

    # roster data for the screenplay
    r = ["-- GENERATED by tools/ai_companions_sidecar/generate_roster.py. Do not edit by hand.", "AiCompanionsRoster = {", "\tarchetypes = {"]
    for arch, a in ARCHETYPES.items():
        r.append("\t\t%s = { activities = %s, acks = { follow = %s, stay = %s, attack = %s, dismiss = %s } }," % (
            arch, lua_list(a["activities"]), lua_list(a["acks"]["follow"]), lua_list(a["acks"]["stay"]),
            lua_list(a["acks"]["attack"]), lua_list(a["acks"]["dismiss"])))
    r += ["\t},", "\tbots = {"]
    for b in bots:
        r.append("\t\t{ key = %s, arch = %s, template = %s, name = %s, zone = %s, x = %s, z = %s, y = %s, heading = %d, roam = %d, level = %d }," % (
            lua_str(b["key"]), lua_str(b["arch"]), lua_str(b["template"]), lua_str(b["name"]), lua_str(b["zone"]),
            b["x"], b["z"], b["y"], b["heading"], b["roam"], b["level"]))
    r += ["\t},", "}"]
    with open(os.path.join(SCRIPTS, "screenplays", "ai_companions", "roster.lua"), "w", encoding="ascii") as f:
        f.write("\n".join(r) + "\n")
    print("generated %d bots across %d cities" % (len(bots), len(pts)))

if __name__ == "__main__":
    main()
