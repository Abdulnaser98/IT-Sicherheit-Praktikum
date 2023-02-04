# About

This project provides software that enables tracking of common Smart Home devices, e.g. power outlets. The idea is to connect sensors to ESP-12 microcontrollers that monitor the IoT devices.

## TL,DR;

### Arduino Scripts
We provide two Arduino scripts:
* `client\tuersensor.ino` provides a script to measure the output of a _photoresistor light sensor module_. Whenever a pre-defined threshold is exceeded, the microcontroller sends the new state as payload of an UDP request.
* `client\optokoppler.ino` is used to track smart power outlets and switches connected to an _ESP-12_ in the same way as described above.

### Data Analysis

1. Start a `Jupyter` server by running `docker run -p 8888:8888 -v $(pwd)/analysis:/home/jovyan/work jupyter/scipy-notebook`. Make sure you have `docker` up and running. Token-authentication is enabled, meaning you can access the application by opening `http://127.0.0.1:8888/lab?token=<YOUR_TOKEN>`. The URL, including your token, is displayed in your terminal.
2. Open `work/analysis.ipynb` and explore our data analysis.

### Database setup and API
This project provides a simple setup including a `mysql` database, `phpmyadmin`, and an API that can be used for Arduino applications. This is legacy since in production we decided to send `UDP` packages that are tracked by `wireshark`. However, for future projects this setup might be helpful.

1. Start all three applications by running `docker-compose up -d`. Afterwards, `phpmyadmin` is available at `localhost/dashboard`.
If you like to adapt `mysql` database user names and passwords, have a look at the `.env` file. By default, the `root` user is used to handle API requests. This can be changed in the `docker-compose` file.

2. Test the API by executing  `curl localhost/test.php`. You should be good to go :sunglasses:

3. Additionally, you can write actual values to the data base by sending a POST request: `curl -d "sensorData=High&date=2022-11-22&time=21:00:00" localhost/postData.php`