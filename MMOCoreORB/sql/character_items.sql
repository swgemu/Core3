
DROP TABLE `character_items`;

-- ----------------------------
-- Table structure for character_items
-- ----------------------------
CREATE TABLE `character_items` (
  `item_id` bigint(20) unsigned NOT NULL,
  `character_id` bigint(20) unsigned NOT NULL,
  `name` text NOT NULL,
  `template_crc` bigint(20) unsigned NOT NULL,
  `template_type` int(10) unsigned NOT NULL,
  `template_name` tinytext NOT NULL,
  `container` bigint(20) unsigned NOT NULL default '0',
  `equipped` tinyint(1) unsigned NOT NULL,
  `deleted` tinyint(1) unsigned NOT NULL default '0',
  `attributes` text NOT NULL,
  `appearance` mediumtext NOT NULL,
  PRIMARY KEY  (`item_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
