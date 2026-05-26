touch tests//.timeout
CMD="valgrind --leak-check=full /home/renato/Desktop/CodeProjectMP/Fraud4/build/Fraud4  -K1 10 -K2 7 ../Datasets/princeton_training.dts ../Datasets/princeton_test.dts 1> tests//.out16 2>&1"
eval $CMD
rm tests//.timeout
