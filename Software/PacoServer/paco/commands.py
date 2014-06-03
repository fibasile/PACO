class PacoCommands:
    
    
    PAN=0x01
    TILT=0x02
    SHOW_BMP=0x03
    SHOW_TXT=0x04
    CLEAR_SCREEN=0x05
    READ_DISTANCE=0x06
    SET_LED=0x07
    SET_BRIGHT=0x08
    # READ_CAP=0x09
    TEST=0x00
    
    
class PacoEvents:
    EVT_DISTANCE=0x01
    EVT_CAPSENSE=0x02
    
    
PacoBitmaps = { 
    "logo" :  0,
    "beachlab" : 1,
    "smile" : 2,
    "grin" : 3,
    "sad" : 4
}
    