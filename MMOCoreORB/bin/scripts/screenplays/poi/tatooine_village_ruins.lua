TatooineVillageRuinsScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("TatooineVillageRuinsScreenPlay", true)

function TatooineVillageRuinsScreenPlay:start()
	if (isZoneEnabled("tatooine")) then

		local random = getRandomNumber(100)

		if random >= 30 then
			self:spawnTuskens()
		elseif random < 5 then
			self:spawnKrayt()
		else
			self:spawnJawas()
		end
	end
end

function TatooineVillageRuinsScreenPlay:spawnTuskens()

	--sceneobjects
	spawnSceneObject("tatooine", "object/tangible/camp/campfire_logs_fresh.iff", 5682.4, 33.1, 1914.2, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/campfire_logs_fresh.iff", 5699.5, 31.8, 1900.4, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/campfire_logs_fresh.iff", 5701.4, 31.2, 1912.1, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/campfire_logs_fresh.iff", 5705.2, 34.8, 1839.2, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/campfire_logs_fresh.iff", 5676.7, 36.4, 1848.2, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/campfire_logs_fresh.iff", 5652.4, 37.8, 1870.6, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/campfire_logs_fresh.iff", 5657.1, 36.4, 1898.0, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/camp_tent_s1.iff", 5678.2, 33.8, 1916.8, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/camp_tent_s1.iff", 5693.8, 32.2, 1898.1, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/camp_tent_s1.iff", 5712.2, 34.8, 1842.9, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/camp_tent_s1.iff", 5656.3, 37.9, 1874.3, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/camp_tent_s1.iff", 5656.9, 36.2, 1919.4, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/camp_tent_s1.iff", 5657.5, 36.5, 1889.6, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/camp_stool_short.iff", 5705.9, 34.4, 1842.7, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/camp_stool_short.iff", 5695.3, 31.7, 1902.0, 0, 1, 0, 0, 0)
	spawnSceneObject("tatooine", "object/tangible/camp/camp_stool_short.iff", 5682.9, 33.1, 1917.5, 0, 1, 0, 0, 0)

	--tuskens
	spawnMobile("tatooine", "tusken_raid_leader", 300, 5669.8, 35.5, 1928.9, 127, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5658.7, 36.4, 1923.5, -47, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5657.4, 36.5, 1926.0, 153, 0)
	spawnMobile("tatooine", "tusken_brute", 300, 5655.4, 36.3, 1924.3, 70, 0)
	spawnMobile("tatooine", "tusken_brute", 300, 5666.4, 35.9, 1920.4, 90, 0)
	spawnMobile("tatooine", "tusken_guard", 300, 5674.8, 34.7, 1925.6, -9, 0)
	spawnMobile("tatooine", "tusken_woman", 300, 5676.9, 34.9, 1931.7, -110, 0)
	spawnMobile("tatooine", "tusken_woman", 300, 5681.8, 33.2, 1917.2, 160, 0)
	spawnMobile("tatooine", "tusken_child", 300, 5684.7, 32.7, 1916.0, -130, 0)
	spawnMobile("tatooine", "tusken_child", 300, 5685.6, 32.5, 1912.9, -80, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5682.8, 32.9, 1911.3, -13, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5676.2, 34.1, 1906.3, 173, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5697.1, 31.6, 1901.8, 119, 0)
	spawnMobile("tatooine", "tusken_woman", 300, 5697.4, 32.0, 1898.1, 46, 0)
	spawnMobile("tatooine", "tusken_child", 300, 5701.4, 31.8, 1898.5, -47, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5703.0, 31.0, 1909.7, -31, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5704.7, 31.1, 1912.4, -80, 0)
	spawnMobile("tatooine", "tusken_chief", 300, 5697.7, 31.5, 1916.7, 140, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5710.7, 31.7, 1919.0, -141, 0)
	spawnMobile("tatooine", "tusken_child", 300, 5717.1, 31.9, 1913.8, -47, 0)
	spawnMobile("tatooine", "tusken_child", 300, 5707.8, 32.9, 1928.3, 107, 0)
	spawnMobile("tatooine", "tusken_child", 300, 5717.4, 34.2, 1890.2, -147, 0)
	spawnMobile("tatooine", "tusken_woman", 300, 5710.7, 33.6, 1889.1, 106, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5671.6, 36.5, 1877.9, -167, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5671.5, 36.6, 1874.3, 1, 0)

	spawnMobile("tatooine", "tusken_raider", 300, 5690.3, 34.7, 1863.4, 165, 0)
	spawnMobile("tatooine", "tusken_child", 300, 5710.5, 35.2, 1870.7, 47, 0)
	spawnMobile("tatooine", "tusken_woman", 300, 5720.9, 36.0, 1864.5, 60, 0)
	spawnMobile("tatooine", "tusken_woman", 300, 5707.1, 34.5, 1841.8, -143, 0)
	spawnMobile("tatooine", "tusken_woman", 300, 5703.9, 34.4, 1841.4, 137, 0)
	spawnMobile("tatooine", "tusken_child", 300, 5703.5, 34.7, 1838.6, 75, 0)
	spawnMobile("tatooine", "tusken_child", 300, 5714.5, 36.1, 1834.5, 104, 0)
	spawnMobile("tatooine", "tusken_brute", 300, 5703.1, 34.0, 1854.7, -31, 0)
	spawnMobile("tatooine", "tusken_brute", 300, 5697.5, 34.3, 1862.0, -81, 0)
	spawnMobile("tatooine", "tusken_guard", 300, 5678.8, 35.9, 1850.0, -139, 0)
	spawnMobile("tatooine", "tusken_woman", 300, 5679.3, 36.7, 1839.0, -69, 0)
	spawnMobile("tatooine", "tusken_child", 300, 5675.9, 37.2, 1839.3, 75, 0)
	spawnMobile("tatooine", "tusken_guard", 300, 5660.6, 39.9, 1838.2, -99, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5661.7, 38.8, 1850.6, 5, 0)
	spawnMobile("tatooine", "tusken_captain", 300, 5717.6, 35.0, 1878.7, -15, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5720.7, 34.5, 1880.5, -65, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5721.7, 35.8, 1865.5, -149, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5705.8, 34.9, 1837.4, -10, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5674.1, 36.6, 1850.7, 146, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5678.7, 40.8, 1814.8, -169, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5683.3, 37.2, 1831.5, -89, 0)
	spawnMobile("tatooine", "tusken_elite_guard", 300, 5699.3, 39.8, 1806.5, -39, 0)
	spawnMobile("tatooine", "tusken_flesh_hunter", 300, 5692.6, 40.4, 1809.2, 0, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5652.8, 37.8, 1867.7, 1, 0)
	spawnMobile("tatooine", "tusken_commoner", 300, 5649.7, 37.6, 1870.3, 81, 0)
	spawnMobile("tatooine", "tusken_avenger", 300, 5651.7, 37.5, 1873.5, 158, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5655.3, 36.3, 1895.6, 29, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5660.1, 36.6, 1896.7, -65, 0)

	spawnMobile("tatooine", "tusken_bantha", 300, 5643.8, 37.9, 1862.9, 87, 0)
	spawnMobile("tatooine", "tusken_bantha", 300, 5643.8, 38.2, 1855.1, 87, 0)
	spawnMobile("tatooine", "tusken_bantha", 300, 5643.8, 38.6, 1847.7, 87, 0)
	spawnMobile("tatooine", "tusken_bantha", 300, 5669.9, 36.1, 1889.1, -90, 0)
	spawnMobile("tatooine", "tusken_bantha", 300, 5669.9, 35.8, 1897.4, -90, 0)
	spawnMobile("tatooine", "tusken_bantha", 300, 5730.8, 35.2, 1864.5, -122, 0)

end

function TatooineVillageRuinsScreenPlay:spawnKrayt()

	spawnMobile("tatooine", "krayt_dragon_adolescent", 1800, 5694.2, 34.3, 1847.1, 0, 0)

	spawnMobile("tatooine", "tusken_bantha", 300, 5490.0, 25.8, 2145.7, -90, 0)
	spawnMobile("tatooine", "tusken_bantha", 300, 5490.0, 25.7, 2154.5, -90, 0)

	spawnMobile("tatooine", "tusken_avenger", 300, 5463.4, 26.3, 2144.2, -158, 0)
	spawnMobile("tatooine", "tusken_avenger", 300, 5453.8, 26.3, 2143.4, -176, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5451.7, 27.4, 2134.5, 105, 0)
	spawnMobile("tatooine", "tusken_raider", 300, 5460.4, 26.9, 2132.7, -135, 0)

end

function TatooineVillageRuinsScreenPlay:spawnJawas()

	spawnMobile("tatooine", "jawa_leader", 300, 5669.8, 35.5, 1928.9, 127, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5658.7, 36.4, 1923.5, -47, 0)
	spawnMobile("tatooine", "jawa_smuggler", 300, 5657.4, 36.5, 1926.0, 153, 0)
	spawnMobile("tatooine", "jawa_avenger", 300, 5655.4, 36.3, 1924.3, 70, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5666.4, 35.9, 1920.4, 90, 0)
	spawnMobile("tatooine", "jawa_thief", 300, 5674.8, 34.7, 1925.6, -9, 0)
	spawnMobile("tatooine", "jawa_protector", 300, 5676.9, 34.9, 1931.7, -110, 0)
	spawnMobile("tatooine", "jawa_smuggler", 300, 5681.8, 33.2, 1917.2, 160, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5684.7, 32.7, 1916.0, -130, 0)
	spawnMobile("tatooine", "jawa_avenger", 300, 5676.2, 34.1, 1906.3, 173, 0)
	spawnMobile("tatooine", "jawa_smuggler", 300, 5697.1, 31.6, 1901.8, 119, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5697.4, 32.0, 1898.1, 46, 0)
	spawnMobile("tatooine", "jawa_avenger", 300, 5704.7, 31.1, 1912.4, -80, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5697.7, 31.5, 1916.7, 140, 0)
	spawnMobile("tatooine", "jawa_healer", 300, 5710.7, 31.7, 1919.0, -141, 0)
	spawnMobile("tatooine", "jawa_thief", 300, 5717.1, 31.9, 1913.8, -47, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5710.7, 33.6, 1889.1, 106, 0)
	spawnMobile("tatooine", "jawa_protector", 300, 5671.6, 36.5, 1877.9, -167, 0)
	spawnMobile("tatooine", "jawa_smuggler", 300, 5671.5, 36.6, 1874.3, 1, 0)

	spawnMobile("tatooine", "jawa_thief", 300, 5690.3, 34.7, 1863.4, 165, 0)
	spawnMobile("tatooine", "jawa_protector", 300, 5710.5, 35.2, 1870.7, 47, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5703.9, 34.4, 1841.4, 137, 0)
	spawnMobile("tatooine", "jawa_healer", 300, 5703.5, 34.7, 1838.6, 75, 0)
	spawnMobile("tatooine", "jawa_smuggler", 300, 5714.5, 36.1, 1834.5, 104, 0)
	spawnMobile("tatooine", "jawa_thief", 300, 5703.1, 34.0, 1854.7, -31, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5679.3, 36.7, 1839.0, -69, 0)
	spawnMobile("tatooine", "jawa_smuggler", 300, 5675.9, 37.2, 1839.3, 75, 0)
	spawnMobile("tatooine", "jawa_leader", 300, 5660.6, 39.9, 1838.2, -99, 0)
	spawnMobile("tatooine", "jawa_thief", 300, 5661.7, 38.8, 1850.6, 5, 0)
	spawnMobile("tatooine", "jawa_protector", 300, 5717.6, 35.0, 1878.7, -15, 0)
	spawnMobile("tatooine", "jawa_healer", 300, 5705.8, 34.9, 1837.4, -10, 0)
	spawnMobile("tatooine", "jawa_healer", 300, 5678.7, 40.8, 1814.8, -169, 0)
	spawnMobile("tatooine", "jawa_thief", 300, 5683.3, 37.2, 1831.5, -89, 0)
	spawnMobile("tatooine", "jawa_protector", 300, 5699.3, 39.8, 1806.5, -39, 0)
	spawnMobile("tatooine", "jawa_protector", 300, 5692.6, 40.4, 1809.2, 0, 0)
	spawnMobile("tatooine", "jawa_avenger", 300, 5651.7, 37.5, 1873.5, 158, 0)
	spawnMobile("tatooine", "jawa_thief", 300, 5655.3, 36.3, 1895.6, 29, 0)
	spawnMobile("tatooine", "jawa_warlord", 300, 5660.1, 36.6, 1896.7, -65, 0)

end
