from moviepy.editor import *
clip = VideoFileClip(r"C:\Users\4334\Desktop\test1.mp4")
clip = clip.set_duration(clip.duration)
clip.write_gif("divide_output.gif",fps=1)