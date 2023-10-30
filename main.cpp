#include <iostream>
#include <string>
#include <unistd.h>

#include "mqttWrapper.h"
#include "VersionConfig.h"


#define BROKER_ADDR		"192.168.31.241"
#define BROKER_PORT		1883
#define CLIENT_ID		"BananaPi"
#define DEFAULT_TOPIC	"topic/main"
#define USERNAME		"lagoria"
#define PASSWORD		"352479"

static void mqtt_recv_handle(const struct mosquitto_message *message)
{
	std::string topic = std::string(message->topic);
	std::string payload = std::string(static_cast<char *>(message->payload));

	std::cout << "topic: " << topic << std::endl;
	std::cout << "payload:" << std::endl << payload << std::endl;
}


int main(int argc, char *argv[])
{
	// report version and build time
    std::cout << "Version : " << PROJECT_VERSION_MAJOR << "."
                << PROJECT_VERSION_MINOR << "."
				<< PROJECT_VERSION_PATCH << std::endl;
	std::cout << "Build timestamp : " << BUILD_TIMESTAMP << std::endl;

	std::cout << "starting MQTT client" << std::endl;
    mqttWrapper* mqtt;
    mqtt = new mqttWrapper(CLIENT_ID, BROKER_ADDR, BROKER_PORT);

	mqtt->setAccount(USERNAME, PASSWORD);
	mqtt->connectBroker();
	mqtt->subscribeTopic(DEFAULT_TOPIC);

	mqtt->recv_callback(&mqtt_recv_handle);

	char message[] = "hello mqtt";

	while (1) {
		int rc = mqtt->connect_status;
		if (!rc) {
			sleep(1);	
		} else {

			// mqtt->publishTopic(DEFAULT_TOPIC, message);
			sleep(5);
		}

	}
    delete mqtt;
    std::cout << "mqtt deleted" << std::endl;

    return 0;
}

