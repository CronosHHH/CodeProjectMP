touch tests//.timeout
CMD=" /home/renato/Desktop/CodeProjectMP/Fraud1/build/Fraud1  < ../Datasets/dataP1/princeton.p1in 1> tests//.out8 2>&1"
eval $CMD
rm tests//.timeout
