#!/bin/bash

IDSK=$CPCT_PATH/tools/iDSK-0.13/bin/iDSK
SOURCE=rpg.bas
TARGET=rpg.dsk
RVM=/Applications/Retro\ Virtual\ Machine\ 2.app/Contents/MacOS/Retro\ Virtual\ Machine\ 2
PRESENTATION_FILE=present.txt

# CREATE DSK
$IDSK $TARGET -n

# Convert to MSDOS CR+LF LINE FORMAT
# brew install unix2dos
unix2dos $SOURCE
unix2dos $PRESENTATION_FILE

# ADD TO DSK
$IDSK $TARGET -i $SOURCE -t 0
$IDSK $TARGET -i $PRESENTATION_FILE -t 0

# LAUNCH RVM
"$RVM" -b=cpc6128 -insert $TARGET -c='RUN"rpg\n'