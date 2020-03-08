#! /bin/bash

i=0

for i in {1..100}
do
    make re && ./test_thread_pool
done