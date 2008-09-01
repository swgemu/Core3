DROP TABLE IF EXISTS `swgemu`.`consentlist`;
CREATE TABLE  `swgemu`.`consentlist` (
  `id` mediumint(8) unsigned NOT NULL auto_increment,
  `character_id` mediumint(8) unsigned NOT NULL default '0',
  `target_id` mediumint(8) unsigned NOT NULL default '0',
  PRIMARY KEY  USING BTREE (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;