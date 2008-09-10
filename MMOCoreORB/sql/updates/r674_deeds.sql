CREATE TABLE IF NOT EXISTS `character_structures` (
  `zoneid` tinyint(4) NOT NULL,
  `objectid` bigint(20) NOT NULL,
  `parentid` bigint(20) NOT NULL,
  `title` varchar(200) NOT NULL,
  `template` varchar(255) NOT NULL,
  `crc` bigint(20) NOT NULL,
  `file` varchar(200) NOT NULL,
  `oX` float NOT NULL,
  `oY` float NOT NULL,
  `oZ` float NOT NULL,
  `oW` float NOT NULL,
  `X` float NOT NULL,
  `Z` float NOT NULL,
  `Y` float NOT NULL,
  `type` float NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

