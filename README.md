import time
import cv2
import numpy as np

def detect_red_light_in_frame(frame, min_area=500):
    """
    Detects and counts red LED lights in a given frame.
    
    Args:
        frame (numpy.ndarray): A single frame of the video.
        min_area (int): Minimum area of a bright region to classify as "red light".
    
    Returns:
        int: Number of detected red regions (LEDs).
        numpy.ndarray: Processed frame with detections highlighted.
    """
    # Convert the frame to HSV color space
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Define the red color range in HSV
    lower_red1 = np.array([0, 120, 100])   # Lower range for red
    upper_red1 = np.array([10, 255, 255])  # Upper range for red
    lower_red2 = np.array([170, 120, 100])  # Second range for red
    upper_red2 = np.array([180, 255, 255])  # Second upper range for red

    # Create masks for red color
    mask1 = cv2.inRange(hsv, lower_red1, upper_red1)
    mask2 = cv2.inRange(hsv, lower_red2, upper_red2)
    mask = cv2.bitwise_or(mask1, mask2)

    # Find contours of red regions
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Count the number of red regions that meet the minimum area criteria
    red_count = 0
    for contour in contours:
        if cv2.contourArea(contour) > min_area:
            red_count += 1
            # Draw a bounding box around the detected red light
            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

    return red_count, frame

def task_test(robot, image, td):
    """
    Verifies the count of red LED lights detected in a frame and updates the test data.
    
    Args:
        robot: Instance of the Robot object (not used in this implementation).
        image: Current camera frame (NumPy array).
        td: Instance of DataTest for tracking the test state.
    
    Returns:
        Updated td, user-facing text, and Result object.
    """
    text = "Processing frame for red LED detection"

    # Set end time for the task if not already set
    if td.end_time is None:
        td.end_time = time.time() + 10  # 10-second verification duration

    # Detect red LED light in the frame and get the count
    red_count, processed_frame = detect_red_light_in_frame(image)

    # Add a debugging circle to the image (optional)
    cv2.circle(processed_frame, (700, 400), 20, (255, 0, 0), -1)

    # Update the result based on the count of red lights detected
    status = f"{red_count} Red Light(s) ON" if red_count > 0 else "No Red Lights Detected"
    text = f"Detection Status: {status}"

    # Return the result
    return td, text, Result(red_count > 0, f"{red_count} red light(s) detected in the frame")
