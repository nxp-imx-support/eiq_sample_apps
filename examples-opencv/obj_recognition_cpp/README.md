# Object recognition demo
## Dependencies:
1. i.MX 8 board running an image with the eIQ release.
2. MIPI Camera or USB camera

## Compile on the target board:
1. Copy the whole folder of src to i.MX8QM board.
2. Change directory to src.
3. Run 'make' to build the app.
4. Run the app with command “./ObjectRecognitionCPP".

## Compile on the host machine:
1. Extract toolchain with eIQ on the host machine.
2. Source the cross compiler environment. For example, 'source /opt/fsl-imx-xwayland/4.14-sumo/environment-setup-aarch64-poky-linux'
3. Run 'make' to build the app.
4. Copy the built app to the board and run it with command “./ObjectRecognitionCPP”.

## Download the model and config files:

Download and copy the files from the following urls to the demo folder.

https://github.com/chuanqi305/MobileNet-SSD/blob/master/mobilenet_iter_73000.caffemodel
https://github.com/chuanqi305/MobileNet-SSD/blob/master/deploy.prototxt

## How to use:

1. Execute “./ObjectRecognitionCPP”. A window with a video from camera will be displayed.
2. In case GTK or QT5 doesn't find the display, export display variable with the command: "export DISPLAY=:0.0"
