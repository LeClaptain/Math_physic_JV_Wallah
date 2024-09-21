# MathsJV

Git repository for the physics engine of Oscar Cizeron, Maëlle Juilliot, Ghali Mechkour and Théo Le Goc, made for 8INF935.

# How to build - tag `phase1`

## Setup
- Create a new open frameworks project with ofxGui enabled.
- Copy the content of the git src folder and paste it in the src of the newly created project.
- Exclude all files under `src\externalressources`

You can then run the project.

## Tests

Create a new Visual Studio c++ console project, and add all files from `src/maths` and `src/tests`. You can then run the project, and it will print results in the console.

# Using the project

Click on the screen to spawn a particle. The distance to the bottom right corner and the orientation matters, as it will change the initial velocity of the particle.

Use the on screen controls on the bottom left to change settings such as the particle type, or show debug info.