package.path = package.path .. ";scripts/managers/name/?.lua"

require("species.bothan")
require("species.human")
require("species.ithorian")
require("species.moncal")
require("species.rodian")
require("species.sullustan")
require("species.trandoshan")
require("species.twilek")
require("species.wookiee")
require("species.zabrak")

require("resource.energy")
require("resource.mineral")
require("resource.plain")
require("resource.reactiveGas")

-- Imperial Trooper Prefixes
stormtrooperPrefixes = { "GK", "LK", "RK", "TK", "VK" };
scouttrooperPrefixes = { "SX", "GX", "VX", "CX", "NX" };
darktrooperPrefixes = { "JLB", "RAR", "KNP", "BCP", "RTZ" };
swamptrooperPrefixes = { "GL", "TL", "RL", "NL", "CL" };