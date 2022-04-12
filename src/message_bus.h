#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef void (*message_bus_message_callback)(void *bus,uint16_t message_id, const void *payload, size_t size);

struct message_bus_message {
    uint16_t id;
    void *payload;
    size_t size;
};

struct message_bus_messages_group {
    struct message_bus_message *messages;
    size_t count;
};

struct message_bus_messages {
    struct message_bus_messages_group group[2];
    size_t max_number_of_messages;
    size_t max_payload_size;
    uint32_t messages_group_selector;
};

struct message_bus_listener {
    uint16_t id;
    message_bus_message_callback callback;
};

struct message_bus_listeners {
    struct message_bus_listener *listeners;
    size_t max_number_of_listeners;
    size_t count;
};

struct message_bus {
    struct message_bus_messages messages;
    struct message_bus_listeners listeners;
};

struct message_bus *message_bus_init(size_t max_number_of_listeners, size_t max_number_of_messages,
                                     size_t max_payload_size);

bool message_bus_register_listener(struct message_bus *bus, uint16_t message_id, message_bus_message_callback callback);

bool message_bus_send_message(struct message_bus *bus, uint16_t message_id, const void *payload, size_t size);

bool message_bus_notify_listeners(struct message_bus *bus);

#endif // MESSAGE_BUS_H