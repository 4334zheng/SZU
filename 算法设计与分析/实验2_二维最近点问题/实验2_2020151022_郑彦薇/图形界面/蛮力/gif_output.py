from moviepy.editor import *
clip = VideoFileClip(r"C:\Users\4334\Desktop\mp4\test.mp4")
clip = clip.set_duration(clip.duration)
clip.write_gif("output.gif",fps=5)