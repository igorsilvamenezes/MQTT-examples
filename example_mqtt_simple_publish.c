#include <stdio.h>
#include <mosquitto.h>
#include <string.h>

void on_connect(struct mosquitto *mosq, void *obj, int result)
{
    char *message = "Hello World!!!";
    printf("Connected to broker!\n");
    mosquitto_publish(mosq, NULL, "/test", strlen(message), message, 0, false);
}

int main()
{
    int rc;
    struct mosquitto *mosq;

    mosquitto_lib_init();
    mosq = mosquitto_new("publisher", true, NULL);
    mosquitto_connect_callback_set(mosq, on_connect);
    rc = mosquitto_connect(mosq, "localhost", 1883, 60);

    while(rc == MOSQ_ERR_SUCCESS){
        rc = mosquitto_loop(mosq, -1, 1);
    }

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}