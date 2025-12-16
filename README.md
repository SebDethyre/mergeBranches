# mergeBranches

**Languages:**  
- [English](#-english)  
- [Français](#-français)

---

## 🇬🇧 English

## SVN Branch Merger GUI

This application provides a graphical interface to easily merge two Subversion (SVN) branches. It allows developers to visually select the source and target branches and perform a merge in a terminal.

## ✨ Features

Interactive GTK TreeView interface for merging SVN branches (Subversion).
  
- Custom handling of integration branch suffixes (e.g., develop, refonte-graphique, rec4).
- Automatic SVN merge command generation.
- Opens a gnome-terminal to execute the merge and show the output.

## ⌨️ Keyboard shortcuts:

- Escape or X → Quit the application.
- Right Arrow or Tab → Move focus to the next TreeView.
- Left Arrow or Tab → Move focus to the previous TreeView.

## 🧩 How it Works

- Executes a script (list_devs_merge) to list available branches.
- Reads branch names from results.txt.
- Displays branches in two side-by-side TreeViews.
- The user selects the source branch (left) and target branch (right).
- Clicking the Merge button runs the appropriate SVN merge command in a terminal.
- Opens a terminal displaying the correct string/commit for merging a development branch into an integration branch, and vice versa

## 📦 Requirements

- GTK3
- xdotool
- Subversion (svn)
- Gnome-terminal
- Linux environment

## 🚀 Installation

- Place the source code in a folder.
- Ensure your configuration file (config.conf) exists and contains the key current_appli.

### Compile the program:
```bash
gcc -o svn_merger svn_merger.c `pkg-config --cflags --libs gtk+-3.0` -lX11
```

## ▶️ Run:

./svn_merger

## 📝 Notes

Branches with special suffixes are treated differently for merge messages.  
The application relies on external scripts and configuration files located in /home/sdethyre/sandbox/dash_dev_boisson/.

---

## 📄 License

To be defined.

## 👤 Author

Project developed as an advanced tooling initiative around Subversion versioning by Sébastien Dethyre.

## 🤝 Contributions

Contributions, suggestions, and feedback are welcome.  
Feel free to open an issue or submit a pull request.
  
---

<br>

---

## 🇫🇷 Français

## Interface Graphique de Fusion SVN

Cette application fournit une interface graphique pour fusionner facilement deux branches Subversion (SVN). Elle permet aux développeurs de sélectionner visuellement les branches source et cible et d'effectuer la fusion dans un terminal.

# ✨ Fonctionnalités

Interface GTK TreeView interactive pour la fusion de branches SVN (Subversion).
  
- Gestion personnalisée des suffixes de branches (ex. develop, refonte-graphique, rec4).
- Génération automatique de la commande SVN merge.
- Ouverture d'un terminal GNOME pour exécuter la fusion et afficher la sortie.

## ⌨️ Raccourcis clavier :

- Escape ou X → Quitter l'application.
- Flèche droite ou Tabulation → Déplacer le focus vers le TreeView suivant.
- Flèche gauche ou Tabulation → Déplacer le focus vers le TreeView précédent.

## 🧩 Fonctionnement

- Exécute le script (list_devs_merge) pour lister les branches disponibles.
- Lit les noms de branches dans results.txt.
- Affiche les branches dans deux TreeViews côte à côte.
- L'utilisateur sélectionne la branche source (gauche) et la branche cible (droite).
- Cliquer sur le bouton Merge exécute la commande SVN merge appropriée dans un terminal.
- Ouvre un terminal affichant la bonne string/commit contenant le merge d'une branche de développement vers celle d'intégration, et inversement.

## 📦 Prérequis

- GTK3
- xdotool
- Subversion (svn)
- Gnome-terminal
- Environnement Linux

## 🚀 Installation

Placez le code source dans un dossier.
Assurez-vous que le fichier de configuration (config.conf) existe et contient la clé current_appli.

### Compiler le programme :

```bash
gcc -o svn_merger svn_merger.c `pkg-config --cflags --libs gtk+-3.0` -lX11
```

## ▶️ Exécuter :

./svn_merger

## 📝 Remarques

Les branches avec des suffixes spéciaux sont traitées différemment pour les messages de fusion.  
L'application dépend de scripts et fichiers de configuration externes situés dans /home/sdethyre/sandbox/dash_dev_boisson/.

---

## 📄 Licence

À définir.

---

## 👤 Auteur

Projet développé dans un objectif d’outillage avancé autour versioning Subversion par Sébastien Dethyre.

---

## 🤝 Contributions

Les contributions, suggestions et retours sont les bienvenus.  
N’hésitez pas à ouvrir une issue ou une pull request.
