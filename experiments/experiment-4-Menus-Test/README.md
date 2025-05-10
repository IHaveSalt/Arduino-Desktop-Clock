# 🧪 Experiment 4 - Multiple Menus
## 📝 Description
This experiment focused primarily on coding the multiple menu system. There are 3 buttons and 3 LEDs which correspond to their respective menu (time, date, and timer/stopwatch). The display is used to show information relevant to that menu, in this experiment it just shows which menu you are on.

### 🎥 Experiment videos
[Link to the experiment video](/experiments/experiment-4-Menus-Test/media/3MenusVideo.mp4)

## ⚙️ Technical Information
### 🔩 Components Used
- **Arduino Uno R3**
- **Jumper Cables**
- **Breadboard**
- **Small I2C 0.96-inch OLED Display**
- **3 Buttons**
- **3 LEDs (Red, Green, Blue)**
- **3 220Ω Resistors**


### 💻 Code
[Link to the code page](/experiments/experiment-4-Menus-Test/code/3Menus.ino)

The code has a menu tracking system using a variable. It starts off as -1 just to show when the display turns on. In the final project, I plan to remove this so that the display shows the time menu on boot. I'm using the Bounce2 library to prevent any issues that may occur with button presses. I also tried to make it scalable by using functions so that it's easier for me in the future to add more menus if needed.


### ⚡ Circuit Diagram
The wiring was straightforward but required more cable connections than any previous experiment. I kept wondering how to connect the button GND pins without using cables, but I couldn't figure it out due to how narrow the breadboard is, but I did manage to connect all the LED GND pins to a single column on the breadboard. (Not shown in the circuit diagram, see the image next to it.)

**Buttons Wiring**
- One leg -> Digital Pins 2,3,4 (Red, Green, Blue)
- Another leg (on the same side) -> GND (All buttons connected to a single column, then to GND on the Arduino using wires)

**LEDs Wiring**
- Anode (long leg) -> 220Ω resistor -> Digital Pins 8,9,10
- Cathode (short leg) -> GND (All cathodes were connected to a single column, similar to the buttons, but without cables connecting them)

**OLED Display Wiring**
- SCL -> Analogue pin A5
- SDA -> Analogue pin A4
- VCC -> 5v pin on the Arduino
- GND -> GND (I connected this to the buttons GND column as Arduino only had 2 available GND pins)

<p align="center">
    <img src="media/Buttons with display.png" width="300">
    <img src="media/LED Connection.jpg" width="273">
</p>

## 🔍 Observations & Challenges
As briefly mentioned earlier, one of the early challenges was figuring out how to efficiently wire all the GND connections together. The very slim layout of the breadboard made it tricky to avoid using extra cables for the buttons, but it was possible to neatly connect all the LED cathodes to a shared GND column.

I also spent quite some time structuring the code and trying to make it scalable, so that I could reuse it later in the final project and easily add new menus or functionality without needing to rewrite the core logic.

Another point worth expanding on is the menu tracking system. Technically, it wasn't necessary to start with -1 as the initial menu, since I can make it boot into one of the main menus by default. However, I wanted to see exactly when the screen starts up, so I used the menu -1 screen as an indication that the display and buttons were ready. In the final project, there won't be a separate starting screen, and it will boot directly into the time menu by default.

## 📈 Evaluation
This experiment was another key stepping stone towards the final project. It helped me structure a basic but functional menu system that can be triggered by button presses. Each menu is linked to an LED and shows a message on the display, not only giving clear feedback on which menu was active, but also being something that will be present in the final project.

By implementing this with functions and clean logic, I've made it easier to build on top of later, whether I'm adding timer logic, another menu, or something else. Using the Bounce2 library also made the button input much more reliable, eliminating issues with button presses not being registered or being registered multiple times. Overall, I believe this experiment was successful and serves as a solid foundation to pick up from during the final project creation process.