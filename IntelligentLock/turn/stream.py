import os
import time

os.system("mjpg_streamer -i \"input_uvc.so -d /dev/video0 -r 213x160 -f 25\" -o \"output_http.so -p 8080 -w /www/webcam\" &")
time.sleep(5)
os.system("python takeaturn.py 1234")

