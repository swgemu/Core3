SecretsOfTheSyren = ScreenPlay:new {
	staticNpcs = {
		{"syren_veega_madish", "corellia", -5203, 21, -2572, 180},
		--{"syren_tyla_jinn", "naboo", -5181, 21, 4258, 50},
		--{"syren_jevan_monsul", "tatooine", -1399, 21, -3675, 50},
	},
}

registerScreenPlay("SecretsOfTheSyren", true)

function SecretsOfTheSyren:start()
	self:spawnStaticNpcs()
end

function SecretsOfTheSyren:spawnStaticNpcs()
	for i = 1, # self.staticNpcs do
		local npc = self.staticNpcs[i]
		if isZoneEnabled(npc[2]) then
			spawnMobile(npc[2], npc[1], 0, npc[3], npc[4], npc[5], npc[6], 0)
		end
	end
end