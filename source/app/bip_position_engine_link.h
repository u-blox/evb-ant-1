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

#ifndef BIP_POSITION_ENGINE_LINK_H_
#define BIP_POSITION_ENGINE_LINK_H_

#include <app/bip_tasks.h>

/**
 *  Creates the task that is responsible to send the measurements messages to the position engine
 *  The task waits for available messages in the queue and once it finds one, it sends it over UDP
 *  to the configured position engine endpoint
 */
void position_engine_link_init(void);

#endif /* POSITION_ENGINE_LINK_H_ */
