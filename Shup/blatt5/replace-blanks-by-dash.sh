#!/bin/bash

echo "Aufrufparameter ist '$1'"

output_tr="$(echo $1 | tr " " "-")" # $1 without quotation marks, so multiple blanks get removed

echo "Mit tr: '$output_tr'"

output_sed="$(echo $1 | sed "s/ /-/g")" # $1 without quotation marks, so multiple blanks get removed

echo "Mit sed: '$output_sed'"


