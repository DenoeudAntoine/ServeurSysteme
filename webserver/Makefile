# Ces variables servent � pr�ciser le compilateur que l�on veut utiliser
# ainsi que les param�tres de compilation
CC=gcc
LD=gcc
CFLAGS=-Wall -W -Werror
LDFLAGS=
# Le nom de l�ex�cutable � fabriquer
EXE=pawnee
# Les variables HEADERS, CFILES et OBJS vont contenir respectivement
# la listes des fichiers .h, .c et le nom des fichiers .o � fabriquer
# On utilise la directive particuli�re $(wildcard ...) qui permet
# de construire automatiquement une liste de fichiers
HEADERS=$(wildcard *.h)
CFILES=$(wildcard *.c)
# Cette construction de variable veut dire: remplacer la chaine ".c" par
# ".o" dans la variable CFILES
# Ceci nous permet de construire la liste des fichiers .o � fabriquer
OBJS=$(CFILES : .c=.o)
# M�me utilisation que pr�c�demment. On pr�cise les r�gles qui
# ne fabrique pas de fichier du nom de leur cible
.PHONY: all clean mrproper
# La r�gle par d�faut d�clenche la fabrication de l�ex�cutable
# par d�pendance 
all: $(EXE)
# Cette r�gle permet de construire l�ex�cutable. Elle d�pend des fichiers
# .o et effectue l��dition de lien. Rien de nouveau ici
$(EXE): $(OBJS) Main.c socket.c
	$(LD) $^ $(LDFLAGS) -o $@
# Cette r�gle permet de construire automatiquement les r�gles
# de compilation pour chacun des fichiers .c
# l�option -MM de gcc analyse un fichier .c et
# affiche sur sa sortie standard une r�gle compatible
# make pour le compiler.
# Ceci permet d�ajouter automatiquement les fichiers .h aux d�pendances
# des fichiers .o � construire. Ainsi, en modifiant un fichier .h
# tous les fichiers .c qui incluent ce fichier sont recompil�s
# Apr�s votre premi�re compilation, regardez le contenu du fichier
# makefile.dep g�n�r� afin de comprendre exactement de quoi il retourne.
makefile.dep: $(CFILES) $(HEADERS)
	$(CC) -MM $(CFILES) > $@
# Cette r�gle efface le fichier de d�pendances et les fichiers .o
clean:
	$(RM) $(OBJS) makefile.dep
# Cette r�gle effectue la pr�c�dente et efface en plus l�ex�cutable
mrproper: clean
	$(RM) $(EXE)
# On inclue le fichier de d�pendance qui va contenir les r�gles
# de construction des fichiers .o
# S�il n�existe pas, make invoque automatiquement la r�gle
# qui l�a pour cible
include makefile.dep
