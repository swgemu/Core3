-- 
-- Table structure for table `character_structures`
-- 
DROP TABLE IF EXISTS `character_structures`;

CREATE TABLE `character_structures` (
  `zone_id` tinyint(4) NOT NULL default '0',
  `object_id` bigint(20) NOT NULL,
  `parent_id` bigint(20) NOT NULL,
  `cell_number` tinyint(4) NOT NULL default '0',
  `owner_id` mediumint(8) NOT NULL,
  `name` text NOT NULL,
  `template_crc` bigint(20) NOT NULL,
  `template_type` int(10) NOT NULL,
  `template_subtype` int(10) NOT NULL,
  `template_name` tinytext NOT NULL,
  `oX` float NOT NULL,
  `oY` float NOT NULL,
  `oZ` float NOT NULL,
  `oW` float NOT NULL,
  `X` float NOT NULL,
  `Z` float NOT NULL,
  `Y` float NOT NULL,
  `deleted` tinyint(1) NOT NULL default '0',
  `attributes` text NOT NULL,
  `noBuildArea` bigint(20) unsigned NOT NULL default '0',
  UNIQUE KEY `object_id` (`object_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


