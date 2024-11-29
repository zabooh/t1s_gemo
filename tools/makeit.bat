set TOOL_PATH="c:\Program Files\Microchip\MPLABX\v6.20\gnuBins\GnuWin32\bin"

pushd .
cd ..\apps\tcpip_iperf_lan865x\firmware\tcpip_iperf_10base_t1s_freertos.X
%TOOL_PATH%\make CONF=FreeRTOS -j 8
%TOOL_PATH%\make CONF=FreeRTOS_Nd_1 -j 8
%TOOL_PATH%\make CONF=FreeRTOS_Nd_2 -j 8
%TOOL_PATH%\make CONF=FreeRTOS_Nd_3 -j 8
popd

