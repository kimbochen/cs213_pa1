speedup_test()
{
    ALGO="$1Seq" DBG="-DPROF" make
    for i in {1..3};
    do
        echo "Testing matrix$i.txt w/ $1Seq..."
        ./spmv "testcases/matrix$i.txt" 8 1
        echo "----------------------------------------"
    done
    make clean
    echo "----------------------------------------"

    ALGO="$1OpenMP" DBG="-DPROF" make
    for i in {1..3};
    do
        for t in {2,4,8,16,32};
        do
            echo "Testing matrix$i.txt w/ $1OpenMP $t threads ..."
            ./spmv "testcases/matrix$i.txt" 8 $t
            echo "----------------------------------------"
        done
    done
    make clean
}

# speedup_test "CSR"
speedup_test "CSC"
