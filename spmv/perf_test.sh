perf_test()
{
    ALGO="$1Seq" DBG="-DPROF" make
    ./spmv "testcases/matrix3.txt" 8 1
    make clean
    echo "------------------------------"

    ALGO="$1OpenMP" DBG="-DPROF" make
    for t in {2,4,8,16,32};
    do
        echo "Testing $1 w/ n_threads = $t..."
        ./spmv "testcases/matrix3.txt" 8 $t
        echo "------------------------------"
    done
    make clean
}


perf_test "CSR"
perf_test "CSC"
