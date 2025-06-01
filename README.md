# McsGui
McsGui is a lightweight, platform-independent GUI library designed specifically for developing user interfaces on small embedded systems. Whether you’re building a touchscreen appliance, an industrial controller, or any device with a constrained microcontroller, this library offers the flexibility and power you need.

With its modular architecture, you can easily create your own reusable GUI components, enabling rapid development and consistent design across projects. The library supports both touch and key navigation, and makes it simple to implement custom themes and translations to match your application’s needs.

A suite of tools is included to streamline development: view and control your interfaces on your PC, generate custom fonts, and convert text or SVG files for use in your embedded project.

**Key Features:**
- Platform-independent: runs on a wide range of microcontrollers
- Designed for resource-constrained embedded systems
- Modular, reusable GUI components—write and share your own!
- Touch and key navigation support
- Easy theming and translation capabilities
- PC-based GUI preview, font creation, and asset conversion tools

**Who is it for?**  
Anyone who wants to add a modern graphical user interface to a small embedded microcontroller—hobbyists, professionals, and students alike.

Get started building rich, interactive interfaces for your embedded applications—without the bloat!

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
 To use the Gui Debugger just run the executable. <br/>

![Demo_1_Main](https://github.com/user-attachments/assets/c34d3fcd-835d-4e40-a848-138d10469d61)
<br/>Demo App 1 - Main menu<br/>

![Demo_4_Main](https://github.com/user-attachments/assets/fd2ff323-f68c-4bc4-8cbb-95a57e34c00c)
<br/>Demo App 4 - Main menu<br/>

![Demo_1_Demo_device](https://github.com/user-attachments/assets/45b3db39-8940-4690-ad2f-1f2af8b7a8fd)


