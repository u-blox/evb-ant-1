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

#ifndef BIP_NINA_GPIOS_H_
#define BIP_NINA_GPIOS_H_

/**
 *  Pulls low the Gpio pin that drives the NINA Reset pin and then releases it
 */
void nina_apply_reset(void);

/**
 *  Pulls low the Gpio pin that drives the NINA Switch 1 pin and then releases it
 */
void nina_apply_sw1(void);

/**
 *  Pulls low the Gpio pin that drives the NINA Switch 2 pin and then releases it
 */
void nina_apply_sw2(void);

#endif /* NINA_GPIOS_H_ */
