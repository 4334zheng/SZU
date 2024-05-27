import numpy as np
import cv2
size = (640, 480)
#生成视频对象
videowrite = cv2.VideoWriter(r'C:\Users\4334\Desktop\test.mp4', -1, 5, size)
img_array = []
#读取图片
for filename in [r'C:\Users\4334\Desktop\graph\{0}.png'.format(i) for i in range(46)]:
    img = cv2.imread(filename)
    if img is None:
        continue
    img_array.append(img)
#将读取的图片写进去
for i in range(46):
    videowrite.write(img_array[i])
videowrite.release()
