#include "message_bus.h"

#include <stdlib.h>
#include <string.h>

struct message {
    struct message *next;
    uint16_t id;
    void *payload;
    size_t size;
};

struct message_list {
    struct message *first;
    struct message *last;
};

struct listener {
    struct listener *next;
    uint16_t id;
    message_callback callback;
};

struct listener_list {
    struct listener *first;
    struct listener *last;
};

static struct message_list messages[2] = {{0}, {0}};
static size_t current_messages_list = 0;

static struct listener_list listeners = {0};

static struct message_list *get_current_messages(void)
{
    return &messages[current_messages_list];
}

static struct message_list *get_next_messages(void)
{
    return &messages[1 - current_messages_list];
}

static void swap_messages(void)
{
    current_messages_list = 1 - current_messages_list;
}

bool register_listener(uint16_t message_id, message_callback callback)
{
    if (callback == NULL) {
        return false;
    }

    struct listener *listener = calloc(1, sizeof(struct listener));
    if (listener) {
        listener->id = message_id;
        listener->callback = callback;
    } else {
        return false;
    }

    if (listeners.last) {
        listeners.last->next = listener;
        listeners.last = listeners.last->next;
    } else {
        listeners.first = listener;
        listeners.last = listeners.first;
    }
    return true;
}

bool send_message(uint16_t message_id, const void *payload, size_t size)
{
    struct message *message = calloc(1, sizeof(struct message));

    if (message) {
        if (payload && (size > 0)) {
            message->payload = calloc(size, sizeof(uint8_t));
            if (message->payload) {
                memcpy(message->payload, payload, size);
                message->size = size;
            } else {
                free(message);
                return false;
            }
        }
        message->id = message_id;
    } else {
        return false;
    }

    struct message_list *next_messages = get_next_messages();
    if (next_messages->last) {
        next_messages->last->next = message;
        next_messages->last = next_messages->last->next;
    } else {
        next_messages->first = message;
        next_messages->last = next_messages->first;
    }
    return true;
}

void notify_listeners(void)
{
    swap_messages();

    struct message_list *current_messages = get_current_messages();
    struct message *message = current_messages->first;
    while (message) {
        for (struct listener *listener = listeners.first; listener != NULL; listener = listener->next) {
            if (message->id == listener->id) {
                listener->callback(message->payload, message->size);
            }
        }
        struct message *next_message = message->next;
        free(message->payload);
        free(message);
        message = next_message;
    }
    current_messages->first = NULL;
    current_messages->last = NULL;
}