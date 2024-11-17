# MathsJV

Git repository for the physics engine of Oscar Cizeron, Maëlle Juilliot, Ghali Mechkour and Théo Le Goc, made for 8INF935.

# How to build

- Creer un nouveau projet openframework avec ofxGui activé
- Copier le contenu du dossier `src` du git dans le dossier `src` du projet nouvellement créé
- Dans le projet C++ ajouter tout les fichiers copiés à l'exception de ceux des dossiers `src\externalressources` et `src\tests`

Vous pouvez ensuite lancer le projet

# Tests

Créer un nouveau projet C++ Console, et ajouter les fichiers des dossiers `src/maths` et `src/tests`. Il faut aussi définir le marqueur `IGNORE_GLM` dans les options de compilation (preprocessor flags). Il suffit ensuite de lancer le projet, les tests vont s'écrire dans la console.

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
