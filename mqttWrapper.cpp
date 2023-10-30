#include "mqttWrapper.h"

#include <iostream>

mqttWrapper::mqttWrapper(const char* id_, const char* host_, int port_) :
    mosquittopp(id_)
{
	// init mosquittopp library
    mosqpp::lib_init();
	/*   init MQTT client info   */
	// default keepalive 60 sec
    this->keepalive = 60;
	this->id = id_;
	this->port = port_;
	this->host = host_;
	this->connect_status = false;

}

mqttWrapper::~mqttWrapper()
{
    if (loop_stop() != MOSQ_ERR_SUCCESS) {
        std::cout << "loop_stop failed" << std::endl;
    }
    mosqpp::lib_cleanup();

    std::cout << "released mqtt client" << std::endl;
}


void mqttWrapper::setAccount(const char *name, const char *passwd)
{
	username = name;
	password = passwd;

    if (username_pw_set(username.c_str(), password.c_str()) != MOSQ_ERR_SUCCESS) {
        std::cout << "setting passwd failed" << std::endl;
    }

}

void mqttWrapper::connectBroker(void)
{
	// asynchronization connect to broker
	connect_async(host.c_str(), port, keepalive);

	// create pthread handle MQTT event
	loop_start();
}

void mqttWrapper::publishTopic(const char *topic, char *message)
{
	std::string mess = message;
	// publish(	int *mid,const char	*topic,int payloadlen, const void *payload, int qos, bool retain)
    int ret = publish(NULL, topic, mess.size(), mess.c_str(), 2, false);
    if (ret != MOSQ_ERR_SUCCESS) {
		switch (ret) {
			case MOSQ_ERR_NO_CONN: 
				std::cout << "Send failed. not connected a broker." << std::endl;
				break;
			default : 
        		std::cout << "Send failed." << std::endl;
				break;
		}
	}
}


void mqttWrapper::subscribeTopic(const char *topic)
{
	// subscribe(int *mid, const char *sub)
    int ret = subscribe(NULL, topic);
	if (ret != MOSQ_ERR_SUCCESS) {
		switch (ret) {
			case MOSQ_ERR_NO_CONN: 
				std::cout << "Subcribe failed. not connected a broker." << std::endl;
				break;
			default : 
        		std::cout << "Subscribe failed." << std::endl;
				break;
		}
	}
}

void mqttWrapper::unsubscribeTopic(const char *topic)
{
    int ret = unsubscribe(NULL, topic);
    if (ret != MOSQ_ERR_SUCCESS){
        std::cout << "Unsubcribe topic: " << topic << "failed." << std::endl;
    }
}



void mqttWrapper::on_connect(int rc)
{
	connect_status = true;
    std::cout << "Broker connected." << std::endl;
}

void mqttWrapper::on_disconnect(int rc)
{
	connect_status = false;
	std::cout << "Broker disconnected." << std::endl;
}


void mqttWrapper::on_message(const struct mosquitto_message *message)
{
	if (recv_callback == nullptr) {
	    std::string payload = std::string(static_cast<char *>(message->payload));
	    std::string topic = std::string(message->topic);

    	std::cout << "topic: " << topic << std::endl;
	    std::cout << "QoS: " << message->mid << std::endl;
	    std::cout << "payload: " << std::string((char *)message->payload, message->payloadlen)<< std::endl;
	} else {
		// go to callback function handle
		recv_callback(message);
	}
}

void mqttWrapper::on_publish(int mid)
{
    std::cout << "Published." << std::endl;
}

void mqttWrapper::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    std::cout << "Subscribe successfully." << std::endl;
}

void mqttWrapper::on_unsubscribe(int mid)
{
    std::cout << "Unsubscribed." << std::endl;
}


