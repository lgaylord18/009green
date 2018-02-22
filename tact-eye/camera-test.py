# Import all modules
from picamera import PiCamera
from gpiozero import LED
import time

light = LED(27)
vibration1 = LED(17)
light.on()
vibration1.off()

camera = PiCamera()
camera.resolution = (128, 128)

# Camera warm-up time
time.sleep(2)
camera.capture('1.jpg')

camera.resolution = (640, 480)
camera.capture('2.jpg')

camera.resolution = (320, 240)
camera.capture('3.jpg')
