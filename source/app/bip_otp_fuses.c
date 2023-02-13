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

#include <app/bip_otp_fuses.h>


static unsigned long long OTP_unique_id;
static unsigned long long OTP_mac;

static unsigned char mac_addr_array[6];

void readOTP()
{
    static int already_read = 0;
    if (already_read) {
        return;
    }

#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
    OCOTP_Init(OCOTP, OCOTP_FREQ_HZ);
#else
    OCOTP_Init(OCOTP, 0U);
#endif

    PRINTF("OCOTP controller version: 0x%08X\r\n\r\n", OCOTP_GetVersion(OCOTP));

    uint32_t fuseData0 = 0;
    uint32_t fuseData1 = 0;

    if (kStatus_Success != OCOTP_ReadFuseShadowRegisterExt(OCOTP, UNIQUE_ID_ADDR_0, &fuseData0, 1)) {
        PRINTF("Could not read fuse data\r\n");
    }

    if (kStatus_Success != OCOTP_ReadFuseShadowRegisterExt(OCOTP, UNIQUE_ID_ADDR_1, &fuseData1, 1)) {
        PRINTF("Could not read fuse data\r\n");
    }

    OTP_unique_id = ((unsigned long long)fuseData0 << 32) | fuseData1;

    if (kStatus_Success != OCOTP_ReadFuseShadowRegisterExt(OCOTP, MAC_0, &fuseData0, 1)) {
        PRINTF("Could not read fuse data\r\n");
    }

    if (kStatus_Success != OCOTP_ReadFuseShadowRegisterExt(OCOTP, MAC_1, &fuseData1, 1)) {
        PRINTF("Could not read fuse data\r\n");
    }

    OTP_mac = ((unsigned long long)fuseData1 << 32) | fuseData0;

    already_read = 1;
}

unsigned char *mac_addr_arr_from_u64(unsigned long long input)
{
    int i;

    for (i = 5; i >= 0; i--) {
        mac_addr_array[i] = (char)(input & 0xff);
        input = input >> 8;
    }

    return mac_addr_array;
}

unsigned char *get_mac_addr_array_from_OTP(void)
{
    readOTP();

    if (OTP_mac) {
        return mac_addr_arr_from_u64(OTP_mac);
    } else {
        return mac_addr_arr_from_u64(OTP_unique_id);
    }

}

unsigned long long get_unique_id_from_OTP(void)
{
    readOTP();
    return OTP_unique_id;
}

unsigned long long get_mac_from_OTP(void)
{
    readOTP();
    return OTP_mac;
}
