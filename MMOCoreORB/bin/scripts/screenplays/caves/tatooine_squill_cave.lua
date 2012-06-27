SquillCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("SquillCaveScreenPlay", true)

function SquillCaveScreenPlay:start()
	self:spawnMobiles()
end

function SquillCaveScreenPlay:spawnMobiles()
	--Cell [7125560]
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -1.0,  -9.9,    3.9, 23, 7125560)
	spawnMobile("tatooine", "mountain_squill_hunter", 200,  1.0, -17.0,   -9.2,-48, 7125560)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -1.3, -17.4,   -9.2, 35, 7125560)

	--Cell [7125561]
	spawnMobile("tatooine", "mountain_squill", 200, -18.2, -29.1, -14.7, -157, 7125561)
	spawnMobile("tatooine", "female_mountain_squill", 200, -12.9, -27.3, -25.7, -12, 7125561)
	spawnMobile("tatooine", "mountain_squill", 200, -28.7, -28.6, -29.1, -1, 7125561)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -37.9, -30.9, -28.0, -67, 7125561)
	spawnMobile("tatooine", "mountain_squill", 200, -42.3, -32.8, -26.5, 118, 7125561)
	spawnMobile("tatooine", "female_mountain_squill", 200, -36.9, -31.5, -24.4, -136, 7125561)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -47.8, -37.2, -6.3, 152, 7125561)
	spawnMobile("tatooine", "mountain_squill", 200, -7.5, -30.3, -44.4, -166, 7125561)
	spawnMobile("tatooine", "mountain_squill", 200, -4.9, -30.0, -47.6, -91, 34, 7125561)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -7.8, -30.0, -51.0, -24, 7125561)
	spawnMobile("tatooine", "female_mountain_squill", 200, -12.9, -30.2, -50.5, 49, 7125561)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -34.0, -31.6, -14.6, 124, 7125561)
	spawnMobile("tatooine", "mountain_squill", 200, -28.8, -30.5, -14.9, -108, 7125561)
	spawnMobile("tatooine", "mountain_squill", 200, -4.9, -30.0, -47.2, -108, 7125561)
	spawnMobile("tatooine", "female_mountain_squill", 200, -11.6, -30.7, -45.9, 141, 7125561)
	
	--Cell [7125578]
	spawnMobile("tatooine", "mountain_squill_hunter", 200, 18.3, -21.2, -16.8, -175, 7125578)
	spawnMobile("tatooine", "mountain_squill", 200, 15.7, -28.0, -41.1, 20, 7125578)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, 18.5, -27.7, -39.4, -86, 7125578)
	spawnMobile("tatooine", "female_mountain_squill", 200, 18.5, -33.1, -54.9, -15, 7125578)

	--Cell [7125579]
	spawnMobile("tatooine", "mountain_squill_hunter", 200, 15.7, -35.4, -69.0, 136, 7125579)
	spawnMobile("tatooine", "female_mountain_squill", 200, 18.7, -35.3, -68.4, -156, 7125579)
	spawnMobile("tatooine", "mountain_squill", 200, 18.5, -35.2, -76.5, -70, 7125579)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, 14.7, -35.4, -76.8, 55, 7125579)
	spawnMobile("tatooine", "female_mountain_squill", 200, 17.2, -35.2, -82.1, 1, 7125579)
	spawnMobile("tatooine", "mountain_squill", 200, -10.6, -34.5, -81.7, 95, 7125579)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -5.3, -35.1, -82.5, -82, 7125579)
	spawnMobile("tatooine", "mountain_squill", 200, -6.8, -35.1, -69.0, -64, 7125579)
	spawnMobile("tatooine", "female_mountain_squill", 200, -6.4, -35.1, -64.6, -125, 7125579)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -10.7, -34.7, -62.6, 152, 7125579)
	spawnMobile("tatooine", "female_mountain_squill", 200, -16.3, -35.0, -76.4, 41, 7125579)
	spawnMobile("tatooine", "mountain_squill", 200, 7.4, -35.6, -83.4, 24, 7125579)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, 2.2, -35.6, -82.9, 55, 7125579)
	spawnMobile("tatooine", "female_mountain_squill", 200, -12.0, -34.9, -78.5, 114, 7125579)
	
	--Cell [7125581]
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -18.3, -43.9, -107.5, 48, 7125581)
	spawnMobile("tatooine", "female_mountain_squill", 200, -15.0,-43.5, -107.7, 3, 7125581)
	spawnMobile("tatooine", "mountain_squill", 200, -13.3, -43.5, -106.8, -45, 7125581)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -11.9, -43.8, -101.6, -117, 7125581)
	spawnMobile("tatooine", "female_mountain_squill", 200, -17.3, -44.2, -101.8, 152, 7125581)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -32.9, -44.4, -98.8, 43, 7125581)
	spawnMobile("tatooine", "female_mountain_squill", 200, -36.0, -44.0, -93.4, 90, 7125581)
	spawnMobile("tatooine", "mountain_squill", 200, -37.0, -44.0, -115.0, -58, 7125581)
	spawnMobile("tatooine", "mountain_squill", 200, -41.0, -44.5, -114.7, -10, 7125581)
	spawnMobile("tatooine", "female_mountain_squill", 200, -56.7, -50.8, -96.4, 139, 7125581)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -52.5, -48.8, -95.4, -141, 7125581)
	spawnMobile("tatooine", "mountain_squill", 200, -53.5, -49.6, -99.6, -47, 7125581)
	spawnMobile("tatooine", "female_mountain_squill", 200, -53.4, -49.4, -114.6, -27, 7125581)
	
	--Cell [7125568]
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -114.2, -69.8, -116.7, 32, 7125568)
	spawnMobile("tatooine", "mountain_squill", 200, -113.6, -69.7, -112.4, 159, 7125568)
	spawnMobile("tatooine", "female_mountain_squill", 200, -110.7, -69.6, -107.9, 163, 7125568)
	spawnMobile("tatooine", "mountain_squill", 200, -103.6, -69.6, 103.4, 66, 7125568)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -97.4, -70.4, -103.4, -85, 7125568)
	spawnMobile("tatooine", "female_mountain_squill", 200, -89.3, -71.6, -106.5, 174, 7125568)
	spawnMobile("tatooine", "female_mountain_squill", 200, -89.0, -71.6, -111.2, -5, 7125568)
	spawnMobile("tatooine", "mountain_squill", 200, -81.2, -72.1, -107.0, 61, 7125568)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -78.7, -71.3, -103.4, 133, 7125568)
	spawnMobile("tatooine", "female_mountain_squill", 200, -74.5, -71.0, -108.0, -78, 7125568)

	--Cell [7125587]
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -42.8, -66.2, -153.7, -139, 7125587)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -41.9, -66.1, -157.9, -100, 7125587)
	spawnMobile("tatooine", "mountain_squill", 200, -45.7, -66.8, -158.0, 47, 7125587)
	spawnMobile("tatooine", "mountain_squill", 200, -41.4, -66.0, -168.5, -103, 7125587)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -44.0, -65.7, -186.4, -62, 7125587)
	spawnMobile("tatooine", "female_mountain_squill", 200, -49.5, -66.1, -189.1, -12, 7125587)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -55.3, -65.7, -187.0, 25, 7125587)
	spawnMobile("tatooine", "female_mountain_squill", 200, -57.6, -66.0, -181.7, 81, 7125587)
	spawnMobile("tatooine", "mountain_squill", 200, -54.0, -65.8, -175.4, 128, 7125587) 
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -68.3, -66.3, -165.7, 20, 7125587)
	spawnMobile("tatooine", "female_mountain_squill", 200, -61.2, -65.8, -165.7, -24, 7125587)
	spawnMobile("tatooine", "female_mountain_squill", 200, -80.2, -65.0, -160.7, -43, 7125587)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -87.8, -66.2, -160.6, 51, 7125587)  
	spawnMobile("tatooine", "female_mountain_squill", 200, -87.4, -65.1, -199.0, 44, 7125587)
	spawnMobile("tatooine", "mountain_squill", 200, -87.1, -65.5, -191.8, 98, 7125587)
	spawnMobile("tatooine", "mountain_squill", 200, -78.8, -66.0, -196.7, -103, 7125587)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -84.4, -66.4, -176.7, 132, 7125587)
	spawnMobile("tatooine", "female_mountain_squill", 200, -73.9, -65.6, -174.3, -162, 7125587)
	spawnMobile("tatooine", "mountain_squill", 200, -80.7, -66.3, -185.9, -27, 7125587)
	
	--Cell [7125588] (primary king chamber)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -57.7, -66.6, -207.2, 10, 7125588)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -50.5, -66.6, -214.0, -94, 7125588)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -60.2, -65.5, -223.7, 110, 7125588)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -51.0, -65.0, -229.2, -81, 7125588)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -68.4, -64.6, -231.2, 113, 7125588)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -66.4, -65.9, -239.1, 67, 7125588)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -55.4, -66.0, -238.9, -37, 7125588)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -55.2, -65.7, -232.7, -122, 7125588)
	
	--Cell [7125585]
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -17.1, -67.7, -115.7, 45, 7125585)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -16.1, -67.6, -102.7, -130, 7125585)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, 1.1, -71.4, -114.5, 57, 7125585)
	spawnMobile("tatooine", "mountain_squill", 200, 6.8, -71.8, -114.7, -19, 7125585)
	spawnMobile("tatooine", "female_mountain_squill", 200, 10.4, -72.1, -108.7, -111, 7125585)
	spawnMobile("tatooine", "mountain_squill", 200, 4.4, -71.5, -106.9, 147, 7125585)
	spawnMobile("tatooine", "female_mountain_squill", 200, 9.1, -70.1, -99.6, -94, 7125585)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -1.6, -68.2, -91.1, 118, 7125585)
	spawnMobile("tatooine", "female_mountain_squill", 200, 9.8, -66.8, -79.8, -154, 7125585)
	spawnMobile("tatooine", "mountain_squill", 200, 8.5, -67.2, -82.7, 25, 7125585)
	
	--Cell [7125564]
	spawnMobile("tatooine", "female_mountain_squill", 200, -63.1, -46.8, -71.2, -91, 7125564)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -62.9, -46.6, -74.6, -63, 7125564)
	spawnMobile("tatooine", "female_mountain_squill", 200, -68.5, -46.8, -75.6, -30, 7125564)
	spawnMobile("tatooine", "mountain_squill", 200, -75.2, -47.0, -74.7, -2, 7125564)
	spawnMobile("tatooine", "female_mountain_squill", 200, -79.8, -46.3, -72.6, 11, 7125564)
	spawnMobile("tatooine", "mountain_squill", 200, -83.3, -47.3, -67.2, 57, 7125564)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -81.8, -46.5, -41.4, 159, 7125564)
	spawnMobile("tatooine", "mountain_squill", 200, -77.7, -46.9, -47.7, -55, 7125564)
	
	spawnMobile("tatooine", "female_mountain_squill", 200, -73.8, -29.9, -40.5, -90, 7125564)
	spawnMobile("tatooine", "female_mountain_squill", 200, -75.4, -29.9, -43.3, -49, 7125564)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -80.4, -31.0, -43.7, -11, 7125564)
	spawnMobile("tatooine", "mountain_squill", 200, -82.9, -30.8, -38.7, 108, 7125564)
	spawnMobile("tatooine", "mountain_squill", 200, -61.6, -30.2, -48.5, -125, 7125564)
	spawnMobile("tatooine", "female_mountain_squill", 200, -62.3, -30.9, -58.1, -58, 7125564)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -73.9, -31.8, -63.2, -86, 7125564)
	spawnMobile("tatooine", "mountain_squill", 200, -73.0, -31.5, -71.4, -74, 7125564)
	spawnMobile("tatooine", "female_mountain_squill", 200, -65.6, -30.5, -75.4, 47, 7125564)
	spawnMobile("tatooine", "mountain_squill_hunter", 200, -62.0, -30.0, -74.4, -29, 7125564)

	--Cell [7125575]
	spawnMobile("tatooine", "mountain_squill", 200, -122.5, -57.5, -24.2, 130, 7125575)
	spawnMobile("tatooine", "mountain_squill", 200, -123.3, -57.6, -29.4, 64, 7125575)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -114.6, -58.0, -34.7, 51, 7125575)
	spawnMobile("tatooine", "mountain_squill", 200, -111.9, -57.6, -34.8, -63, 7125575)
	spawnMobile("tatooine", "female_mountain_squill", 200, -112.9, -58.1, -32.5, -159, 7125575)
	spawnMobile("tatooine", "mountain_squill", 200, -112.7, -57.6, -25.0, 129, 7125575)
	spawnMobile("tatooine", "female_mountain_squill", 200, -106.8, -57.5, -24.9, -98, 7125575)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -106.6, -58.1, -28.7, -54, 7125575)
	spawnMobile("tatooine", "mountain_squill", 200, -101.6, -58.5, -37.1, -27, 7125575)

	--Cell [7125570]
	spawnMobile("tatooine", "mountain_squill", 200, -121.0, -53.9, -81.2, -121, 7125570)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -123.9, -53.8, -81.3, -106, 7125570)
	spawnMobile("tatooine", "mountain_squill", 200, -128.7, -53.7, -90.7, -1, 7125570)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -142.0, -53.8, -78.8, 135, 7125570)
	spawnMobile("tatooine", "mountain_squill", 200, -146.2, -53.8, -82.9, 64, 7125570)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -145.9, -53.8, -89.8, 53, 7125570)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -133.5, -53.8, -78.4, 117, 7125570)

	--Cell [7125569]
	spawnMobile("tatooine", "mountain_squill", 200, -164.9, -49.6, -63.4, 146, 7125569)
	spawnMobile("tatooine", "female_mountain_squill", 200, -161.6, -49.6, -64.5, -108, 7125569)
	spawnMobile("tatooine", "mountain_squill", 200, -160.1, -49.6, -71.3, -171, 7125569)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -163.1, -50.0, -73.5, 107, 7125569)
	spawnMobile("tatooine", "mountain_squill", 200, -162.3, -49.9, -76.7, 39, 7125569)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -163.3, -49.8, -80.8, 36, 7125569)
	spawnMobile("tatooine", "mountain_squill", 200, -159.8, -50.0, -80.6, 29, 7125569)
	spawnMobile("tatooine", "mountain_squill_guardian", 200, -163.8, -49.4, -86.8, 32, 7125569)
	spawnMobile("tatooine", "mountain_squill", 200, -161.8, -49.7, -83.5, -152, 7125569)
	
	--Cell [7125565]
	spawnMobile("tatooine", "mountain_squill", 200, -135.0,  -49.7, -60.2,    128, 7125565)
	spawnMobile("tatooine", "mountain_squill", 200, -132.6,  -49.9, -59.7,   -168, 7125565)
	spawnMobile("tatooine", "female_mountain_squill", 200, -130.6,  -49.6, -62.0,    -87, 7125565)
	spawnMobile("tatooine", "mountain_squill", 200, -133.3,  -49.5, -63.8,     -6, 7125565)
	spawnMobile("tatooine", "female_mountain_squill", 200, -108.7,  -52.4, -57.9,   -144, 7125565)
	spawnMobile("tatooine", "mountain_squill", 200,  -89.9,  -49.6, -60.9,     84, 7125565)
	spawnMobile("tatooine", "female_mountain_squill", 200, -100.6,  -51.6, -64.8,    -34, 7125565)
	spawnMobile("tatooine", "mountain_squill", 200,  -95.4,  -50.6, -54.7,   -141, 7125565)
	
	--Cell [7125571]
	spawnMobile("tatooine", "female_mountain_squill", 200,  -176.7, -53.8, -122.5, 54, 7125571)
	spawnMobile("tatooine", "mountain_squill", 200,  -167.5, -54.9, -123.2, 9, 7125571)
	spawnMobile("tatooine", "female_mountain_squill", 200,  -177.1, -52.7, -109.3, 118, 7125571)
	
	
	--Cell [7125576]
	spawnMobile("tatooine", "mountain_squill", 200,  -104.6, -42.4, -9.1, 179, 7125571)
	spawnMobile("tatooine", "female_mountain_squill", 200,  -107.1, -42.0, -21.1, 9, 7125571)
	spawnMobile("tatooine", "mountain_squill", 200,  -123.1, -47.9, -11.7, 66, 7125571)
end