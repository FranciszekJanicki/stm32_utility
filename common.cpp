#include "usart.h"

#ifdef __cplusplus
extern "C" {
#endif

int _write(int file, uint8_t* p, int len)
{
    if (HAL_UART_Transmit(&huart2, p, len, len) == HAL_OK) {
        return len;
    }
    return 0;
}

#ifdef __cplusplus
}
#endif