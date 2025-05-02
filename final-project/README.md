#   🚀 Final Project - Desktop Clock Assistant

##  🧠 Initial Concept
### 💡 Project Idea and Inspiration
After watching Rick and Morty as a teenager, I became fascinated by the "Pass me the Butter" robot. That idea, combined with the concept of SCP-079 (a sentient computer from the fictional SCP Foundation), sparked a long-term interest in creating a somewhat sentient and a small task focused AI robot. With today's accessibility and the power of AI, creating something like this seems very much possible.

However, I quickly realised that creating a fully functioning AI robot is far too ambitious given the limited timeframe and my current experience level with Arduino. Even a partially functional version would likely become an unmanageable time sink.

Instead, I decided to pursue a scaled-down but conceptually similar project. A multifunctional desktop clock. At its core, this will be a digital clock with a small display and menu navigation via buttons. Planned menus include time, date, stopwatch, and timer functions. When looking at projects that people have created, I really liked the ultrasonic sensor in projects such as the [Obstacle Avoiding Robot](https://www.youtube.com/watch?v=jQwYBc7YBXs) and the [Parking Sensor](https://www.youtube.com/watch?v=sEWw087KOj0), so I wanted to include this component to create a low-power or an ambient mode that preserves battery life. When the user waves their hand in front of the clock, it wakes up and displays the information.

This refocus allows me to build a creative and technically layered project while staying within the scope. This also lays the foundation from which I can build on in the future when I will be revisting the initial idea.

-- add an image of the prototype idea --


### 🎯 Target audience
The primary target audience for this project is me. As I mentioned earlier, this will lay a foundation for my initial idea in the future as well as being a distraction free alternative to checking my phone all the time for time, which is quite distracting when focusing on something.

This project is also suitable for beginner Arduino enthusiasts who are looking for a first project. It serves as a practical and manageable base to explore buttons, displays, sensors and user interaction, without overwhelming complexity. Enthusiasts could also adapt or build on the project to better suit their specific needs.

While not intended as a commercial product, this project could be seen as an early prototype for a minimalist desk smart clock. With additional functionality and polishing it has the potential to evolve and compete on the market.

### 🛠️ Planned Experiments
This project will be developed in stages, beginning with individual experiments testing and understanding each major component, such as the ultrasonic sensor, buttons, and the RTC module for time. These experiments will help shape the final build, to ensure that each component works relieably. These separate experiments will then be intergrated together and polished into a complete final project.

### 🚧 Expected Challenges
One expected challenge I found out about when researching is handling button debounce, which can cause the Arduino to register multiple presses from a single input. I understand this issue in theory but will have to figure out how to manage this in code.

Power management is another big consideration, as I have already burnt some LEDs when experimenting. I estimated the power usage and it's well below the Arduino's current limit. I'll still need to ensure that components like LEDs and the screen are properly regulated with resistors and capacitors.

Implementing multiple display menus may also be tricky, as it involves managing input, display updates, and state transitions. I expect this to be one of the most technically demanding aspects.

Lastly, I will need to keep an eye on the memory usage as the Arduino Uno has limited space and if I use too many libraries there could be issues.


##  ⚙️ Technical Information
### 🔩 Components Used
- List the main components (Arduino model, sensors, etc.) and briefly explain what they do.
- Add images of components

### 💻 Code
- Explain what the code does in simple terms. Mention any key parts of the code.
- Link to the code folder and add screenshots of the code if helpful.

### ⚡ Circuit Diagram
- Describe the circuit setup and any key wiring decisions (e.g., resistor values, connections).
- Add an image of the circuit diagram here.

## 🔍 Observations & Challenges
- Describe any issues faced during the project and how I solved them. If no issues, write about observations.
- Be honest about what went wrong and how I fixed it.

## 📈 Final Evaluation
- Summarize what was learned from the project. Mention how it could be improved and what I would do differently next time.
- Reflect on how the final outcome compares to the initial concept. Was it successful? Why or why not?
- Keep this section thoughtful and reflective.