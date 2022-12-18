# About

This project provides a simple setup including a `mysql` database, `phpmyadmin`, and an API that can be used for Arduino applications.

## TL,DR;

1. Start all three applications by running `docker-compose up -d`. Afterwards, `phpmyadmin` is available at `localhost/dashboard`.
If you like to adapt `mysql` database user names and passwords, have a look at the `.env` file. By default, the `root` user is used to handle API requests. This can be changed in the `docker-compose` file.

2. Test the API by executing  `curl localhost/test.php`. You should be good to go :sunglasses:

3. Additionally, you can write actual values to the data base by sending a POST request: `curl -d "sensorData=High&date=2022-11-22&time=21:00:00" localhost/postData.php`

## UDP
Test UDP connectivity by booting up a local server: `nc -ul 9999`. You can send messages by opening another terminal: `nc -4u localhost 9999`.