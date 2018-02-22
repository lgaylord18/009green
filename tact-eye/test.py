import numpy as np

arr = np.array([[[10, 10, 10], [20, 20, 20], [30, 30, 30], [40, 40, 40]],
                [[11, 11, 11], [21, 21, 21], [31, 31, 31], [41, 41, 41]],
                [[12, 12, 12], [22, 22, 22], [32, 32, 32], [42, 42, 42]],
                [[13, 13, 13], [23, 23, 23], [33, 33, 33], [43, 43, 43]],
                [[14, 14, 14], [24, 24, 24], [34, 34, 34], [44, 44, 44]],
                [[15, 15, 15], [25, 25, 25], [35, 35, 35], [45, 45, 45]]])

# rgbmeans = np.mean(arr, axis=0)
# means = np.mean(rgbmeans, axis=1)
# halfs = np.mean(means.reshape(-1, 2), axis=1)
# first_half = halfs[0]
# second_half = halfs[1]
# print(first_half, second_half)
# print(arr)
# means = np.mean(arr, axis=0)
# print(means)
# means2 = np.mean(means, axis=1)

# print(np.mean(means, axis=1))

# print(means2.reshape(-1, 2))
# print(np.mean(means2.reshape(-1, 2), axis=1))

# Determine the rgb values for the appropriate pixels
left_array = arr[1, 3, :]

right_array = arr[1, 1, :]
print(left_array)

left_pixel = tuple(list(left_array))
print(left_pixel)
right_pixel = tuple(list(right_array))

# For left and right, determine whether or not to vibrate
