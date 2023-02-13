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

#ifndef BIP_NON_VOLATILE_STORAGE_H_
#define BIP_NON_VOLATILE_STORAGE_H_


#include "fsl_romapi.h"
#include "fsl_debug_console.h"
#include "fsl_cache.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_common.h"

#define FlexSpiInstance           0U
#define EXAMPLE_FLEXSPI_AMBA_BASE FlexSPI_AMBA_BASE
#define FLASH_SIZE                0x800000UL /* 8MBytes */
#define FLASH_PAGE_SIZE           256UL      /* 256Bytes */
#define FLASH_SECTOR_SIZE         0x1000UL   /* 4KBytes */
#define FLASH_BLOCK_SIZE          0x10000UL  /* 64KBytes */
#define BUFFER_LEN                FLASH_PAGE_SIZE
#define SECTOR_INDEX_FROM_END     1U

/**
 * Initializes and configures the FLEXSPI flash memory module
 */
int initialize_flash(void);

/**
 * Stores a memory block of specified size to flash
 * The memory block is copied to a buffer of page size (FLASH_PAGE_SIZE) and then written to flash as a whole
 */
int store_to_flash(uint32_t relative_address, void *user_data_ptr, size_t user_data_size);

/**
 *	A whole page is retrieved from flashed and copied to a static buffer
 *	Returns a pointer to that buffer
 */
char *read_from_flash(void);

#endif /* NON_VOLATILE_STORAGE_H_ */
