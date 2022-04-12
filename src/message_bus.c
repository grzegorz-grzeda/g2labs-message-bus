#include "message_bus.h"

#include <stdlib.h>
#include <string.h>

static struct message_bus_messages_group *get_current_message_group(struct message_bus *bus)
{
    return &bus->messages.group[bus->messages.messages_group_selector];
}

static struct message_bus_messages_group *get_next_message_group(struct message_bus *bus)
{
    return &bus->messages.group[1 - bus->messages.messages_group_selector];
}

static void swap_message_group(struct message_bus *bus)
{
    bus->messages.messages_group_selector = 1 - bus->messages.messages_group_selector;
}

static void init_messages(struct message_bus_messages *messages, size_t max_number_of_messages, size_t max_payload_size)
{
    messages->max_number_of_messages = max_number_of_messages;
    messages->max_payload_size = max_payload_size;
    for (int i = 0; i < 2; i++) {
        messages->group[i].messages = calloc(max_number_of_messages, sizeof(struct message_bus_message));
        if (max_payload_size) {
            for (size_t j = 0; j < max_number_of_messages; j++) {
                messages->group[i].messages[j].payload = calloc(max_payload_size, sizeof(uint8_t));
            }
        }
    }
}

static void init_listeners(struct message_bus_listeners *listeners, size_t max_number_of_listeners)
{
    listeners->max_number_of_listeners = max_number_of_listeners;
    listeners->listeners = calloc(listeners->max_number_of_listeners, sizeof(struct message_bus_listener));
}

struct message_bus *message_bus_init(size_t max_number_of_listeners, size_t max_number_of_messages,
                                     size_t max_payload_size)
{
    if (!max_number_of_listeners || !max_number_of_messages) {
        return NULL;
    }
    struct message_bus *bus = calloc(1, sizeof(struct message_bus));
    init_messages(&bus->messages, max_number_of_messages, max_payload_size);
    init_listeners(&bus->listeners, max_number_of_listeners);
    return bus;
}

bool message_bus_register_listener(struct message_bus *bus, uint16_t message_id, message_bus_message_callback callback)
{
    if (!bus || !callback || (bus->listeners.count == bus->listeners.max_number_of_listeners)) {
        return false;
    }
    bus->listeners.listeners[bus->listeners.count].id = message_id;
    bus->listeners.listeners[bus->listeners.count].callback = callback;
    bus->listeners.count++;
    return true;
}

bool message_bus_send_message(struct message_bus *bus, uint16_t message_id, const void *payload, size_t size)
{
    if (!bus || ((size > 0) && !payload)) {
        return false;
    }
    struct message_bus_messages_group *group = get_next_message_group(bus);
    if (group->count >= bus->messages.max_number_of_messages) {
        return false;
    }
    group->messages[group->count].id = message_id;
    group->messages[group->count].size = size;
    memcpy(group->messages[group->count].payload, payload, size);
    group->count++;
    return true;
}

bool message_bus_notify_listeners(struct message_bus *bus)
{
    if (!bus) {
        return false;
    }
    swap_message_group(bus);
    struct message_bus_messages_group *group = get_current_message_group(bus);
    for (size_t i = 0; i < group->count; i++) {
        struct message_bus_message *current_message = &group->messages[i];
        for (size_t j = 0; j < bus->listeners.count; j++) {
            struct message_bus_listener *current_listener = &bus->listeners.listeners[j];
            if (current_message->id == current_listener->id) {
                current_listener->callback(bus, current_message->id, current_message->payload, current_message->size);
            }
        }
    }
    group->count = 0;
    return true;
}