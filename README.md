# mosuquittopp client of c++ cmake project
base on mosquittopp c++ library

# build

edit main.cpp of connect information

```
cd build
cmake ..
make
./MqttClient
```

`g++ -o mqttClient main.cpp mqttWrapper.cpp mqttWrapper.h  -lmosquittopp`

