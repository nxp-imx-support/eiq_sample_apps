# Face recognition demo
## Dependencies:
1. i.MX 8 board running an image with the eIQ release.
2. MIPI Camera or USB camera 

## How to compile:
1. Copy the whole foder of src to i.MX8QM board.
2. Change directory to src.
3. Run 'make' to build the app.
4. Run the app with command “./FaceRecognition -c 0 -h 0.85”, where ‘-c’ is camera index, and ‘-h’ is threshold for the predict score.

## How to use:
1. The left side of the interface shows real time video captured from the camera.
2. The top-right corner of the interface displays the matched face if there is any in the face database.
   It also shows the label and similarity.
3. When a user wants to add a new face to the face database, the user can either
   - enter label name using the virtual keyboard in the interface, and press the "Add new person" button
   - or press the "Add new person" button and type label name in the console
  The face recognition function of the demo will be paused when user entering the label name.
4. Press the stop button to exit the demo.