#include <stdio.h>
#include <unistd.h>
#include <mosquitto.h>
#include <string.h>

void on_connect(struct mosquitto *mosq, void *onj, int result)
{
    printf("connected to broker\n");
}

int main()
{
    int rc;
    int counter = 0;
    char message[100];
    struct mosquitto *mosq;

    mosquitto_lib_init();
    mosq = mosquitto_new("publisher", true, NULL);
    mosquitto_connect_callback_set(mosq, on_connect);
    rc = mosquitto_connect(mosq, "localhost", 1883, 60);

    while(rc == MOSQ_ERR_SUCCESS){
        rc = mosquitto_loop(mosq, -1, 1);
        sprintf(message, "message %d", counter++);
        mosquitto_publish(mosq, NULL, "/test", strlen(message), message, 0, false);
        sleep(5);
    }

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}