# mosquittopp client of c++ example
A simple MQTT client example

## prerequisites 
base on mosquittopp c++ library  
基于mosquittopp库

If not, install it:  
如果没有可直接安装：

```
sudo apt install libmosquittopp1 libmosquittopp-dev
```


## build

edit `main.cpp` of server connect information  
编辑 `main.cpp` 服务器连接信息

1. use the cmake

	使用cmake构建
	```
	mkdir build
	cd build
	cmake ..
	make
	./MqttClient
	```
2. use the g++

	直接使用g++  
	```
	g++ -o MqttClient -std=c++11 main.cpp mqttWrapper.cpp mqttWrapper.h  -lmosquittopp
	./MqttClient
	```
