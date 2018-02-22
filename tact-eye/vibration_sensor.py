# Import all modules
import io
import time
import picamera
import PIL
import RPi.GPIO as GPIO

# initialize vibrator as output
GPIO.setup([whatever pin number], GPIO.OUT)
# initialize LED as output
GPIO.setup([whatever pin number], GPIO.OUT)

# initialize camera
camera = picamera()

# set to lower resolution
camera.resolution = (1024, 768)

# Use grayscale
camera.color_effects(128, 128)

# initializa IO
camera_stream = BytesIO()

with picamera.PiCamera() as camera:
    camera.resolution = (640, 480)
    camera.color_effects(128, 128)
    camera_stream = BytesIO()
    camera.start_preview()
    time.sleep(2)

    for picture in camera.capture_continuous(camera_stream, format='jpeg'):
        camera_stream.truncate()
        camera_stream.seek(0)
        image = Image.open(camera_stream)
        width, height = image.size()
        x_center = width/2
        y_center = height/2
        pixel = image.getpixel((x_center, y_center))

        if process(stream):
            break

    # convert the stream to a PIL image
    #image = Image.open(camera_stream)

    # find the cener of the PIL image
    #width, height = image.size()
    #x_center = width/2
    #y_center = height/2

    #pixel = image.getpixel((x_center, y_center))
    # if it is black
    # if pixel is blac:
    #	vibrate


# Turn off everything
