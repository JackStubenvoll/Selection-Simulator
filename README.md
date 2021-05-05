This project simulates natural selection among two different species, each with the same traits. These traits are:

* Speed, which determines how many tiles an animal can move in one frame.
* Intelligence, which determines the likelihood of moving when the nearest piece of food is out of reach.
* Color, which is purely visual.

Each day lasts 300 frames, during which the animals can move around, seeking food. During the day, the herbivores can reproduce once they have enough energy, while predators must wait until the end of the day. Herbivores will seek out food and predators will seek out herbivores. At the start of a new day, a set number of plants will be randomly generated across the board to provide food for the herbivores.

There are also histograms displayed in other quadrants of the window, tracking the populations and the two traits. You can swap between herbivore stats and predator stats.

When an animal reproduces, its child will have a random offset from the parent in each stat. The histograms keep track of the average of these stats across the whole population. This is because populations evolve, not individuals. This simulation shows how the populations change over time.

There are also several controls for the simulation:

* The spacebar will pause and unpause the simulation.
* The TAB key will, when the simulation is paused, move the simulation forward one frame.
* The 0 key on either the numpad or the keyboard will swap the histograms between herbivore and predator.
