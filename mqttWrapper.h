#ifndef MQTTWRAPPER_H
#define MQTTWRAPPER_H

#include <mosquittopp.h>
#include <string>




class mqttWrapper : public mosqpp::mosquittopp
{

public:

	// message receive callback function type define
	typedef void (*recv_callback_t)(const struct mosquitto_message *);

    mqttWrapper(const char* id_, const char* host_, int port_);
    ~mqttWrapper();

	// This is must be called before calling connectBroker.
	void setAccount(const char *name, const char *passwd);
	// connect to MQTT broker
	void connectBroker(void);

	// subscribe topic
	void subscribeTopic(const char *topic);
	// unsubscribe topic
	void unsubscribeTopic(const char *topic);
	// publish message of topic
    void publishTopic(const char *topic, char *message);

	// register message recevice callback
	void register_recv_callback(void (*recv_callback_func)(const struct mosquitto_message *)) {
		recv_callback = recv_callback_func;
	}

	// broker connect status
	bool connect_status;

private:
	// event callback function
    void on_connect(int rc);
	void on_disconnect(int rc);
	void on_message(const struct mosquitto_message *message);
    void on_publish(int mid);
	void on_subscribe(int mid, int qos_count, const int *granted_qos);
	void on_unsubscribe(int mid);

	// callback porter
	recv_callback_t recv_callback = nullptr;

	// MQTT broker connect information
    std::string host;
	std::string id;
	std::string username;
	std::string password;
    int port;
	int keepalive;
};


#endif

