from commands import PacoCommands, PacoBitmaps, PacoEvents
import serial
from time import sleep

START_SYSEX = 0xF0  
END_SYSEX = 0xF7

class Paco:
    
    def __init__(self, serial_port):
        self.serial_port = serial_port
        self.serial = serial.Serial(serial_port,115200)
        self.serial.write('0xFF')
        self.distance = 0
        self.ready=False

    def test(self):
        self.send_command(PacoCommands.TEST,[])
        sleep(10)


    def send_command(self, cmd, args):
        print 'Command sent'
        self.serial.write(chr(START_SYSEX))
        self.serial.write(chr(cmd))
        for a in args:
            self.send_as_two_bytes(a)
        while self.bytes_available():
                   self.iterate()
        self.serial.write(chr(END_SYSEX))


    def from_two_bytes(self,bytes):
        """
        Return an integer from two 7 bit bytes.

        >>> for i in range(32766, 32768):
        ...     val = to_two_bytes(i)
        ...     ret = from_two_bytes(val)
        ...     assert ret == i
        ...
        >>> from_two_bytes(('\\xff', '\\xff'))
        32767
        >>> from_two_bytes(('\\x7f', '\\xff'))
        32767
        """
        lsb, msb = bytes
        try:
            # Usually bytes have been converted to integers with ord already
            return msb << 7 | lsb
        except TypeError:
            # But add this for easy testing
            # One of them can be a string, or both
            try:
                lsb = ord(lsb)
            except TypeError:
                pass
            try:
                msb = ord(msb)
            except TypeError:
                pass
            return msb << 7 | lsb
            


    def send_as_two_bytes(self, val):
            if type(val) == type(''):
                val = ord(val)
            value = chr(val % 128) + chr(val >> 7)
            self.serial.write(value)

    def iterate(self):
            """
            Reads and handles data from the microcontroller over the serial port.
            This method should be called in a main loop or in an :class:`Iterator`
            instance to keep this boards pin values up to date.
            """
            byte = self.serial.read()
            if not byte:
                return
            data = ord(byte)
            received_data = []
            handler = None
            if data == START_SYSEX:
                cmd = ord(self.serial.read())
                data = ord(self.serial.read())
                while data != END_SYSEX:
                    received_data.append(data)
                    data = ord(self.serial.read())
                self.handle_sysex(cmd,received_data)
            

    def handle_sysex(self,cmd,data):
        if cmd==121:
            self.ready=True
        if cmd==PacoEvents.EVT_DISTANCE:
            if len(data) >= 2:
                self.distance = self.from_two_bytes(data[0:2]) 
                print 'Distance %d' % self.distance
        print 'Received %s' % cmd

    def bytes_available(self):
        return self.serial.inWaiting()

    def pan(self, degrees):
        self.send_command(PacoCommands.PAN, [degrees] )
        sleep(.3)

    def tilt(self, degrees):
        self.send_command(PacoCommands.TILT, [degrees] )
        sleep(.3)
        
    def panTiltTest(self):
        self.pan(40)
        self.tilt(30)
        self.pan(130)
        self.tilt(70)
        self.pan(40)
        self.tilt(50)
        self.pan(90)
        
        
    def showBitmap(self, bitmap):
        if PacoBitmaps.has_key(bitmap):
            self.send_command(PacoCommands.SHOW_BMP, [PacoBitmaps[bitmap]])
    
    def showText(self, text):
        if len(text)>0:
           self.serial.write(chr(START_SYSEX))
           self.serial.write(chr(PacoCommands.SHOW_TXT))
           for ch in text:
               self.serial.write(ch)
           self.serial.write(chr(END_SYSEX))
           
    def clearScreen(self):
        l=[]
        for i in range(0,50):
            l.append(' ')
        self.send_command(PacoCommands.SHOW_TXT,l)
    
    
    def setLed(self, ledNo, r,g,b):
        cmdArgs = [ledNo,r,g,b]
        self.send_command(PacoCommands.SET_LED, cmdArgs)
        
    def setLeds(self, r,g,b):
        cmdArgs = [9,r,g,b]
        self.send_command(PacoCommands.SET_LED, cmdArgs)
        
        
    def setBrightness(self, val):
        self.send_command(PacoCommands.SET_BRIGHT, [val])
    
    
    def readDistance(self):
        self.send_command(PacoCommands.READ_DISTANCE, [])
        # for i in range(0,10):
            # self.iterate()
        return self.distance
    
    def logo(self):
        self.showBitmap("logo")
    
    def smile(self):
        self.showBitmap("smile")
    
    def beachlab(self):
        self.showBitmap("beachlab")
        
    def sad(self):
        self.showBitmap("sad")
    
    def grin(self):
        self.showBitmap("grin")
            
    def version(self):
        return 1.0
        
    def exit(self):
        self.serial.close()