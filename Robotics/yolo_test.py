#!/bin/python3
import cv2
import numpy as np
import multiprocessing as mp
import threading
import time

def capture_frames(queue):
    cap = cv2.VideoCapture(0)
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        if queue.full():
            continue
        queue.put(frame)
        
    cap.release()
    cv2.destroyAllWindows()

# function to get the output layer names 
# in the architecture
def get_output_layers(net):
    layer_names = net.getLayerNames()
    output_layers = [layer_names[i - 1] for i in net.getUnconnectedOutLayers()]
    return output_layers

# function to draw bounding box on the detected object with class name
def draw_bounding_box(img, class_id, confidence, x, y, x_plus_w, y_plus_h, classes, COLORS):

    label = str(classes[class_id])

    color = COLORS[class_id]

    cv2.rectangle(img, (x,y), (x_plus_w,y_plus_h), color, 2)

    cv2.putText(img, label, (x-10,y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)
    
def detect_objects(queue):
    while True:
        if not queue.empty():
            frame = queue.get()
            Width = frame.shape[1]
            Height = frame.shape[0]
            # Width = 320
            # Height = 320
            scale = 0.00392

            # read class names from text file
            classes = None
            with open("yolov3.txt", 'r') as f:
                classes = [line.strip() for line in f.readlines()]

            # generate different colors for different classes 
            COLORS = np.random.uniform(0, 255, size=(len(classes), 3))

            net = cv2.dnn.readNet("yolov3-tiny.weights", "yolov3.cfg")

            # create input blob 
            blob = cv2.dnn.blobFromImage(frame, scale, (Width, Height), (0,0,0), True, crop=False)

            # set input blob for the network
            net.setInput(blob)

            # Run forward pass to get output of the output layers
            outs = net.forward(get_output_layers(net))

            # Initialization
            class_ids = []
            confidences = []
            boxes = []

            # For each detection from each output layer
            # get the confidence, class id, bounding box params
            # and ignore weak detections (confidence < 0.5)
            for out in outs:
                for detection in out:
                    scores = detection[5:]
                    class_id = np.argmax(scores)
                    confidence = scores[class_id]
                    if confidence > 0.5:
                        center_x = int(detection[0] * Width)
                        center_y = int(detection[1] * Height)
                        w = int(detection[2] * Width)
                        h = int(detection[3] * Height)
                        x = center_x - w / 2
                        y = center_y - h / 2
                        class_ids.append(class_id)
                        confidences.append(float(confidence))
                        boxes.append([x, y, w, h])

            # Perform non-max suppression to eliminate redundant overlapping boxes with
            # lower confidences
            indices = cv2.dnn.NMSBoxes(boxes, confidences, 0.5, 0.4)
            
            # Draw bounding box for each detected object
            for i in indices:
                # i = i[0]
                box = boxes[i]
                x = box[0]
                y = box[1]
                w = box[2]
                h = box[3]
                draw_bounding_box(frame, class_ids[i], confidences[i], round(x), round(y), round(x + w), round(y + h), classes, COLORS)
            
            # Display the resulting frame
            cv2.imshow('Frame', frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

if __name__ == '__main__':
    
    # Create a queue to store frames
    queue = mp.Queue(maxsize=10)
    
    # Start the thread for reading in frames
    camera_thread = threading.Thread(target=capture_frames, args=(queue,))
    camera_thread.daemon = True
    camera_thread.start()
    
    # Start thread for object detection
    object_detection_process = mp.Process(target=detect_objects, args=(queue,))
    object_detection_process.start()
    
    object_detection_process.join()
    
    
