# ocean.s-24
Source code of the Ocean.s-24 projects

## Matériel nécessaire

- 2 arduino (1 pour la gestion des capteurs et 1 pour les bandes led et bouton)
- un multiplexeur (pour connecter plusieurs capteur de profondeur)
- un bouton (pour activer l’animation et passer les différentes étapes)
- 5 bandes led (pour simuler le niveau de la mers avec la couleur)
- 1 écran (pour l’affichage de l’animation)
- Des câbles
- board … 

## Logiciels nécessaires et procédure d'installation

- 

## Procédures d'installation et de lancement du projet

### Arduino
Pour installer le logiciel Arduino et la bibliothèque Adafruit NeoPixel, suivez ces étapes :
1. Téléchargement et installation d'Arduino :
    - Rendez-vous sur le site officiel d'Arduino : <https://www.arduino.cc/>.
    - Téléchargez la dernière version du logiciel Arduino compatible avec votre système d'exploitation.
    - Suivez les instructions d'installation fournies sur le site.

2. Installation de la bibliothèque Adafruit NeoPixel :
    - Ouvrez l'IDE Arduino.
    - Allez dans le menu "Croquis" (Sketch) -> "Inclure une bibliothèque" (Include Library) -> "Gérer les bibliothèques" (Manage Libraries).
    - Dans la fenêtre qui s'ouvre, recherchez "Adafruit NeoPixel" dans la barre de recherche.
    - Sélectionnez la bibliothèque Adafruit NeoPixel dans la liste des résultats.
    - Cliquez sur le bouton "Installer" (Install).

3. Utilisation de la bibliothèque Adafruit NeoPixel :
    - Pour utiliser la bibliothèque dans votre code, incluez la ligne suivante en haut de votre fichier d'esquisse Arduino :
    `include <Adafruit_NeoPixel.h>`

4. Copie du fichier main.cpp depuis le référentiel Git `Arduino/arduino-ws2812led/arduino-ws2812led.ino` :
    - Assurez-vous d'avoir cloné ou téléchargé le référentiel Git arduino-ws2812led.
    - Naviguez jusqu'au répertoire où se trouve le fichier main.cpp dans votre système de fichiers.
    - Copiez le fichier main.cpp dans votre IDE Arduino.
    - Collez le contenu du fichier main.cpp dans un nouvel onglet ou un nouveau fichier dans l'IDE Arduino.
    - Enregistrez le fichier avec un nom approprié, par exemple my_led_control.ino.

5. Connexion des broches de contrôle de la bande de LED

    - Assurez-vous de connecter les broches de contrôle de votre bande de LED NeoPixel à votre carte Arduino selon la séquence suivante :
        - Broche de contrôle de la bande de LED -> Broche Arduino
        - 6ème broche de contrôle -> Broche 6 de l'Arduino
        - 5ème broche de contrôle -> Broche 5 de l'Arduino
        - 4ème broche de contrôle -> Broche 4 de l'Arduino
        - 3ème broche de contrôle -> Broche 3 de l'Arduino
        - 2ème broche de contrôle -> Broche 2 de l'Arduino


