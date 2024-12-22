import sys
import socket
import serial
import serial.threaded
import time

import json
import subprocess
import platform
from threading import Thread, Semaphore
from ctypes import *
import struct


def frame_deal(record_items, datas):
    global cmd_strs, cmd_strs_w, sem

    addr = str(int(datas[1]) + (int(datas[2]) << 8))
    if addr in record_items:
        item = record_items[addr]

        args_p = 3
        args_c = 0
        args_array = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        for idx, arg_len in enumerate(item['args']):
            if arg_len:
                arg_t = item['args_t'][idx]
                arg = datas[args_p: (args_p + arg_len)]
                if 7 == arg_t:
                    value = c_double(struct.unpack('f', arg)[0])
                elif 8 == arg_t:
                    value = c_double(struct.unpack('d', arg)[0])
                elif 1 == (arg_t & 0x01):
                    value = int.from_bytes(
                        arg, byteorder='little', signed=True)
                elif 0 == (arg_t & 0x01):
                    value = int.from_bytes(
                        arg, byteorder='little', signed=False)

                args_array[args_c] = value
                args_c += 1
                args_p += arg_len
        # print(args_array)

        str_array = create_string_buffer(1000)  #

        sys = platform.system()
        if sys == "Windows":
            msvcrt = cdll.msvcrt
            msvcrt.sprintf(str_array, bytes(item['str'] + '\r\n', encoding="utf-8"), args_array[0],
                           args_array[1],
                           args_array[2],
                           args_array[3],
                           args_array[4],
                           args_array[5],
                           args_array[6],
                           args_array[7],
                           args_array[8],
                           args_array[9])
        else:
            cdll.LoadLibrary("libc.so.6")
            libc = CDLL("libc.so.6")
            libc.sprintf(str_array, bytes(item['str'] + '\r\n', encoding="utf-8"), args_array[0],
                         args_array[1],
                         args_array[2],
                         args_array[3],
                         args_array[4],
                         args_array[5],
                         args_array[6],
                         args_array[7],
                         args_array[8],
                         args_array[9])
        print(str_array.value.decode('utf-8'))


record_json_f = open(r"/home/dengbo/workspace/cabin/FastLog/fastlog_out/fastlog_lines.json", mode='r')
records = record_json_f.read()
record_json_f.close()
record_items = json.loads(records)

fp = open('/home/dengbo/workspace/cabin/FastLog/flog', mode='rb')
context = fp.read()
while (context):
    size = int(context[0])
    if size > len(context):
        print('Err size')
        break
    frame_deal(record_items, context[0:size])
    context = context[size:]
