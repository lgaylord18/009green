# Import all modules
import io
import numpy as np
import time
import picamera
import picamera.array
import numpy as np
from gpiozero import LED

###########################
# EXPERIMENTAL VARIABLES
# Vision analysis

# Pixel location for input to left and right vibration
# Given as an x, y coordinate
# Where x and y are both values between zero and one
# s. t. (0,0) is the left upper corner and (1,1) is b.r.
left_loc = (.5, .3)
right_loc = (.5, .7)

# Average color of the uv marker, given as a rgb tuple
# On 255 scale
uv_color = (52, 61, 33)

# Color tolerance, given as rgb tuple.
# The device will vibrate if the pixel is within the range of
# uv_color +- uv_var
uv_var = (25, 20, 10)

# Resolution (Multiple of 32)
resolution = 128
###########################

# Compute some helper variables
left_x = int(left_loc[0] * resolution)
left_y = int(left_loc[1] * resolution)
right_x = int(right_loc[0] * resolution)
right_y = int(right_loc[1] * resolution)

# Variables for component initialization
light = LED(27)
vibration1 = LED(17)
vibration2 = LED(22)
capturing = True

# Start components
light.on()

#
# Helper functions
#

# Determines if a pixel is in range
# (All input are tuples)
# pixel - rgb of pixel in question
# target - rgb of target color
# var - rgb of tolerated color variance
# OUTPUT - boolean (true if pixel is in range, otherwise false)


def pixel_in_range(pixel, target, var):
    # For each value, assess if it is in range
    for i, component in enumerate(pixel):
        difference = np.abs(target[i] - component)
        if difference > var[i]:
            return False
    return True

#
# Main image analysis code
#


class RGBTest(picamera.array.PiRGBAnalysis):
    # Analyse is a defined function of picamera
    # This overwrites the default function to provide a custom
    # analysis of the image.
    # The main image analysis code is here.

    def analyse(self, array):
        # Determine the rgb values for the appropriate pixels
        # left_array = array[left_x, left_y, :]

        # right_array = array[right_x, right_y, :]

        # left_pixel = tuple(list(array[64][64]))
        # left_pixel = tuple(list(left_array))
        # right_pixel = tuple(list(right_array))
        # print(array[64][64])
        # print(array[10][10])
        #
        # for x in range(0, 8):
        #     for y in range(0, 8):
        #         r = array[60 + x][60 + y][0]
        #         g = array[60 + x][60 + y][1]
        #         b = array[60 + x][60 + y][2]
        #         rgb = np.mean([r, g, b])
        #         color += rgb
        # average = color / 64
        # For left and right, determine whether or not to vibrate
        left_on = False
        # left_on = pixel_in_range(tuple(list(left_pixel)), uv_color, uv_var)
        # right_on = pixel_in_range(right_pixel, uv_color, uv_var)

        # Turn on / off vibration pads as needed
        if left_on:
            vibration1.on()
        else:
            vibration1.off()
        if right_on:
            vibration2.on()
        else:
            vibration2.off()

#
# Main Loop -- Access and process image
#
with picamera.PiCamera() as camera:
    # Initialize camera affects
    camera.resolution = (resolution, resolution)
    # Start the camera and begin processing
    with RGBTest(camera) as stream:
        camera.start_recording(stream, 'rgb')
        camera.wait_recording()
        while capturing:
            None
        camera.stop_recording()
