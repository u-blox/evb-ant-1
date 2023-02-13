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

#include <app/bip_non_volatile_storage.h>
#include <task.h>

/*! @brief config serial NOR option  */
static serial_nor_config_option_t option = {
    .option0.U = 0xc0000007U,
    .option1.U = 0U,
};


/*! @brief FLEXSPI NOR flash driver Structure */
static flexspi_nor_config_t norConfig;
/*! @brief Buffer for program */
static uint8_t s_buffer[BUFFER_LEN];
/*! @brief Buffer for readback */
static uint8_t s_buffer_rbc[BUFFER_LEN];

static uint32_t serialNorTotalSize;
static uint32_t serialNorSectorSize;
static uint32_t serialNorPageSize;


/*
 * @brief Gets called when an error occurs.
 *
 * @details Print error message and trap forever.
 */
static void error_trap(void)
{
    PRINTF("\r\n\r\n\r\n\t---- HALTED DUE TO FLEXSPI NOR ERROR! ----");
    while (1) {
    }
}

static status_t FLEXSPI_NorFlash_GetVendorID(uint32_t instance, uint32_t *vendorID)
{
    uint32_t lut_seq[4];
    memset(lut_seq, 0, sizeof(lut_seq));
    // Read manufacturer ID
    lut_seq[0] = FSL_ROM_FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x9F, READ_SDR, FLEXSPI_1PAD, 4);
    ROM_FLEXSPI_NorFlash_UpdateLut(instance, NOR_CMD_LUT_SEQ_IDX_READID, (const uint32_t *)lut_seq, 1U);

    flexspi_xfer_t xfer;
    xfer.operation            = kFLEXSPIOperation_Read;
    xfer.seqId                = NOR_CMD_LUT_SEQ_IDX_READID;
    xfer.seqNum               = 1U;
    xfer.baseAddress          = 0U;
    xfer.isParallelModeEnable = false;
    xfer.rxBuffer             = vendorID;
    xfer.rxSize               = 1U;

    uint32_t status = ROM_FLEXSPI_NorFlash_CommandXfer(instance, &xfer);
    if (*vendorID != kSerialFlash_ISSI_ManufacturerID) {
        status = kStatus_ROM_FLEXSPINOR_Flash_NotFound;
        return status;
    }

    return status;
}

int store_to_flash(uint32_t relative_address, void *user_data_ptr, size_t user_data_size)
{
    status_t status;
    uint32_t i        = 0U;
    uint32_t serialNorAddress;        /* Address of the serial nor device location */
    uint32_t FlexSPISerialNorAddress; /* Address of the serial nor device in FLEXSPI memory */

    /*
     * SECTOR_INDEX_FROM_END = 1 means the last sector,
     * SECTOR_INDEX_FROM_END = 2 means (the last sector - 1) ...
     */

    taskENTER_CRITICAL();

    /* Erase a sector from target device dest address */
    serialNorAddress        = serialNorTotalSize - (SECTOR_INDEX_FROM_END * serialNorSectorSize);
    FlexSPISerialNorAddress = EXAMPLE_FLEXSPI_AMBA_BASE + serialNorAddress;

    FlexSPISerialNorAddress += relative_address;

    /* Erase one sector. */
    status = ROM_FLEXSPI_NorFlash_Erase(FlexSpiInstance, &norConfig, serialNorAddress, serialNorSectorSize);
    if (status != kStatus_Success) {
        error_trap();
    }

    /* Prepare user buffer. */

    memset(s_buffer, 0, BUFFER_LEN);

    for (i = 0; i < user_data_size; i++) {
        s_buffer[i] = ((uint8_t *)user_data_ptr)[i];
    }

    /* Program user buffer into FLEXSPI NOR flash */
    status =
        ROM_FLEXSPI_NorFlash_ProgramPage(FlexSpiInstance, &norConfig, serialNorAddress, (const uint32_t *)s_buffer);
    if (status != kStatus_Success) {
        error_trap();
    }

    DCACHE_InvalidateByRange(FlexSPISerialNorAddress, sizeof(s_buffer_rbc));
    /* Verify programming by reading back from FLEXSPI memory directly */
    memcpy(s_buffer_rbc, (void *)(FlexSPISerialNorAddress), sizeof(s_buffer_rbc));
    if (memcmp(s_buffer_rbc, s_buffer, sizeof(s_buffer)) != 0) {
        error_trap();
    }

    taskEXIT_CRITICAL();

    return 0;
}

char *read_from_flash(void)
{
    status_t status;
    uint32_t i        = 0U;
    uint32_t serialNorAddress;        /* Address of the serial nor device location */
    uint32_t FlexSPISerialNorAddress; /* Address of the serial nor device in FLEXSPI memory */

    /*
     * SECTOR_INDEX_FROM_END = 1 means the last sector,
     * SECTOR_INDEX_FROM_END = 2 means (the last sector - 1) ...
     */

    taskENTER_CRITICAL();

    /* Erase a sector from target device dest address */
    serialNorAddress        = serialNorTotalSize - (SECTOR_INDEX_FROM_END * serialNorSectorSize);
    FlexSPISerialNorAddress = EXAMPLE_FLEXSPI_AMBA_BASE + serialNorAddress;


    DCACHE_InvalidateByRange(FlexSPISerialNorAddress, sizeof(s_buffer_rbc));
    memcpy(s_buffer_rbc, (void *)(FlexSPISerialNorAddress), sizeof(s_buffer_rbc));

    PRINTF("\r\nFound in flash: %s\r\n", (char *)s_buffer_rbc);

    taskEXIT_CRITICAL();

    return (char *)s_buffer_rbc;
}

int initialize_flash(void)
{
    status_t status;
    uint32_t vendorID = 0U;

    /* Clean up FLEXSPI NOR flash driver Structure */
    memset(&norConfig, 0U, sizeof(flexspi_nor_config_t));

    /* Setup FLEXSPI NOR Configuration Block */
    status = ROM_FLEXSPI_NorFlash_GetConfig(FlexSpiInstance, &norConfig, &option);
    if (status == kStatus_Success) {
        PRINTF("\r\n Successfully got FLEXSPI NOR configuration block\r\n ");
    } else {
        PRINTF("\r\n Get FLEXSPI NOR configuration block failure!\r\n");
        error_trap();
    }

    /* Initializes the FLEXSPI module for the other FLEXSPI APIs */
    status = ROM_FLEXSPI_NorFlash_Init(FlexSpiInstance, &norConfig);
    if (status == kStatus_Success) {
        PRINTF("\r\n Successfully init FLEXSPI serial NOR flash\r\n ");
    } else {
        PRINTF("\r\n Erase sector failure !\r\n");
        error_trap();
    }

    /* Perform software reset after initializing flexspi module */
    ROM_FLEXSPI_NorFlash_ClearCache(FlexSpiInstance);

    /*  Probe device presence by verifying Manufacturer ID */
    status = FLEXSPI_NorFlash_GetVendorID(FlexSpiInstance, &vendorID);
    if (status == kStatus_Success) {
        PRINTF("\r\n Serial NOR flash has been found successfully\r\n ");
        PRINTF("Vendor ID: 0x%x\r\n", vendorID);
    } else {
        PRINTF("\r\n Serial flash can not be found!\r\n");
        error_trap();
    }

    serialNorTotalSize  = norConfig.memConfig.sflashA1Size;
    serialNorSectorSize = norConfig.sectorSize;
    serialNorPageSize   = norConfig.pageSize;

    /* Print serial NOR flash information */
    PRINTF("\r\n Serial NOR flash Information: ");
    PRINTF("\r\n Total program flash size:\t%d KB, Hex: (0x%x)", (serialNorTotalSize / 1024U), serialNorTotalSize);
    PRINTF("\r\n Program flash sector size:\t%d KB, Hex: (0x%x) ", (serialNorSectorSize / 1024U), serialNorSectorSize);
    PRINTF("\r\n Program flash page size:\t%d B, Hex: (0x%x)\r\n", serialNorPageSize, serialNorPageSize);

    return 0;
}
