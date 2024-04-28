# ocean.s-24
Source code of the Ocean.s-24 projects

## Serveur Web

### installer les dépendances
```
npm install
```

### compiler le projet
```
npm run build
```
cd server
node app.js

go to localhost:3010/datapage
go to localhost:3010/userpage

### Customize configuration
See [Configuration Reference](https://cli.vuejs.org/config/).



## ESP32

### Installation

1. Installer l'IDE Arduino
2. Installer les librairies suivantes:
    - FastLED
    - ArduinoJson

### Configuration

1. Connecter au bon port série (pour le board : ESP32 DEV Module)
2. Configurer le SSID et le mot de passe du réseau WiFi
3. Configurer l'adresse IP du serveur
4. Configurer le nombre de LEDs
