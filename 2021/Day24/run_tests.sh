if [[ -d "build" ]]; then
    rm -rf build
fi

if [[ -f "/tmp/test.log" ]]; then
    rm /tmp/test.log
fi

mkdir build
cd build
cmake ..
make
valgrind --leak-check=full --error-exitcode=1 --track-origins=yes -s ./*_exe 1>> /tmp/test.log 2>&1
cd ..
cat /tmp/test.log
failure_messages=$(grep FAILED /tmp/test.log)
[ -z "$failure_messages" ]
exit_status=$?
exit $exit_status