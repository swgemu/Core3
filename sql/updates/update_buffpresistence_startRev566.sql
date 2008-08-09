DROP TABLE IF EXISTS `swgemu`.`buffs`;
CREATE TABLE  `swgemu`.`buffs` (
  `buff_id` bigint(20) unsigned NOT NULL auto_increment,
  `character_id` mediumint(8) unsigned NOT NULL default '0',
  `buff` text NOT NULL,
  PRIMARY KEY  (`buff_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;
