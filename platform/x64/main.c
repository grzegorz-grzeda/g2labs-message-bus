#include <stdio.h>
#include <message_bus.h>

void cb1(uint16_t message_id, const void *payload, size_t size)
{
    (void) message_id;
    (void) payload;
    (void) size;
    printf("Callback 1\n");
}

void cb2(uint16_t message_id, const void *payload, size_t size)
{
    (void) message_id;
    (void) payload;
    (void) size;
    printf("Callback 2\n");
}

void cb3(uint16_t message_id, const void *payload, size_t size)
{
    (void) message_id;
    (void) payload;
    (void) size;
    printf("Callback 3\n");
    send_message(4, NULL, 0);
    printf("--> sending message id:4\n");
    send_message(1, NULL, 0);
    printf("--> sending message id:1\n");
}

void cb4(uint16_t message_id, const void *payload, size_t size)
{
    (void) message_id;
    (void) payload;
    (void) size;
    printf("Callback 4\n");
}

int main(void)
{
    register_listener(1, cb1);
    register_listener(2, cb2);
    register_listener(3, cb3);
    register_listener(4, cb4);

    send_message(2, NULL, 0);
    send_message(1, NULL, 0);
    send_message(3, NULL, 0);

    notify_listeners(); // process msg 2, 1, 3
    notify_listeners(); // process msg 4, 1

    notify_listeners(); // nothing to process here

    return 0;
}