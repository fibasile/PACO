from paco import Paco
from time import sleep

SERIAL_PORT='/dev/tty.usbserial-A702U58D'


if __name__ == '__main__':
    p = Paco(SERIAL_PORT)
    sleep(5)
    while True:
       p.readDistance()
       sleep(1)
    # p.test()
    #p.panTiltTest()
    # p.grin()
    # sleep(1)
    # p.setBrightness(5)
    # p.setLeds(255,255,255)
    # for i in range(5,255,10):
    #     p.setBrightness(i)
    #     sleep(.1)
    # p.showText("FabAcademy 2014")
    # sleep(1)
    # p.clearScreen()
    # p.showText("Yeah")
    # print p.version()
    # p.clearScreen()
    # sleep(2)

    p.exit()
    # p.pan(135)
    # board.send_sysex(0x01, ['t','h','i','s','','i','s','','a','','t','e','s','t'])
