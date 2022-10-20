TCASE=$1
N_ITER=$2
N_THREAD=$3

diff <(./spmv $TCASE $N_ITER $N_THREAD) <(python3 get_ans.py $TCASE $N_ITER)
