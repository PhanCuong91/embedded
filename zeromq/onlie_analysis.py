#! /usr/bin/env python3

import zmq
import struct

topic = "Trace".encode('ascii')

print("Reading messages with topic: {}".format(topic))

with zmq.Context() as context:
    socket = context.socket(zmq.SUB)

    socket.connect("tcp://127.0.0.1:5555")
    socket.setsockopt(zmq.SUBSCRIBE, topic)

    i = 0

    try:
        while True:
            binary_topic, data_buffer = socket.recv().split(b' ', 1)
            print(binary_topic)
            print(data_buffer)
            topic = binary_topic.decode(encoding = 'ascii')
            # data_buffer = socket.recv()
            print("Message {:d}:".format(i))
            print("\ttopic: '{}'".format(topic))

            packet_size = len(data_buffer) // struct.calcsize("i")
            print(data_buffer)
            print("\tpacket size: {:d}".format(packet_size))

            struct_format = "{:d}i".format(packet_size)

            data = struct.unpack(struct_format, data_buffer)

            print("\tdata: {}".format(data))

            i += 1

    except KeyboardInterrupt:
        socket.close()
    except Exception as error:
        print("ERROR: {}".format(error))
        socket.close()
