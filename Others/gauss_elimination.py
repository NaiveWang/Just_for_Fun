from numpy import array
from scipy.linalg import lu

a = array([[1,1,1,1],[1,2,2,3],[1,2,1,4]])
print(a)
pl,a = lu(a, permute_l=True)
print(a)
