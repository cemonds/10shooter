#!/bin/bash

echo "Content-Type: text/html"
echo ""
echo "<html>"
echo "<body>"
echo "Hallo Cocktail"
$command = $(echo $QUERY_STRING | cut -d "=" -f 3)
echo $command > /dev/ttyS0
awk `
/finished/ {exit;}
 {print;}` < /dev/ttyS0 > /tmp/currentControl

    for line in $(cat /tmp/currentControl)
    do
        if [ $line = "Cocktail finished" ]; then
            break
        else
            echo "<p>$line</p>"
        fi
    done

echo "</body>"
echo "</html>"

exit 0

