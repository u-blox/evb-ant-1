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

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "functional_tests.h"

typedef struct {
    char *name;
    command_callback_t callback;
} supported_command_t;

/**
 * Parses an incoming AT command and invokes the corresponding testing function
 */
char *parse_command(char *in_str, unsigned int in_length, uint8_t *out_length);

#endif
