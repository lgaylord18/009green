# Import all modules
import io
import time
import picamera
import picamera.array
import numpy as np
from gpiozero import LED

light = LED(27)
vibration1 = LED(17)
capturing = True
light.on()


class RGBTest(picamera.array.PiRGBAnalysis):

    def analyse(self, array):
        color = 0
        for x in range(0, 8):
            for y in range(0, 8):
                r = array[60 + x][60 + y][0]
                g = array[60 + x][60 + y][1]
                b = array[60 + x][60 + y][2]
                rgb = np.mean([r, g, b])
                color += rgb
        average = color / 64
        # if average < 70:
        #     vibration1.on()
        # else:
        #     vibration1.off()
        # if array[320][240][0] < 50 and array[320][240][0] < 50 and array[320][240][0] < 50:
        #     vibration1.on()
        # else:
        #     vibration1.off()

# capturing = True
# with picamera.PiCamera() as camera:
#     camera.color_effects = (128, 128)
#     with picamera.array.PiRGBArray(camera) as output:
#         while capturing:
#             camera.resolution = (640, 480)
#             camera.capture(output, 'rgb')
#             # print('Captured %dx%d image' % (
#             #     output.array.shape[1], output.array.shape[0]))
#             # print(output.array[320][240])
#             if output.array[320][240][0] < 50 and output.array[320][240][0] < 50 and output.array[320][240][0] < 50:
#                 print("BLACK")
#                 # capturing = False
#             output.truncate(0)


with picamera.PiCamera() as camera:
    camera.color_effects = (128, 128)
    camera.resolution = (128, 128)
    with RGBTest(camera) as stream:
        camera.start_recording(stream, 'rgb')
        camera.wait_recording()
        while capturing:
            None
        camera.stop_recording()

        # stream = io.BytesIO()

        # for picture in camera.capture_continuous(stream, format='rgb'):
        #     # Truncate the stream to the current position (in case
        #     # prior iterations output a longer image)
        #     stream.truncate()
        #     stream.seek(0)
        #     if output.array[320][240][0] < 50 and output.array[320][240][0] < 50 and output.array[320][240][0] < 50:
        #         print("BLACK")
        #     break
