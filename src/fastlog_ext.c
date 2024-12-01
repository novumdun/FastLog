#include <stdarg.h>
#include <stdio.h>
#include <board.h>

void console_output_bin(char *buff, int data_len)
{
    os_device_t *console = os_console_get_device();

    if (console == OS_NULL)
    {
        ;
    }
    else
    {
        int count = 0;
        int size = data_len;

        while (count < size)
        {
            count = os_device_write_nonblock(console, 0, buff + count, size - count);
            if (count < 0)
            {
                return;
            }
        }
    }
    return;
}