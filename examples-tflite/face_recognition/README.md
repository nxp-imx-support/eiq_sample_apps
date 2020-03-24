# Face recognition demo
## Dependencies:
1. i.MX 8 board running an image with the eIQ release.
2. MIPI Camera or USB camera 

## Compile on the target board:
1. Copy the whole foder of src to i.MX8QM board.
2. Change directory to src.
3. Run 'make' to build the app.
4. Run the app with command “./FaceRecognition -c 0 -h 0.85”, where ‘-c’ is camera index, and ‘-h’ is threshold for the predict score.

## Compile on the host machine:
1. Exact toolchain with eIQ on the host machine.
2. Source the cross compiler environment. For example, 'source /opt/fsl-imx-xwayland/4.14-sumo/environment-setup-aarch64-poky-linux'
3. Run 'make -f Makefile.linux' to build the app.
4. Copy the built app and "haarcascade_frontalface_alt.xml" to the board and run it with command “./FaceRecognition -c 0 -h 0.85”, where ‘-c’ is camera index, and ‘-h’ is threshold for the predict score.

## How to use:
1. The left side of the interface shows real time video captured from the camera.
2. The top-right corner of the interface displays the matched face if there is any in the face database.
   It also shows the label and similarity.
3. When a user wants to add a new face to the face database, the user can either
   - enter label name using the virtual keyboard in the interface, and press the "Add new person" button
   - or press the "Add new person" button and type label name in the console
  The face recognition function of the demo will be paused when user entering the label name.
4. Press the stop button to exit the demo.

## Link

For further information on this demo please check:
https://community.nxp.com/docs/DOC-343740
