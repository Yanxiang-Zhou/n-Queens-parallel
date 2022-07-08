#!/bin/bash -e
k=0
e=0
for n in 6 8 10; do
    echo "Testing n=$n"
    f="out_${n}_1_${k}_${e}.txt"
    rm -f "$f"
    ./nqueen "$n" "$k" "$e"
    if diff <(sort "$f") <(sort "sample/${n}.txt") > /dev/null ; then
        echo "Outputs match on n=${n}"
    else
        echo "Outputs didn't match on n=${n}"
    fi
    echo
done

