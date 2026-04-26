touch tests//.timeout
CMD="valgrind --leak-check=full /home/toniverger/Escritorio/MP/CodeProjectMP/Fraud2/build/Fraud2  5 0 3 ../Datasets/dataP2/princeton_names.loc 1> tests//.out11 2>&1"
eval $CMD
rm tests//.timeout
