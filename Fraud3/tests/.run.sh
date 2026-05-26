touch tests//.timeout
CMD="valgrind --leak-check=full /home/renato/Desktop/CodeProjectMP/Fraud3/build/Fraud3  -K 3 -o tests/output/output.dts 1> tests//.out1 2>&1"
eval $CMD
rm tests//.timeout
