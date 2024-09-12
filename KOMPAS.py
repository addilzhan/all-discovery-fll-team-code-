import cv2
import numpy as np

def detect_direction(frame, prev_frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray_prev = cv2.cvtColor(prev_frame, cv2.COLOR_BGR2GRAY)
    diff = cv2.absdiff(gray_prev, gray)
    _, thresh = cv2.threshold(diff, 25, 255, cv2.THRESH_BINARY)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    if not contours:
        return "No movement detected"

    largest_contour = max(contours, key=cv2.contourArea)
    M = cv2.moments(largest_contour)
    if M["m00"] == 0:
        return "No movement detected"
    
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])
    h, w, _ = frame.shape
    centerX, centerY = w // 2, h // 2
    
    dx = cX - centerX
    dy = cY - centerY

    if abs(dx) > abs(dy):
        return "East" if dx > 0 else "West"
    else:
        return "South" if dy > 0 else "North"

def main():
    cap = cv2.VideoCapture(0)
    
    if not cap.isOpened():
        print("Error: Unable to access the webcam.")
        return

    ret, prev_frame = cap.read()
    if not ret:
        print("Error: Unable to capture an image.")
        return

    while True:
        ret, frame = cap.read()
        if not ret:
            break
        
        direction = detect_direction(frame, prev_frame)
        cv2.putText(frame, f"Direction: {direction}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        cv2.imshow('Compass', frame)
        
        prev_frame = frame.copy()
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
