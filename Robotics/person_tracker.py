#!/bin/python3
import cv2

import cv2

# Initialize video source, 0 for the primary camera
cap = cv2.VideoCapture(0)

# Create the background subtractor object
backSub = cv2.createBackgroundSubtractorMOG2()

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Apply the background subtractor
    fgMask = backSub.apply(frame)

    # Apply morphological operations to remove noise and fill in holes
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3))
    fgMask = cv2.morphologyEx(fgMask, cv2.MORPH_OPEN, kernel, iterations=2)
    fgMask = cv2.dilate(fgMask, kernel, iterations=2)

    # Find contours in the foreground mask
    contours, _ = cv2.findContours(fgMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Draw contours on the original frame
    for contour in contours:
        if cv2.contourArea(contour) > 800:  # Filter out small contours
            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

    # Display the resulting frame
    cv2.imshow('Frame', frame)
    cv2.imshow('Foreground Mask', fgMask)

    # Press 'q' on the keyboard to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the capture and close any open windows
cap.release()
cv2.destroyAllWindows()
