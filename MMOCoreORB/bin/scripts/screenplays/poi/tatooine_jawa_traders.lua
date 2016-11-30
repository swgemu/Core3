JawaTradersScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("JawaTradersScreenPlay", true)

function JawaTradersScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function JawaTradersScreenPlay:spawnMobiles()

	-- Canopy
	spawnMobile("tatooine", "jawa", 300, -6184.270, 7.253, 1852.560, 154.785, 0)
	spawnMobile("tatooine", "jawa_protector", 300, -6183.420, 7.123, 1848.440, 29.248, 0)
	
	-- Canopy
	spawnMobile("tatooine", "jawa", 300, -6171.940, 7.331, 1862.540, -110.813, 0)
	spawnMobile("tatooine", "jawa_engineer", 300, -6174.910, 7.386, 1862.260, 92.763, 0)
	spawnMobile("tatooine", "moisture_farmer", 300, -6169.650, 7.167, 1860.390, 58.128, 0)
	spawnMobile("tatooine", "jawa", 300, -6166.610, 7.171, 1861.790, -119.299, 0)
	
	-- Canopy
	spawnMobile("tatooine", "jawa_engineer", 300, -6157.420, 6.743, 1856.570, 147.092, 0)
	spawnMobile("tatooine", "eg6_power_droid", 300, -6156.360, 6.590, 1852.880, 1.025, 0)
	spawnMobile("tatooine", "jawa", 300, -6161.590, 6.750, 1854.700, 51.543, 0)
	
	-- Canopy
	spawnMobile("tatooine", "jawa", 300, -6137.470, 6.150, 1826.010, 27.736, 0)
	spawnMobile("tatooine", "commoner_tatooine", 300, -6135.190, 6.113, 1829.220, -154.897, 0)
	
	-- Canopy
	spawnMobile("tatooine", "jawa", 300, -6126.570, 6.175, 1850.980, -138.479, 0)
	spawnMobile("tatooine", "jawa", 300, -6125.800, 6.128, 1848.700, 56.274, 0)
	
	-- Tent
	spawnMobile("tatooine", "jawa", 300, -6108.430, 6.119, 1854.190, -168.669, 0)
	spawnMobile("tatooine", "jawa_smuggler", 300, -6109.630, 6.073, 1850.870, 10.805, 0)
	
	-- Tent
	spawnMobile("tatooine", "scavenger", 300, -6105.770, 7.200, 1876.150, -98.492, 0)
	spawnMobile("tatooine", "jawa", 300, -6100.430, 6.979, 1874.480, 42.015, 0)
	spawnMobile("tatooine", "jawa_healer", 300, -6102.740, 7.177, 1876.340, 105.968, 0)
	
	-- Canopy
	spawnMobile("tatooine", "jawa", 300, -6120.880, 7.706, 1879.030, 26.748, 0)
	spawnMobile("tatooine", "jawa", 300, -6121.260, 7.966, 1881.340, 150.557, 0)
	spawnMobile("tatooine", "commoner_tatooine", 300, -6121.310, 8.365, 1884.780, -129.463, 0)
	spawnMobile("tatooine", "jawa", 300, -6123.150, 8.465, 1885.460, 176.567, 0)
	
	-- Dome Houses
	spawnMobile("tatooine", "jawa", 300, -6146.680, 7.080, 1866.570, -152.161, 0)
	spawnMobile("tatooine", "jawa", 300, -6148.050, 7.584, 1873.060, 54.630, 0)
	spawnMobile("tatooine", "jawa", 300, -6145.830, 7.657, 1874.370, -95.463, 0)
	
	-- Tent Cluster
	spawnMobile("tatooine", "jawa", 300, -6071.840, 10.802, 1904.960, -160.486, 0)
	spawnMobile("tatooine", "jawa", 300, -6067.380, 10.531, 1901.040, 67.575, 0)
	spawnMobile("tatooine", "jawa", 300, -6063.900, 10.867, 1901.970, -102.024, 0)
	spawnMobile("tatooine", "commoner_old", 300, -6064.160, 11.961, 1910.560, 93.988, 0)
	spawnMobile("tatooine", "jawa", 300, -6061.060, 12.454, 1911.960, -156.009, 0)
	spawnMobile("tatooine", "devaronian_male", 300, -6059.150, 12.399, 1909.300, -115.978, 0)
	spawnMobile("tatooine", "jawa", 300, -6083.090, 10.157, 1924.180, -112.091, 0)
	spawnMobile("tatooine", "commoner_tatooine", 300, -6085.170, 10.049, 1923.600, 61.361, 0)
	
	-- Crawler
	spawnMobile("tatooine", "jawa", 300, -6123.260, 6.450, 1812.290, -116.804, 0)
	spawnMobile("tatooine", "commoner_fat", 300, -6125.770, 6.516, 1809.530, 30.035, 0)
	spawnMobile("tatooine", "jawa", 300, -6123.290, 6.651, 1807.380, -176.159, 0)
	spawnMobile("tatooine", "jawa_leader", 300, -6122.600, 6.823, 1804.870, -176.159, 0)
	spawnMobile("tatooine", "jawa", 300, -6123.230, 6.994, 1802.610, 9.479, 0)
	spawnMobile("tatooine", "r4", 300, -6122.400, 7.118, 1801.420, -91.645, 0)
	spawnMobile("tatooine", "eg6_power_droid", 300, -6122.380, 7.310, 1799.560, -91.645, 0)
	spawnMobile("tatooine", "jawa", 300, -6123.020, 7.453, 1798.180, 0.000, 0)
	
	-- Hovels
	spawnMobile("tatooine", "jawa", 300, -6100.840, 6.172, 1832.440, 55.087, 0)
	spawnMobile("tatooine", "jawa", 300, -6094.930, 6.048, 1841.790, 170.197, 0)
	spawnMobile("tatooine", "jawa_engineer", 300, -6095.260, 6.080, 1839.210, 14.127, 0)
	spawnMobile("tatooine", "jawa", 300, -6079.390, 6.021, 1846.490, 54.682, 0)
	
	-- Dome Houses
	spawnMobile("tatooine", "jawa", 300, -6068.180, 7.094, 1878.710, 174.814, 0)
	spawnMobile("tatooine", "jawa", 300, -6068.000, 6.825, 1876.200, 31.008, 0)
	
	-- Hovels
	spawnMobile("tatooine", "jawa", 300, -6090.350, 10.358, 1910.360, -165.395, 0)
	spawnMobile("tatooine", "jawa", 300, -6096.040, 10.178, 1911.140, 77.474, 0)
	spawnMobile("tatooine", "jawa", 300, -6117.270, 9.510, 1916.360, 114.374, 0)
	spawnMobile("tatooine", "jawa_thief", 300, -6115.550, 9.479, 1917.080, 142.642, 0)
	spawnMobile("tatooine", "jawa", 300, -6114.830, 9.614, 1915.280, 51.347, 0)
	spawnMobile("tatooine", "jawa", 300, -6116.080, 9.634, 1914.720, 29.945, 0)
	
	-- Saucer
	spawnMobile("tatooine", "jawa_engineer", 300, -6149.440, 10.070, 1904.440, 79.172, 0)
	spawnMobile("tatooine", "spacer", 300, -6146.920, 10.040, 1906.230, -165.636, 0)
	spawnMobile("tatooine", "jawa", 300, -6146.380, 10.028, 1904.410, -100.932, 0)
	spawnMobile("tatooine", "jawa", 300, -6148.210, 10.025, 1902.720, 27.088, 0)
	
	-- Crawler
	spawnMobile("tatooine", "r2", 300, -6168.600, 8.994, 1884.490, 144.538, 0)
	spawnMobile("tatooine", "r4", 300, -6166.940, 9.091, 1885.690, 143.232, 0)
	spawnMobile("tatooine", "ra7_bug_droid", 300, -6164.780, 9.195, 1887.040, 156.766, 0)
	spawnMobile("tatooine", "rancher", 300, -6165.580, 8.923, 1884.280, 36.089, 0)
	spawnMobile("tatooine", "jawa_leader", 300, -6167.400, 8.841, 1883.180, 9.433, 0)
	spawnMobile("tatooine", "jawa", 300, -6166.120, 8.800, 1882.970, 5.940, 0)
	spawnMobile("tatooine", "jawa", 300, -6163.290, 9.208, 1887.390, -129.183, 0)

 	-- Clothing & Apparel Junk Dealer
	local pNpc = spawnMobile("tatooine", "junk_jawa", 0, -6142.8, 6.2, 1845, -40, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerJawaFineryConvoTemplate")
	end
	
	-- Misc Items Junk Dealer
	spawnMobile("tatooine", "junk_jawa", 0, -6171.1, 8.2, 1874.8, 136, 0)
	
	-- Weapons Junk Dealer
	pNpc = spawnMobile("tatooine", "junk_jawa", 0, -6111.9, 6, 1840.1, -92, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerJawaArmsConvoTemplate")
	end
	
	-- Tusken Equipment Junk Dealer
	pNpc = spawnMobile("tatooine", "junk_jawa", 0, -6120.2, 9.7, 1899.5, 175, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerJawaTuskenConvoTemplate")
	end
end

