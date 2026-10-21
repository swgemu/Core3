#!/usr/bin/env python3
"""
AI Companions sidecar for SWGEmu Core3.

Watches log/ai_companions_requests.tsv (written by the AiCompanions Lua screenplay),
asks an LLM to answer in character, and appends the reply to
log/ai_companions_responses.tsv for the screenplay to speak in-game.

Runs without an API key too: it then answers with canned lines from personas.json
so you can test the whole pipeline first.

Usage:
  python3 sidecar.py --log-dir /path/to/MMOCoreORB/bin/log
Env:
  ANTHROPIC_API_KEY   enables real LLM replies
  AI_COMPANION_MODEL  model id (default: claude-haiku-5-5)
"""
import argparse, json, os, random, sys, threading, time
from collections import defaultdict, deque
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
MAX_REPLY_CHARS = 220
HISTORY_TURNS = 8

SYSTEM_TEMPLATE = """You are {name}, a character living in a Star Wars Galaxies server. Stay fully in character.

World: {world}
Who you are: {bio}
How you talk: {voice}

Current situation: you are level {level} and you are {activity}. Zone: {zone}. {following}

Rules:
- Reply with ONE or TWO short sentences of spoken dialogue, under {limit} characters total.
- Plain text only. No markdown, no quotes around the line, no stage directions or asterisks.
- Talk to {player} directly. Use their name only occasionally.
- Never invent game mechanics or promise items, credits or quests you cannot deliver.
- If {player} sincerely asks whether you are a real person or an AI, be honest in a light, in-character way. Otherwise do not bring it up.
- Keep content suitable for a general audience."""


def load_personas():
    with open(os.path.join(HERE, "personas.json"), encoding="utf-8") as f:
        return json.load(f)


class Brain:
    def __init__(self, personas, model):
        self.personas = personas
        self.model = model
        self.history = defaultdict(lambda: deque(maxlen=HISTORY_TURNS * 2))
        self.lock = threading.Lock()
        self.client = None
        if os.environ.get("ANTHROPIC_API_KEY"):
            try:
                import anthropic
                self.client = anthropic.Anthropic()
            except ImportError:
                print("anthropic package missing (pip install anthropic); using canned replies", file=sys.stderr)

    def fallback(self, key):
        lines = self.personas["bots"].get(key, {}).get("fallback") or ["..."]
        return random.choice(lines)

    def reply(self, req):
        key = req["bot"]
        persona = self.personas["bots"].get(key)
        if persona is None:
            return None
        if self.client is None:
            return self.fallback(key)

        system = SYSTEM_TEMPLATE.format(
            name=persona["name"], world=self.personas["world"], bio=persona["bio"], voice=persona["voice"],
            level=req["level"], activity=req["activity"], zone=req["zone"], player=req["player"], limit=MAX_REPLY_CHARS,
            following=("You are currently travelling with %s as their companion." % req["player"]) if req["following"] else "")
        hist_key = (key, req["player"])
        with self.lock:
            messages = list(self.history[hist_key]) + [{"role": "user", "content": req["message"]}]
        try:
            resp = self.client.messages.create(model=self.model, max_tokens=120, system=system, messages=messages)
            text = "".join(b.text for b in resp.content if getattr(b, "type", "") == "text").strip()
        except Exception as e:  # network, rate limit, bad key...
            print("LLM error: %s" % e, file=sys.stderr)
            return self.fallback(key)
        text = " ".join(text.replace('"', "").split())[:MAX_REPLY_CHARS] or self.fallback(key)
        with self.lock:
            self.history[hist_key].append({"role": "user", "content": req["message"]})
            self.history[hist_key].append({"role": "assistant", "content": text})
        return text


def parse(line):
    parts = line.rstrip("\n").split("\t", 7)
    if len(parts) != 8:
        return None
    try:
        return {"id": parts[0], "bot": parts[1], "player": parts[2], "level": int(parts[3]),
                "activity": parts[4], "zone": parts[5], "following": parts[6] == "1", "message": parts[7]}
    except ValueError:
        return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--log-dir", required=True, help="Core3 bin/log directory")
    ap.add_argument("--model", default=os.environ.get("AI_COMPANION_MODEL", "claude-haiku-5-5"))
    ap.add_argument("--replay", action="store_true", help="process existing requests instead of starting at the end")
    args = ap.parse_args()

    os.makedirs(args.log_dir, exist_ok=True)
    req_path = os.path.join(args.log_dir, "ai_companions_requests.tsv")
    resp_path = os.path.join(args.log_dir, "ai_companions_responses.tsv")
    open(req_path, "a").close()
    open(resp_path, "a").close()

    brain = Brain(load_personas(), args.model)
    print("sidecar up | llm=%s | watching %s" % ("on (%s)" % args.model if brain.client else "OFF (canned replies)", req_path))

    write_lock = threading.Lock()

    def handle(req):
        text = brain.reply(req)
        if not text:
            return
        text = text.replace("\t", " ").replace("\n", " ")
        with write_lock, open(resp_path, "a", encoding="utf-8") as out:
            out.write("%s\t%s\t%s\n" % (req["id"], req["bot"], text))
        print("[%s -> %s] %s" % (req["player"], req["bot"], text))

    pool = ThreadPoolExecutor(max_workers=4)
    with open(req_path, "r", encoding="utf-8") as f:
        if not args.replay:
            f.seek(0, os.SEEK_END)
        buf = ""
        while True:
            chunk = f.read()
            if not chunk:
                time.sleep(0.4)
                continue
            buf += chunk
            while "\n" in buf:
                line, buf = buf.split("\n", 1)
                req = parse(line)
                if req:
                    pool.submit(handle, req)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
