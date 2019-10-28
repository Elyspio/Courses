# Tâche 1

## Objectifs

* Réaliser un environement client serveur pour :

  + envoie de message (avec réponse)
  + envoie de données (sans réponse)
  + envoie d'un calcul à effectuer
  + envoie d'une liste de couleurs à stocker au niveau du serveur

* Les échanges se font à travers des sockets.

## Fichiers

README.md

INSTALL.md

CONTRIBUTORS.md

Makefile

src

* task1
  + client
    - client.c
    - client.h
  + common
    - const.c
    - const.h
    - tools.c
    - tools.h
  + server
    - server.c
    - server.h

## Bibliothèques

* `string.h` pour la manipulation des chaines de caractères
* `stdlib.h` pour la manipulation de mémoire
* `stdio.h` pour les entrées/sorties
* `sys/socket.h` pour les sockets entre le client et le serveur
* `time.h` pour la récupération de l'heure

## Référence

/

## Difficulté

Facile

