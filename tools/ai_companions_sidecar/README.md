# AI Companions for SWGEmu Core3

103 player-like characters across 12 cities (3 hand-written in Mos Eisley, 100 generated) who roam, "level up", talk back to you through an LLM,
and can be recruited to follow and fight beside you. No C++ changes and no rebuild: Lua + a small Python sidecar.

The 100 generated bots come in 11 archetypes (hunter, trader, smuggler, scout, medic, artisan, pilot, miner, slicer, noble, homesteader), each with a unique name, persona and spawn point in Mos Eisley, Mos Espa, Bestine, Mos Entha, Theed, Keren, Moenia, Coronet, Tyrena, Kor Vella, Dearic and Narmle.

| Hand-written bot | Role | Vibe |
|---|---|---|
| Kessa Vor | Bounty hunter, your adventuring partner (L38) | terse, sardonic, loyal |
| Dax Morrow | Trader / gossip (L18) | chatty, haggling, rumor mill |
| Jinx Telaro | Rookie smuggler (L12) | eager, boastful, wants to be taken seriously |

## Install
1. Copy the contents of this folder tree into your Core3 checkout (same relative paths):
   - `MMOCoreORB/bin/scripts/custom_scripts/mobile/serverobjects.lua` (replaces the empty file)
   - `MMOCoreORB/bin/scripts/custom_scripts/mobile/ai_companions.lua` and `ai_companions_archetypes.lua`
   - `MMOCoreORB/bin/scripts/custom_scripts/screenplays/screenplays.lua` (replaces the empty file)
   - `MMOCoreORB/bin/scripts/custom_scripts/screenplays/ai_companions/ai_companions.lua` and `roster.lua`
   - `tools/ai_companions_sidecar/`
   If you already have custom content in those two `serverobjects`/`screenplays` files, just add the one `includeFile` line from each.
2. Make sure `MMOCoreORB/bin/log/` exists (the server already writes logs there).
3. Start the sidecar (a second terminal; pip install is only needed for LLM replies):
   ```
   pip install -r tools/ai_companions_sidecar/requirements.txt
   export ANTHROPIC_API_KEY=sk-ant-...      # omit to test with canned replies
   python3 tools/ai_companions_sidecar/sidecar.py --log-dir MMOCoreORB/bin/log
   ```
4. Start the server (scripts are Lua, so no recompile). Watch the server log for `AiCompanions:` errors.

## Play
In Mos Eisley, near the market (around 3535, -4800), say a bot's name in spatial chat:
- `Kessa, what are you up to?` -> an in-character LLM reply (a few seconds)
- `Kessa, follow me` / `let's go` / `join me` -> she follows you and auto-assists in your fights
- `Kessa, attack` -> attacks your current target
- `Kessa, stay` / `wait here` -> holds position; `go home` / `dismissed` -> returns to her post
Once she is travelling with you, you don't need to say her name each time.
Only one player at a time can recruit a given bot; bots never auto-attack players.

## Tuning
- Regenerate or reshuffle the 100 bots: edit the tables in `generate_roster.py` (archetypes, names, quirks, counts; `SEED` gives a different cast) and run `python3 generate_roster.py`. It rewrites `roster.lua`, `ai_companions_archetypes.lua` and `personas.json`. Coordinates come from `spawn_points.json` (outdoor points mined from Core3's own city files).
- A player can have at most 3 companions following at once (`MAX_PARTY`).
- Add/edit hand-written bots: `bots = {...}` in `ai_companions.lua`, a template in `mobile/ai_companions.lua`, and a persona (same key) in `personas.json`.
- Cost control: bots only call the LLM when addressed, with a 3s per-bot cooldown, ~120 output tokens. Model via `AI_COMPANION_MODEL` (default `claude-haiku-5-5`).
- Commands and acknowledgements run in Lua and are instant; only free conversation goes to the LLM.

## Known limits / not yet tested in a live server
- Written against current Core3 source (Lua API names checked in the repo; generated data validated), but I could not compile or run the server. Expect to fix small things on first boot.
- Bots follow and assist, but are not real group members: no shared XP/loot, and their "levels" are narrative (they show up in their chat, not as real skills).
- `includeFile("../custom_scripts/mobile/...")` path style is inferred from how Core3 includes custom content; if the mobile template does not load, check the server log for the include error.
