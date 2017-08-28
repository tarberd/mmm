
max=$1

for (( i=1000, j=3; i <= 1000000000; i*=10, ++j))
do
    ./uniform_generator input/input${j} 123 ${i}
    touch output/out${j}

    echo output/out${j}
    for (( x=1; x <= $max; ++x ))
    do
        ./mmm input/input${j} >> output/out${j}
    done
done
