#!/bin/bash

IDSK=$CPCT_PATH/tools/iDSK-0.13/bin/iDSK
SOURCE=rpg.bas
DESTINATION=rpggame.bas
TARGET=rpg.dsk
RVM=/Applications/Retro\ Virtual\ Machine\ 2.app/Contents/MacOS/Retro\ Virtual\ Machine\ 2
PRESENTATION_FILE=present.txt

# REMOVE COMMENTS FROM BASIC FILE
grep -v "'" $SOURCE > $DESTINATION

# CREATE DSK
$IDSK $TARGET -n

# Convert to MSDOS CR+LF LINE FORMAT
# This needs unix2dos util 
# brew install unix2dos
unix2dos $SOURCE
unix2dos $DESTINATION
unix2dos $PRESENTATION_FILE

# ADD TO DSK
$IDSK $TARGET -i $SOURCE -t 0
$IDSK $TARGET -i $DESTINATION -t 0
$IDSK $TARGET -i $PRESENTATION_FILE -t 0

# ONCE MINIMIFIED FILE IS IN DSK, DELETE IT
rm $DESTINATION

# LAUNCH RVM
"$RVM" -b=cpc6128 -insert $TARGET -c="RUN\"$DESTINATION\n"