# MathsJV

Git repository for the physics engine of Oscar Cizeron, Maëlle Juilliot, Ghali Mechkour and Théo Le Goc, made for 8INF935.

# How to build - tag `phase1`

- Create a new open frameworks project with ofxGui enabled.
- Copy the content of the git src folder and paste it in the src of the newly created project.
- Exclude all files under `src\externalressources` and under `src\tests`

You can then run the project.

# How to build - tag `phase2`

- Create a new open frameworks project with ofxGui enabled.
- Copy the content of the git src folder and paste it in the src of the newly created project.
- Include everything
- Then exclude all files under `src\externalressources` and under `src\tests`

You can then run the project.

# How to build - tag `phase3`

- Create a new open frameworks project with ofxGui enabled.
- Copy the content of the git src folder and paste it in the src of the newly created project.
- Include everything
- Then exclude all files under `src\externalressources` and under `src\tests`

You can then run the project.

# Tests

Create a new Visual Studio c++ console project, and add all files from `src/maths` and `src/tests`. You will also need to set the define flag `IGNORE_GLM`. You can then run the project, and it will print results in the console.

# Using the project - tag `phase1`

Click on the screen to spawn a particle. The distance to the bottom right corner and the orientation matters, as it will change the initial velocity of the particle.

Use the on screen controls on the bottom left to change settings such as the particle type, or show debug info.

# Using the project - tag `phase2`

You can right click on a particle and move the mouse to move it. If you apply a force too big on one of the particle of the blob it will separate from the rest.

Camera movement : right click to rotate the camera, middle click to translate and right click / scroll to zoom in and out.

Blob : click once on one of the arrow key to add some horizontal movement.

# Using the project - tag `phase3`

Use the on screen controls to cycle through different rigidbodies, and launch them using the button. 

Camera movement : right click to rotate the camera, middle click to translate and right click / scroll to zoom in and out.

Links :
- White : basic two particle spring
- Red : rod
- Azure : bungee
- Green/sometimes blue : cable
- White ball and no line : basic single particle spring
