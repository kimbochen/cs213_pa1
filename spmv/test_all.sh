verify_algo()
{
    make clean
    ALGO=$1 make
    for i in {1..3}; do
        ./verify.sh "testcases/matrix$i.txt" 8 8;
    done
}

verify_algo "CSRSeq"
verify_algo "CSROpenMP"
verify_algo "CSCSeq"
verify_algo "CSCOpenMP"
