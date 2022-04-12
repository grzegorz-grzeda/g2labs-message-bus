#include <stdio.h>
#include <message_bus.h>

void cb1(void *bus, uint16_t message_id, const void *payload, size_t size)
{
    (void) bus;
    (void) message_id;
    (void) payload;
    (void) size;
    printf("Callback 1\n");
}

void cb2(void *bus, uint16_t message_id, const void *payload, size_t size)
{
    (void) bus;
    (void) message_id;
    (void) payload;
    (void) size;
    printf("Callback 2\n");
}

void cb3(void *bus, uint16_t message_id, const void *payload, size_t size)
{
    (void) message_id;
    (void) payload;
    (void) size;
    printf("Callback 3\n");
    message_bus_send_message(bus, 4, NULL, 0);
    printf("--> sending message id:4\n");
    message_bus_send_message(bus, 1, NULL, 0);
    printf("--> sending message id:1\n");
}

void cb4(void *bus, uint16_t message_id, const void *payload, size_t size)
{
    (void) bus;
    (void) message_id;
    (void) payload;
    (void) size;
    printf("Callback 4\n");
}

int main(void)
{
    struct message_bus *bus = message_bus_init(4, 4, 0);
    message_bus_register_listener(bus, 1, cb1);
    message_bus_register_listener(bus, 2, cb2);
    message_bus_register_listener(bus, 3, cb3);
    message_bus_register_listener(bus, 4, cb4);

    message_bus_send_message(bus, 2, NULL, 0);
    message_bus_send_message(bus, 1, NULL, 0);
    message_bus_send_message(bus, 3, NULL, 0);

    message_bus_notify_listeners(bus); // process msg 2, 1, 3
    message_bus_notify_listeners(bus); // process msg 4, 1

    message_bus_notify_listeners(bus); // nothing to process here

    return 0;
}