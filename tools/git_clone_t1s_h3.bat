@ECHO OFF

set H3_GITHUB="https://github.com/Microchip-MPLAB-Harmony"
set H3_INSTALL="../../h3"

git clone -b "v10.5.1"              https://github.com/ARM-software/CMSIS-FreeRTOS %H3_INSTALL%/CMSIS-FreeRTOS
git clone -b "5.9.0"                https://github.com/ARM-software/CMSIS_5 %H3_INSTALL%/CMSIS_5
git clone -b "v3.18.1"              %H3_GITHUB%/csp.git  %H3_INSTALL%/csp   
git clone -b "v3.13.1"              %H3_GITHUB%/core.git %H3_INSTALL%/core    
git clone -b "v5.4.0"               %H3_GITHUB%/wolfssl.git %H3_INSTALL%/wolfssl
git clone -b "v3.11.0"              %H3_GITHUB%/net.git %H3_INSTALL%/net
git clone -b "v3.8.1"               %H3_GITHUB%/crypto.git %H3_INSTALL%/crypto     
git clone -b "v1.1.0"               %H3_GITHUB%/devices.git %H3_INSTALL%/Devices
git clone -b "v1.3.2"               %H3_GITHUB%/net_10base_t1s.git  %H3_INSTALL%/net_10base_t1s  

@ECHO ON

