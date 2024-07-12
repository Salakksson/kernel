#!/bin/bash

set -e 

if [ $# -le 0 ]; then
    echo "Usage: generate_isr_include.sh <filename>"
    exit 1
fi

error_codes="8 10 11 12 13 14 17 21 29 30"

file=$1

echo "assembly:" >> $file

for i in $(seq 0 255); 
do
    if echo "$error_codes" | grep -q "\b${i}\b"; 
    then
        echo "ISR_ERROR ${i}" >> $file
    else
        echo "ISR_NOERROR ${i}" >> $file
    fi
done


echo "c:" >> $file

for i in $(seq 0 255); 
do
    echo "void isr${i}();" >> $file
done

for i in $(seq 0 255); 
do
    echo "fill_idt_entry(${i}, isr${i}, 1, DPL_RING0 | IDT_FLAG_INT | IDT_FLAG_PRESENT);" >> $file
done
