# McsGui
McsGui - Generic GUI module for small embedded systems.


## McsGui Demo Projects.
### Hardware used in the examples:
### Demo App 1, 2 and 3:
- NUCLEO-L496ZG-P: STM32 Nucleo-144 development board
- Waveshare 4 inch TFT Display Shield 480\*320 with Touchscreen
- Digilent: Pmod MicroSD Card Slot
- 5 buttons for keynavigation

### Demo App 4:
- NUCLEO-L496ZG-P: STM32 Nucleo-144 development board
- Waveshare 2.8 inch TFT Display Shield 320\*240 with Touchscreen
- Digilent: Pmod MicroSD Card Slot
- 5 buttons for keynavigation

### How to run the demo applications
Create a folder on the Sd-card named "GuiImage" and copy the pixel-datafile into this folder.
The pixel-datafile can be found in the folders: 
- https://github.com/mcvanstee/McsGui/tree/main/McsGuiDemoProjects/Gui_Image_Projects/McsGui_Demo_1_2/build
- https://github.com/mcvanstee/McsGui/tree/main/McsGuiDemoProjects/Gui_Image_Projects/McsGui_Demo_3/build
- https://github.com/mcvanstee/McsGui/tree/main/McsGuiDemoProjects/Gui_Image_Projects/McsGui_Demo_4/build
  
Run the project from STM32CubeIDE.

 _Run the demo applications on only the Nucleo development board_
 Using the Windows application IRL Gui Debugger it is possible to run a demo application on a development board only.
 The IRL Gui Debugger can be found in the repo: https://github.com/mcvanstee/McsGuiTools_GuiDebugger/releases/tag/V100 </br>
 To use the Gui Debugger just run the executable. 



![Demo_1_Main](https://github.com/user-attachments/assets/c34d3fcd-835d-4e40-a848-138d10469d61)
<br/>Demo App 1 - Main menu

![Demo_4_Main](https://github.com/user-attachments/assets/fd2ff323-f68c-4bc4-8cbb-95a57e34c00c)
<br/>Demo App 4 - Main menu
