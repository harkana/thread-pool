#! /bin/bash

i=0

for i in {1..500}
do
    a=$(./test_thread_pool)
    echo $?
done