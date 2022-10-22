generate()
{
    make clean
    ALGO="$1OpenMP" make
    for i in {1..3}; do
        ./spmv "testcases/matrix$i.txt" 8 8 > "$1Vec$i.txt";
        python3 get_ans.py "testcases/matrix$i.txt" 8 | diff "$1Vec$i.txt" -;
    done
}

generate "CSR"
generate "CSC"
