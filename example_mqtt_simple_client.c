#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>

void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
    printf("Connected with code %d.\n", rc);
    if(rc == 0){
        mosquitto_subscribe(mosq, NULL, "/test", 0);
    }
}

void on_message(struct mosquitto *mosq, void *obj, 
    const struct mosquitto_message *message)
{
    printf("Received message '%.*s' from topic '%s'\n", 
        message->payloadlen,
        (char*) message->payload,
        message->topic);
}

int main()
{
    mosquitto_lib_init();
    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    if(mosquitto_connect(mosq, "localhost", 1883, 60)){
        fprintf(stderr, "Unable to connect.\n");
        return 1;
    }

    mosquitto_loop_forever(mosq, -1, 1);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}