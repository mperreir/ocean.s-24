# Guide technique de réalisation et d’installation du projet

## Matériel nécessaire

- 2 arduino (1 pour la gestion des capteurs et 1 pour les bandes led et bouton)
- un multiplexeur (pour connecter plusieurs capteur de profondeur)
- un bouton (pour activer l’animation et passer les différentes étapes)
- 5 bandes led (pour simuler le niveau de la mers avec la couleur)
- 1 écran (pour l’affichage de l’animation)
- Des câbles

## Logiciels nécessaires et procédure d'installation

### Assurez-vous d'avoir cloné ou téléchargé le référentiel Git

### Unreal Engine
Installer la bonne version de Unreal Engine
1. Installer Epic Games d’après le lien : <https://store.epicgames.com/en-US/download>
2. Il faut ensuite créer un compte Epic Games.
3. Puis, il faut ouvrir le Epic Games Launcher et être sûre qu’on est dans la section “Unreal Engine” (parmi les tabs de navbar à gauche).
4. Dans le navbar tout en haut, il faut aller à “Library” et sous “Engine Versions” il faut choisir “+”.
5. Une nouvelle brique d’installation de Unreal Engine s’affiche, il faut sélectionner “5.0.3” de la liste déroulante qui s’affiche en s’appuyant sur le numéro de version qui se met par défaut (5.4.0).

**Rq : Il faut noter que l’installation de UE prend du temps, la taille est aux alentours de 100Gb.**

Vérifier qu’on a les bonnes plugins activé et installé

**Rq : Pas besoin de re-installer les plugins, ils sont déjà incluent dans le code envoyé dans sa partie de UE, il faut juste les activer**

6. Tout d’abord, il faut ouvrir le projet UE 
    1. On lance **Unreal Engine** 5.0.3 à partir de Epic Games Launcher dans le même endroit là on a installé, on trouve un bouton “Launch” dans la brique d’installation.
    2. Il faut ensuite sélectionner “Browse” tout en bas dans le menu de sélection de projets.
    3. Puis, il faut choisir “Ocean2.uproject” sous le dossier “Ocean2 UE” dans le projet déposé sur Git.


7. Une fois dans le projet UE, il faut aller dans Edit -> Plugins dans le navbar tout en haut.

8. Une fois dans le menu des plugins, il faut activer les deux plugins : 
    - Water
    - Communication Serial Port (Serial COM)

9. Relancer le projet (Refaire a)

### Arduino: l'IDE Arduino
Téléchargement et installation d'Arduino :
- Rendez-vous sur le site officiel d'Arduino : <https://www.arduino.cc/>.
- Téléchargez la dernière version du logiciel Arduino compatible avec votre système d'exploitation.
- Suivez les instructions d'installation fournies sur le site.

Installation des bibliothèques nécessaire :
- Ouvrez l'IDE Arduino.
- Allez dans le menu "Croquis" (Sketch) -> "Inclure une bibliothèque" (Include Library) -> "Gérer les bibliothèques" (Manage Libraries).
- Dans la fenêtre qui s'ouvre, recherchez "Adafruit NeoPixel" dans la barre de recherche.
- Sélectionnez la bibliothèque Adafruit NeoPixel dans la liste des résultats.
- Cliquez sur le bouton "Installer" (Install).
- Faire de même avec la librairie “DFRobot_VL53L0X”

## Procédure de montage
Après avoir installé le logiciel et les librairies nécessaire il faut faire le montage : 
1. Connexion des broches de contrôle de la bande de LED (avec arduino 1):

    Assurez-vous de connecter les broches de contrôle de votre bande de LED NeoPixel à votre carte Arduino selon la séquence suivante :
    
    Broche de contrôle de la bande de LED -> Broche Arduino
- 6ème broche de contrôle -> Broche 6 de l'Arduino
- 5ème broche de contrôle -> Broche 5 de l'Arduino
- 4ème broche de contrôle -> Broche 4 de l'Arduino
- 3ème broche de contrôle -> Broche 3 de l'Arduino
- 2ème broche de contrôle -> Broche 2 de l'Arduino

2. Connexion du bouton (avec l’arduino 1):
- branché le bouton sur le pin 8 de l’arduino

3. Connexion des capteurs de profondeur : 
- Banché les broches SDA, SCL entres l’arduino et un multiplexeur 
- Branché les broches SD et SC du multiplexeur de 0 au nombre de capteur voulu (pour notre cas 5, ce qui indique d’utiliser les ports du multiplexeur 0 à 4) aux capteurs de profondeur (VL53L0X Gravity)
- Vous pouvez tester les branchements des capteurs sur le multiplexeur en testant le code arduino “detect_connexion_port_multiplexage”.

## Procédures de lancement du projet 

1. Sur le logiciel arduino, ouvrez les sketchs (code arduino) : “control_bouton_lumiere” et “control_capteur”
2. Exécuter les codes sur l’arduino correspondant (sur le port série indiqué dans le code Unreal)
3. Finalement il suffit de lancer le projet UE 
    1. Il faut vérifier qu’on est bien dans le level “Ocean”. Si ce n’est pas le cas par défaut (on ne voit pas le tab nommé “Ocean” tout en haut directement sous le navbar) : 
        - Dans le “Content Browser” en bas, aller dans le dossier 
Content -> Levels et double click sur “Ocean”

    2. Il suffit de cliquer sur le bouton triangulaire en vert “Play this level” qui se trouve en haut sous le navbar pour lancer l’animation.



