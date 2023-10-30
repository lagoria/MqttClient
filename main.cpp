#include <iostream>
#include <string>
#include <unistd.h>

#include "mqttWrapper.h"

#ifdef USE_THE_CMAKE
#include "VersionConfig.h"
#endif

#define BROKER_ADDR		"192.168.31.241"
#define BROKER_PORT		1883
#define CLIENT_ID		"example"
#define DEFAULT_TOPIC	"topic/test"
#define USERNAME		"test"
#define PASSWORD		"123456"

static void mqtt_recv_handle(const struct mosquitto_message *message)
{
	std::string topic = std::string(message->topic);
	std::string payload = std::string(static_cast<char *>(message->payload));

	std::cout << "topic: " << topic << std::endl;
	std::cout << "payload:" << std::endl << payload << std::endl;
}


int main(int argc, char *argv[])
{
#ifdef VERSION_CONFIG_H
	// report version and build time
    std::cout << "Version : " << PROJECT_VERSION_MAJOR << "."
                << PROJECT_VERSION_MINOR << "."
				<< PROJECT_VERSION_PATCH << std::endl;
	std::cout << "Build timestamp : " << BUILD_TIMESTAMP << std::endl;
#endif

	std::cout << "starting MQTT client" << std::endl;
    mqttWrapper* mqtt;
    mqtt = new mqttWrapper(CLIENT_ID, BROKER_ADDR, BROKER_PORT);

	// 设置账户信息
	mqtt->setAccount(USERNAME, PASSWORD);
	// 连接MQTT代理
	mqtt->connectBroker();
	// 订阅主题
	mqtt->subscribeTopic(DEFAULT_TOPIC);
	// 注册消息接收回调
	mqtt->register_recv_callback(&mqtt_recv_handle);

	char message[] = "hello mqtt";

	while (1) {
		// MQTT代理连接状态
		int rc = mqtt->connect_status;
		if (!rc) {
			sleep(1);	// 等待1秒
		} else {

			// 发布消息
			//mqtt->publishTopic(DEFAULT_TOPIC, message);
			sleep(5);
		}

	}
    delete mqtt;
    std::cout << "mqtt deleted" << std::endl;

    return 0;
}

