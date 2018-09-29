# Character-Drawing

The final result is shown in the "TIM截图20180928232917.png"

This software ONLY SUPPORT PNG FORMAT!!!

Tips:   1. Don't apply images of little difference in color (eg. a picture of the whole scene too dark)
        2. Don't apply images with high resolution (max of height and width within 200px is recommended.)
        3. The higher threshold value is, the more details lose；
          the less threshold value is, the more disordered characters generated are
        4. (IMPORTANT) Please use monospaced fonts
        5. If the final result txt is too big to display, there are two ways to improve:
          1>. Adjust font size smaller.
          1>. Retry a image with smaller resolution.

Noiced that the aspect ratio of the original image to the result is not 1:1.
        The result will be higher in height. 
        The solution is that reducing height to 0.5-0.75 before using this software (with Photoshop), or expand the width to 0.5-0.75

The final result will automatically save at your desktop.

Thanks very much for the png read library provided by lvandeve.
The project address is https://github.com/lvandeve/lodepng
(It's a very simple library without any other lib as "libpng" or "zlib". I highly recommend it to those who wanna read/write PNG files.)

How to use:
        You could copy codes(three file including header and its implementation and main file) to your IDE, or download the exe I've compiled named "characterDrawing.exe", then follow the instruction inside the program.
