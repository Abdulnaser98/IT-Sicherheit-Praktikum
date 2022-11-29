CREATE DATABASE sensordaten;

CREATE TABLE  sensordaten.Sesnoractions(
  id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  action_of_sensor varchar(244),
  date_of_action date,
  time_of_action time
);