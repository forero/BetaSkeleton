from subprocess import call

total_mocks = 27
base_mass = [1.0E13]
base_f_in = [1.0]
rsd_options = [0,1]
beta_values = [1,2,5,10,15,20,25,30]

min_theta=90.0
max_theta=180.0
min_phi=[0.0,89.0,179.0]
max_phi=[1.0,90.0,180.0]
min_r=0.0
max_r=2000.0

for i_mock in range(total_mocks):
    for rsd in rsd_options:
        for beta in beta_values:
            for i_mass, i_f_in in zip(base_mass, base_f_in):
                for i_min_phi, i_max_phi in zip(min_phi, max_phi):
                    command_all=\
                        "make -f Makefile %s MOCK_ID=%02d BETA=%d CUT_MASS=%.1E FRAC=%.4f \
                         RSD=%d MIN_THETA=%.1f MAX_THETA=%.1f MIN_PHI=%.1f MAX_PHI=%.1f MIN_R=%.1f MAX_R=%.1f" \
                        %("all", i_mock, beta, i_mass, i_f_in, rsd, min_theta, max_theta, i_min_phi, i_max_phi, min_r, max_r)

                    print command_all
                    retcode = call(command_all,shell=True)
