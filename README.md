# GPS2CAN
This porjects implements the functionality for a STM32F303K8T6 to communicate with a ublox cam-m8c GPS reiver and sends the data via CAN to other devices. 

## Attention
1. Once you change the baudrate between the receiver and STM32 make sure to disconnect the reiver from supply volateg for a short amount of time otherwise wrong baudrate is set internally in the receiver.
2. The request frequency from the microcontroller to the GPS must not be exactly the frequency of the GPS. This leads to checksum errors, presumably because the clocks drift.
