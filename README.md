
# Objectifs

- Réaliser un environement client serveur pour :
    - envoie de message (avec réponse)
    - envoie de données (sans réponse)
    - envoie d'un calcul à effectuer
    - analyse d'une image et envoie au server d'une liste des principales couleurs de celle-ci

- Les échanges se font à travers des sockets.


# Fichiers

README.md

INSTALL.md

CONTRIBUTORS.md

Makefile

src
- task2
    - client
        - bmp.c
        - bmp.h
        - client.c
        - client.h
        - couleur.c
        - couleur.h
    - common
        - const.c
        - const.h
        - enum.c
        - enum.h
        - json.c
        - json.h
        - tools.c
        - tools.h
    - server
        - server.c
        - server.h


# Bibliothèques

- `string.h` pour la manipulation des chaines de caractères
- `stdlib.h` pour la manipulation de mémoire
- `stdio.h` pour les entrées/sorties
- `sys/socket.h` pour les sockets entre le client et le serveur
- `time.h` pour la récupération de l'heure

# Référence 

/ 

# Difficulté

Moyen (parsing réel du json et non brutforce)
