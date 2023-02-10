# Application Smart Farm
Application de gestion de ferme, elle permet l'ajout, modification, suppression, et la mise à jour des différents équipements (Capteurs) installés dans la ferme.

Cette application est développée avec l'outil Glade sous Ubuntu 18, la bibliothèque GTK, GDK, et le langage de programmation C. 

## Ce projet comporte :
* Authentification flexible qui - selon l’identifiant entré -  permet l’accès soit à l’espace admin soit à l’espace employé .
* Espace employé : 

        - Gestion des capteurs. 
        - Gestion des clients.
        - Gestion des troupeaux.

* Espace Admin :
	- La marque ayant le maximum des capteurs défectueux.
 	- La liste des capteurs ayant des valeurs alarmantes. (*) 
	- Le taux d’absentéisme.
	- Le nombre de troupeaux de chaque type.
 	- Le meilleur ouvrier.
 	- L'année la plus sèche.

  - Un API SMS a été intégré dans le code (**)



