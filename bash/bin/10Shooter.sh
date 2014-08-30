#!/bin/bash

# Initialisierung

echo "Beginne Initialisierung!"
BIN_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
WORKSPACE="$BIN_DIR/.."
WEBDIR=/var/www/10shooter
INDEX=$WORKSPACE/web/html/index.html
echo "Räume auf..."
rm $WEBDIR/*.*
rm $WORKSPACE/web/html/*.*
rm $WORKSPACE/*.rezept
IFS=$'\n'
### Liest die geladenen Flaschen ein. Bestückung in ~/10shooter/misc/munition.txt editieren 
echo "Lade meine Munition..."
header=0
for line in $(cat $WORKSPACE/misc/munition.txt) 
	do

		if [ "$header" = "0" ]; then
			header=1
		else
			slot=$(echo $line|cut -d "#" -f 1)
			name=$(echo $line|cut -d "#" -f 2)
			munition[$slot]=$name
		fi
	done

for ((i=0; i<=9; i++))
	do
		echo "Slot $i ${munition[$i]}"
	done

### Durchsucht die vorhandenen Rezepte anhand der geladenen Getränke. Entsprechende Dateien enden auf *.rezepte und werden in ~/10shooter/misc/rezepte erwartet

echo "Checke mögliche Operationen... "

REZEPTE=$(find $WORKSPACE/misc/rezepte -type f -name "*.rezept")

for file in $REZEPTE
	do
	echo -e "\033[1m# + # + # + # + # + # + # + # + # + # + # + # + # + #\033[0m"	
	echo "Checke Zutaten für $file "
	allesda=1
		for line in $(cat $file)
			do
				zutat=$(echo $line|cut -d "#" -s -f 2)
				if [ "$zutat" ]; then
					treffer=0
					echo "Suche: $zutat..."
					for ((i=0; i<=9; i++))
						do
							if [ "${munition[$i]}" = "$zutat" ]; then
								treffer=1
								echo -e "\033[32m$zutat gefunden!!\033[0m"
							else 
								if [ "$i" = "9" ] && [ "$treffer" = "0" ] ; then
								allesda=0
								echo -e "\033[31mEs fehlt: $zutat!\033[0m"
								fi
							fi
						done
				fi
			done
	if [ "$allesda" = "1" ]; then
		echo "Alles gefunden! Kopiere Rezept..."
		cp $file $WORKSPACE
	else
		echo "Mir fehlt etwas!"
	fi
	done

### Baut die Webseiten anhand der Übereinstimmtung Munition <-> Rezepte auf

echo "#-#-#-#-#-#-#-#  Webseiten #-#-#-#-#-#-#-#" 
echo "- - - Kopiere format.css - - -"
cp $WORKSPACE/web/format.css $WEBDIR
echo "- - - Baue und kopiere Index.html - - -"
cat $WORKSPACE/web/head/index.head>>$INDEX
TREFFER=$(find $WORKSPACE -maxdepth 1 -type f -name "*.rezept")
for file in $TREFFER
	do
		datei=$(basename $file .rezept)
		for line in $(cat $file)
			do
				if [ $(echo $line | cut -d ":" -f 1) = "Name"  ]; then
					name=$(echo $line | cut -d ":" -f 2 | sed -e 's/^[ \t]*//;s/[ \t]*$//')
					echo "Nehme \"$name\" im Index auf..."
					echo "</br> <a href="$datei".html>"$name"</a>">>$INDEX
				fi
			done
	done
cat $WORKSPACE/web/foot/index.foot>>$INDEX
cp $INDEX $WEBDIR 
echo "Index.html generiert und kopiert!"

echo "- - - Baue und kopiere Seite der einzelnen Drinks - - -"
for file in $TREFFER
	do
		datei=$(basename $file .rezept)
		webseite=$WORKSPACE/web/html/$datei.html
		echo "- - - Ertelle "$datei".html"
		cat $WORKSPACE/web/head/drink.head>>$webseite
		for line in $(cat $file)
			do
				if [ $(echo $line | cut -d ":" -f 1) = "Name"  ]; then
					name=$(echo $line | cut -d ":" -f 2|sed -e 's/^[ \t]*//;s/[ \t]*$//')
					echo "<h2>"$name"</h2>">>$webseite
				elif [ $(echo $line | cut -d ":" -f 1) = "Bild"  ]; then
					pfad=$(echo $line|cut -d ":" -f 2|sed -e 's/^[ \t]*//;s/[ \t]*$//')
					jpg=$(basename $pfad)
					cp $WORKSPACE/misc/pics/$jpg $WEBDIR/$jpg	
					echo "<p><img src=\""$jpg"\" alt=\"Bild\"></p>">>$webseite
					echo "Zutaten:">>$webseite
				elif [ $(echo $line | cut -d "#" -s -f 1) ]; then
					echo "</br>"$(echo $line | cut -d "#" -s -f 1)" * 2cl "$(echo $line | cut -d "#" -s -f 2)>>$webseite
				elif [ $(echo $line | cut -d ":" -f 1) = "Hinterher" ]; then
					echo "</br>Hinterher:">>$webseite	
				elif [ $(echo $line | cut -c 1) = "-" ]; then
					echo "</br> -" $(echo $line | cut -c 3-)>>$webseite
				fi
				
			done
		echo '<form action="cgi-bin/control.sh" method="GET" >' >>$webseite
		cocktailControlCode="n5ttn6tn1t"
		echo "<input name=\"command\" type=\"hidden\" value=\"$cocktailControlCode\">" >>$webseite
		echo '<input type="submit" value="Mixen" />' >>$webseite
		echo '</form>' >>$webseite
		cat $WORKSPACE/web/foot/drink.foot>>$webseite
		cp $webseite $WEBDIR
		echo $datei".html erstellt und kopiert"
	done


