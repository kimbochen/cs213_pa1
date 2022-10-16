import sys
import numpy as np
import scipy.sparse as sp


data = np.loadtxt(sys.argv[1])

m, n = map(int, data[0, :2])
idxs, val = data[1:, :2], data[1:, 2]
idxs = idxs - 1
row, col = idxs[:, 0], idxs[:, 1]


mat = sp.coo_matrix((val, (row, col)), shape=(m, n))
x = np.ones([m, 1], dtype=np.float64)

n_iter = int(sys.argv[2])
for _ in range(n_iter):
    x = mat @ x
print(x)
