import numpy as np
from scipy import stats
import sys
import random

def KS_test_edges(filename):
    edge_data = np.loadtxt(filename)
    edge_length = np.sqrt(edge_data[:,0]**2 
                       + edge_data[:,1]**2 
                       + edge_data[:,2]**2) 

    #pick a random unit vector over the sphere
    phi = 2.0*np.pi*random.random()
    theta = np.arccos(2.0*(random.random()-0.5))
    x_unit = np.sin(theta) * np.cos(phi)
    y_unit = np.sin(theta) * np.sin(phi)
    z_unit = np.cos(theta)

    mu = abs((edge_data[:,0]*x_unit 
              + edge_data[:,1]*y_unit + edge_data[:,2]*z_unit))/edge_length
    n_points = np.size(mu)
    mu_flat = np.linspace(0.0,1.0,n_points)
    KS_stat, p_value = stats.ks_2samp(mu, mu_flat)
    return KS_stat, p_value 

if __name__ == '__main__':
    filein = sys.argv[1]    
    ks, p_value = KS_test_edges(filein)
    print ks, p_value
