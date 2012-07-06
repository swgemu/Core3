CREATE TABLE  `swgemu`.`account_ips` (
  `idaccount_ips` int(11) NOT NULL AUTO_INCREMENT,
  `account_id` int(10) unsigned NOT NULL,
  `ip` varchar(45) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `logout` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`idaccount_ips`)
) ENGINE=MyISAM AUTO_INCREMENT=1099 DEFAULT CHARSET=latin1
