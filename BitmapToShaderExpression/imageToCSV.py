import os
import sys
import matplotlib.pyplot as plt
import numpy

pixelMax = 255
path = "C:\\Users\\John\\source\\repos\\BitmapToShaderExpression\\BitmapToShaderExpression\\GXvmX_64_64.png"

image = plt.imread(path)

print(str(image.shape)[1:-1])
for i in range(0, image.shape[0]):
	for j in range(0, image.shape[1]):
		data = [i] + [j] + (image[i,j,] * pixelMax).tolist()
		dataString = ', '.join(map(str,data))
		print(dataString)
