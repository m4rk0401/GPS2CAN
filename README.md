# GPS2CAN
This porjects implements the functionality for a STM32F303K8T6 to communicate with a ublox cam-m8c GPS reiver and sends the data via CAN to other devices. 

## Attention
Once you change the baudrate between the receiver and STM32 make sure to disconnect the reiver from supply volateg for a short amount of time otherwise wrong baudrate is set internally in the receiver.
