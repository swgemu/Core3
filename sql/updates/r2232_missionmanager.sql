USE swgemu;

DROP TABLE IF EXISTS `mission_manager_spawn_lairs`;

CREATE TABLE `mission_manager_spawn_lairs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `template` varchar(250) DEFAULT NULL,
  `planets` varchar(45) DEFAULT '-1',
  `level_range` varchar(45) DEFAULT '5-10',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

INSERT INTO `mission_manager_spawn_lairs`
(`template`)mission_manager_spawn_lairs
VALUES
(
'object/tangible/lair/cu_pa/lair_cu_pa.iff'
);