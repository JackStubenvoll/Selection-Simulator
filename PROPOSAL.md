I want to simulate natural selection over multiple generations. I'm going to have several steps that I'm going to try to implement, but won't be a big deal if I can't implement them all.

The first step is to have a board not unlike the gas container from ideal gas, where small blobs of "food" will spawn each "day". Each member of the "herbivore" species will have a trait determined by a number, like speed. The herbivores will have an energy level like the mining robots from mineopoly, that food increases. If they are below a certain threshold, the herbivore dies. If they are above a certain threshold, they will replicate into two new herbivores, with there being a random value their stat will change. If they are between these thresholds at the end of the day, they survive but do not reproduce. 

This step will also involve creating a histogram (like with ideal gas) to track the number of individuals and the various trait values.

The second step is to increase the traits in the herbivores. At the moment I'm thinking speed, where the herbivores can move faster at the cost of more energy per tile; sense, where the herbivores can detect food from further away; and the third step is an (currently) arbitrary color value that determines the color of the herbivore.

The third step is to introduce a predator species that targets the herbivores instead of the food particles. They will also have the same traits as the herbivores. 


I have a few reasons why I want to do this for my project. The first is that I've seen it done before on YouTube (not the code, only the result), although they didn't have predators and instead had a different third trait. The second is that I'm minoring in bioengineering and enjoy biology in general, so this will be both fun and applicable. The third is that I can reference old code to get parts of this working, which makes it easier for me.

Each step corresponds to roughly a week of development. For stretch goals,  I will create sections of the board with different colors, and if a creature blends in it will be harder to spot.
