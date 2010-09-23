#! /usr/bin/env python
import sys

def conversor(line):
    bases = list(line.strip("T\n"))
    result=""
    for base in bases:
        if base == "0":
            result += "A"
        elif base == "1":
            result += "C"
        elif base == "2":
            result += "G"
        elif base == "3":
            result += "T"

    print result

def main():
    print ""
    for line in sys.stdin.readlines():
        if line.startswith(">"):
            new_line = ">> " + line.strip(">")
            sys.stdout.write(new_line)
        elif line.startswith("T"):
            conversor(line)

main()
