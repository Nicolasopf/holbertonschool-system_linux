#!/usr/bin/python3
''' Change a string inside a running process '''
from sys import argv

if __name__ == "__main__":
    if len(argv) != 4:
        print("Usage {} pid search_string replace_string".format(argv[0]))
        exit(1)

    pid = argv[1]
    search_string = argv[2]
    replace_string = argv[3]

    maps_path = '/proc/{}/maps'.format(pid)
    mem_path = '/proc/{}/mem'.format(pid)

    with open(maps_path) as file:
        for line in file:
            if "[heap]" in line:
                map_data = line.split()
                mem_addresses = map_data[0].split("-")
                start_address = int(mem_addresses[0], 16)
                ending_address = int(mem_addresses[1], 16)
                print(start_address, ending_address)
                break

    with open('/proc/{}/mem'.format(pid), 'rb+') as mem_file:
        # file is the mem binary image file where to seek address.
        mem_file.seek(start_address)
        mem = mem_file.read(ending_address - start_address)
        try:
            str_address = mem.index(bytes(search_string, "ASCII"))
        except:
            print("Can't find '{}'".format(search_string))
            exit(1)
        print("[*] Found '{}' at {:x}".format(search_string, str_address))
        print("[*] Writing new string")
        mem_file.seek(start_address + str_address)  # Go to the str address.
        mem_file.write(bytes(replace_string, "ASCII"))
