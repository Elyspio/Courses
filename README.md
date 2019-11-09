
# Objectifs

- Réaliser un environement client serveur pour :
    - envoie de message (avec réponse)
    - envoie de données (sans réponse)
    - envoie d'un calcul à effectuer
    - analyse d'une image et envoie au server d'une liste des principales couleurs de celle-ci

- Les échanges se font à travers des sockets.

- Les échanges se font au format json 

# Fichiers

README.md

INSTALL.md

CONTRIBUTORS.md

Makefile

src
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
    - json.c (verification.c)
    - json.h (verification.h)
    - tools.c
    - tools.h
    - types.c
    - types.h
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

Dur
- Problème avec realloc et la gestion de la mémoire en général, 
- Les couleurs récupérées par 'analyse' ne sont pas les bonnes, 
- Les void* sont capricieux
+ Projet très chronophage si l'on veut faire quelque chose de générique