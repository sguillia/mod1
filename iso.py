#!/usr/bin/python

points = [
(0, 0, 0),
(0, 10, 0),
(10, 10, 0),
(10, 0, 0),
(0, 0, 10),
(0, 10, 10),
(10, 10, 10),
(10, 0, 10)
]

#mapx = int(input("x: "))
#mapy = int(input("y: "))

for point in points:
	mapx = point[0]
	mapy = point[1]
	mapz = point[2]
	screenx = mapx - mapy
	screeny = mapx + mapy + mapz
	print "From (%d, %d, %d) to (%d, %d)" % (mapx, mapy, mapz, screenx, screeny)

