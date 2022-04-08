#ifndef MESSAGE_BUS_H
#define MESSAGE_BUS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef void (*message_callback)(uint16_t message_id, const void *payload, size_t size);

bool register_listener(uint16_t message_id, message_callback callback);

bool send_message(uint16_t message_id, const void *payload, size_t size);

void notify_listeners(void);

#endif // MESSAGE_BUS_H