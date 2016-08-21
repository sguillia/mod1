#!/usr/bin/python

import sys
import string

if len(sys.argv) == 2:
	path = sys.argv[1]
else:
	sys.exit("Expeected one argument")

content = None

with open(path, 'r') as file:
    content = file.read()

if content is None:
	sys.exit("Failed to read file")

tab = string.split(content, " ")

for point in tab:
	point = point.strip()
	print point
