# Import all modules
import io
import time
import picamera
import picamera.array
import numpy as np
from gpiozero import LED

light = LED(26)
vibration1 = LED(17)
vibration2 = LED(22)
capturing = True
light.on()


class RGBTest(picamera.array.PiRGBAnalysis):

    def analyse(self, array):
        # split 3d array into means
        rgbmeans = np.mean(array, axis=0)
        means = np.mean(rgbmeans, axis=1)
        halfs = np.mean(means.reshape(-1, 320), axis=1)
        left_half = halfs[0]
        right_half = halfs[1]

        if left_half < 50:
            vibration1.on()
        else:
            vibration1.off()
        if right_half < 50:
            vibration2.on()
        else:
            vibration2.off()

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
    camera.resolution = (640, 480)
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
