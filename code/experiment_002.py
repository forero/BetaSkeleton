from subprocess import call

total_mocks = 27
base_mass = [1.0E13]
base_f_in = [1.0]
rsd_options = [1]
beta_values = [1,2,5,10,20,30]

min_theta=90.0
max_theta=180.0
min_phi=[0.0,89.0]
max_phi=[1.0,90.0]
min_r=0.0
max_r=2000.0
omega_m_values = [0.10, 0.20, 0.30, 0.40, 0.50]
w_values = [-0.8,-0.9,-1.0,-1.1,-1.2]

for i_mock in range(total_mocks):
    for rsd in rsd_options:
        for beta in beta_values:
            for i_mass, i_f_in in zip(base_mass, base_f_in):
                for i_min_phi, i_max_phi in zip(min_phi, max_phi):
                    for w in w_values:
                        for omega_m in omega_m_values:
                            command_all=\
                                "make -f Makefile %s MOCK_ID=%02d BETA=%d CUT_MASS=%.1E FRAC=%.4f \
                         RSD=%d MIN_THETA=%.1f MAX_THETA=%.1f MIN_PHI=%.1f MAX_PHI=%.1f MIN_R=%.1f MAX_R=%.1f \
                         OMEGA_M=%.2f OMEGA_L=%.2f W=%.1f" \
                                %("all", i_mock, beta, i_mass, i_f_in, rsd, min_theta, max_theta, \
                                      i_min_phi, i_max_phi, min_r, max_r, omega_m, 1.0 - omega_m, w)
                         
                    print command_all
                    retcode = call(command_all,shell=True)
