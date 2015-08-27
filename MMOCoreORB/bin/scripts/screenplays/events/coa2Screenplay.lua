
--[[
Rebel Quest states:
1 - m1 refused
2 - m1 active
3 - m1 return
4 - m1 complete
5 - m2 refused
6 - m2 active
7 - m2 return
8 - m2 complete
9 - m3/4 active
10 - m3/4 complete
11 - m5 refused
12 - m5 active
13 - m5 return
14 - m5 complete

Imperial Quest states:
1 - m1 active
2 - m1 complete
3 - m2 active
4 - m2 complete
5 - m3/4 active
6 - m3/4 complete
7 - m5 active
8 - m5 return
9 - m5 complete
]]

Coa2Screenplay = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "Coa2Screenplay",
}

registerScreenPlay("Coa2Screenplay", true)

function Coa2Screenplay:start()
	self:spawnNpcs()
end

function Coa2Screenplay:spawnNpcs()

end

function Coa2Screenplay:hasDecodedDisk(pPlayer)

end

function Coa2Screenplay:hasEncodedDisk(pPlayer)

end

function Coa2Screenplay:startMission(pPlayer, faction, number)

end

function Coa2Screenplay:progressMission(pPlayer, faction, number)

end

function Coa2Screenplay:cleanupMission(pPlayer, faction, number)

end

function Coa2Screenplay:finishMission(pPlayer, faction, number)

end
