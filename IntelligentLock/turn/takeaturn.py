import web
import mraa
import os
import time
import thread

leftled = mraa.Gpio(17)
rightled = mraa.Gpio(16)
breakled = mraa.Gpio(15)

leftled.dir(mraa.DIR_OUT)
leftled.write(0)

rightled.dir(mraa.DIR_OUT)
rightled.write(0)

breakled.dir(mraa.DIR_OUT)
breakled.write(0)

urls = ('/turn', 'turn')
app = web.application(urls, globals())

class turn:
    def GET(self):
        data = web.input(turn='forward')
        if data.turn == 'forward':
            leftled.write(0)
            rightled.write(0)
            return "forward set!"
        if data.turn == 'left':
            blink('left')
            return "left set!"
        if data.turn == 'right':
            blink('right')
            return "right set!"
        if data.turn == 'break':
            blink('break')
            return "break set!"

def blink(turn):
    if turn == 'left':
        breakled.write(0)
        rightled.write(0)
        for i in range(1,5):
            leftled.write(1)
            time.sleep(1)
            leftled.write(0)
            time.sleep(1)
    elif turn == 'right':
        breakled.write(0)
        leftled.write(0)
        for i in range(1,5):
            rightled.write(1)
            time.sleep(1)
            rightled.write(0)
            time.sleep(1)
    elif turn == 'break':
        breakled.write(1)

if __name__ == "__main__":
    app.run()
