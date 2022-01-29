import web
import serial
import thread
import time
import val

sensor_data = None


def setup():
    global ser
    ser = serial.Serial("/dev/ttyS0", 57600)

def loop():
    global sensor_data
    sensor_data = ser.read(9)
    print sensor_data
    time.sleep(1)

urls = ('/sensor', 'sensor')

app = web.application(urls,globals())

class sensor:

    def GET(self):
        global sensor_data
        global ser
        ser = serial.Serial("/dev/ttyS0", 57600)
        sensor_data = ser.read(9)
        data = web.input(t='26',h='70',u='6',l='1',r='1')
        val.t = int(data.t)
        val.h = int(data.h)
        val.u = int(data.u)
        val.l = int(data.l)
        val.r = int(data.r)
        return "Temperature : " + str(sensor_data[0:2]) + '.' + str(sensor_data[2:4]) + "'C   Humidity : " + str(sensor_data[4:6]) + '.' + str(sensor_data[6:8]) + "%   UV index : " + str(sensor_data[8])

if __name__=="__main__":
    
    thread.start_new_thread(app.run())
