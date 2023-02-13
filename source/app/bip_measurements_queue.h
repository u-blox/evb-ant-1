/*
 * Copyright 2023 u-blox
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BIP_MEASUREMENTS_QUEUE_H
#define BIP_MEASUREMENTS_QUEUE_H

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*
 * Capacity of the queue
 */
#define MEASUREMENTS_QUEUE_LENGTH 20

/*
 *  The struct that holds each measurement message.
 *  Right now it is plain text.
 *  Later this may be replaced by a struct with more meaningful fields
 *  representing the business logic of bluetooth positioning
 */
#define MEASUREMENT_MESSAGE_LENGTH 150

typedef struct measurement {
    uint8_t data[MEASUREMENT_MESSAGE_LENGTH];
} measurement_t;

/**
 * Initializes a FreeRTOS task-safe queue object purposed to store the incoming messages
 */
int measurements_queue_init(void);

/**
 * Adds a copy of the pointed message to the queue
 */
void add_measurement_to_queue(measurement_t *m);

/**
 * Dequeues a message if available and copies it to the given buffer
 * If no message is available, the task blocks at this call
 */
int get_measurement_from_queue(measurement_t *m_out);

#endif
