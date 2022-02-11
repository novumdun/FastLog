#!/usr/bin/env python
#
# Redirect data from a TCP/IP connection to a serial port and vice versa.
#
# (C) 2002-2020 Chris Liechti <cliechti@gmx.net>
#
# SPDX-License-Identifier:    BSD-3-Clause

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
# from goto import with_goto

# ./tcp_serial_redirect.py COM11 115200 -P 2217

sem = Semaphore(0)
cmd_strs = [None for i in range(16)]
cmd_strs_w = 0
cmd_strs_r = 0

c_print_socket = None


class FrameRx:
    def __init__(self):
        self.frame_data = bytearray(1024)
        self.frame_cnt = 0
        self.frame_len = 0

        self.not_frame_data = bytearray(1024)
        self.not_frame_cnt = 0

        record_json_f = open(r"./fast_print_lines.json", mode='r')
        context = record_json_f.read()
        record_json_f.close()
        self.record_items = json.loads(context)

    def frame_deal(self, datas):
        global cmd_strs, cmd_strs_w, sem

        addr = str(int(datas[2]) + (int(datas[3]) << 8))
        if addr in self.record_items:
            item = self.record_items[addr]

            args_p = 4
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
                        value = int.from_bytes(arg, byteorder='little', signed=True)
                    elif 0 == (arg_t & 0x01):
                        value = int.from_bytes(arg, byteorder='little', signed=False)

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
            # print(str_array.value.decode('utf-8'))

            if c_print_socket is not None:
                c_print_socket.sendall(bytes(str_array))

    # @with_goto
    def rxdeal(self, datas):
        self.not_frame_cnt = 0
        datas_p = datas

        # label .redeal
        redeal = True
        while(redeal):
            redeal = False
            for i in range(len(datas_p)):
                data = datas_p[i]
                # if self.frame_cnt:
                #     print(str(int(data[0])))
                if 0 == self.frame_cnt:
                    if bytes([0xA8])[0] == data:
                        self.frame_data[self.frame_cnt] = data
                        self.frame_cnt += 1
                        # print('Rx')
                    else:
                        self.not_frame_data[self.not_frame_cnt] = data
                        self.not_frame_cnt += 1
                elif 1 == self.frame_cnt:
                    self.frame_data[self.frame_cnt] = data
                    self.frame_len = int(data)
                    self.frame_cnt += 1
                elif self.frame_cnt < (self.frame_len + 1):
                    self.frame_data[self.frame_cnt] = data
                    self.frame_cnt += 1
                elif self.frame_cnt == (self.frame_len + 1):
                    if bytes([0x55])[0] == data:
                        self.frame_data[self.frame_cnt] = data
                        self.frame_cnt += 1
                        self.frame_deal(self.frame_data[0:self.frame_cnt + 1])
                        self.frame_cnt = 0
                        self.frame_len = 0
                    else:
                        self.frame_cnt = 0
                        self.frame_len = 0
                        self.not_frame_data[self.not_frame_cnt] = data
                        self.not_frame_cnt += 1
                        datas_p = datas_p[1:]
                        # goto .redeal
                        redeal = True
        return bytes(self.not_frame_data[0: self.not_frame_cnt])


class SerialToNet(serial.threaded.Protocol):
    """serial->socket"""

    framerx = FrameRx()

    def __init__(self):
        self.socket = None

    def __call__(self):
        return self

    def data_received(self, data):
        datas = self.framerx.rxdeal(data)
        if self.socket is not None:
            self.socket.sendall(datas)


if __name__ == '__main__':  # noqa
    import argparse

    parser = argparse.ArgumentParser(
        description='Simple Serial to Network (TCP/IP) redirector.',
        epilog="""\
NOTE: no security measures are implemented. Anyone can remotely connect
to this service over the network.

Only one connection at once is supported. When the connection is terminated
it waits for the next connect.
""")

    parser.add_argument(
        'SERIALPORT',
        help="serial port name")

    parser.add_argument(
        'BAUDRATE',
        type=int,
        nargs='?',
        help='set baud rate, default: %(default)s',
        default=9600)

    parser.add_argument(
        '-q', '--quiet',
        action='store_true',
        help='suppress non error messages',
        default=False)

    parser.add_argument(
        '--develop',
        action='store_true',
        help='Development mode, prints Python internals on errors',
        default=False)

    group = parser.add_argument_group('serial port')

    group.add_argument(
        "--bytesize",
        choices=[5, 6, 7, 8],
        type=int,
        help="set bytesize, one of {5 6 7 8}, default: 8",
        default=8)

    group.add_argument(
        "--parity",
        choices=['N', 'E', 'O', 'S', 'M'],
        type=lambda c: c.upper(),
        help="set parity, one of {N E O S M}, default: N",
        default='N')

    group.add_argument(
        "--stopbits",
        choices=[1, 1.5, 2],
        type=float,
        help="set stopbits, one of {1 1.5 2}, default: 1",
        default=1)

    group.add_argument(
        '--rtscts',
        action='store_true',
        help='enable RTS/CTS flow control (default off)',
        default=False)

    group.add_argument(
        '--xonxoff',
        action='store_true',
        help='enable software flow control (default off)',
        default=False)

    group.add_argument(
        '--rts',
        type=int,
        help='set initial RTS line state (possible values: 0, 1)',
        default=None)

    group.add_argument(
        '--dtr',
        type=int,
        help='set initial DTR line state (possible values: 0, 1)',
        default=None)

    group = parser.add_argument_group('network settings')

    exclusive_group = group.add_mutually_exclusive_group()

    exclusive_group.add_argument(
        '-P', '--localport',
        type=int,
        help='local TCP port',
        default=7777)

    exclusive_group.add_argument(
        '-c', '--client',
        metavar='HOST:PORT',
        help='make the connection as a client, instead of running a server',
        default=False)

    args = parser.parse_args()

    # connect to serial port
    ser = serial.serial_for_url(args.SERIALPORT, do_not_open=True)
    ser.baudrate = args.BAUDRATE
    ser.bytesize = args.bytesize
    ser.parity = args.parity
    ser.stopbits = args.stopbits
    ser.rtscts = args.rtscts
    ser.xonxoff = args.xonxoff

    if args.rts is not None:
        ser.rts = args.rts

    if args.dtr is not None:
        ser.dtr = args.dtr

    if not args.quiet:
        sys.stderr.write(
            '--- TCP/IP to Serial redirect on {p.name}  {p.baudrate},{p.bytesize},{p.parity},{p.stopbits} ---\n'
            '--- type Ctrl-C / BREAK to quit\n'.format(p=ser))

    try:
        ser.open()
    except serial.SerialException as e:
        sys.stderr.write('Could not open serial port {}: {}\n'.format(ser.name, e))
        sys.exit(1)

    ser_to_net = SerialToNet()
    serial_worker = serial.threaded.ReaderThread(ser, ser_to_net)
    serial_worker.start()

    if not args.client:
        srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        srv.bind(('', args.localport))
        srv.listen(1)
    try:
        intentional_exit = False
        while True:
            if args.client:
                host, port = args.client.split(':')
                sys.stderr.write("Opening connection to {}:{}...\n".format(host, port))
                client_socket = socket.socket()
                try:
                    client_socket.connect((host, int(port)))
                except socket.error as msg:
                    sys.stderr.write('WARNING: {}\n'.format(msg))
                    time.sleep(5)  # intentional delay on reconnection as client
                    continue
                sys.stderr.write('Connected\n')
                client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
                #~ client_socket.settimeout(5)
            else:
                sys.stderr.write('Waiting for connection on {}...\n'.format(args.localport))
                client_socket, addr = srv.accept()
                sys.stderr.write('Connected by {}\n'.format(addr))
                # More quickly detect bad clients who quit without closing the
                # connection: After 1 second of idle, start sending TCP keep-alive
                # packets every 1 second. If 3 consecutive keep-alive packets
                # fail, assume the client is gone and close the connection.
                try:
                    client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, 1)
                    client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, 1)
                    client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, 3)
                    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
                except AttributeError:
                    pass  # XXX not available on windows
                client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
            try:
                ser_to_net.socket = client_socket
                c_print_socket = client_socket
                # enter network <-> serial loop
                while True:
                    try:
                        data = client_socket.recv(1024)
                        if not data:
                            break
                        print(data)
                        ser.write(data)                 # get a bunch of bytes and send them
                    except socket.error as msg:
                        if args.develop:
                            raise
                        sys.stderr.write('ERROR: {}\n'.format(msg))
                        # probably got disconnected
                        break
            except KeyboardInterrupt:
                intentional_exit = True
                raise
            except socket.error as msg:
                if args.develop:
                    raise
                sys.stderr.write('ERROR: {}\n'.format(msg))
            finally:
                ser_to_net.socket = None
                c_print_socket = None
                sys.stderr.write('Disconnected\n')
                client_socket.close()
                if args.client and not intentional_exit:
                    time.sleep(5)  # intentional delay on reconnection as client
    except KeyboardInterrupt:
        pass

    sys.stderr.write('\n--- exit ---\n')
    serial_worker.stop()
