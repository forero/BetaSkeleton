from subprocess import call

total_mocks = 27
base_mass = [1.0E14]
base_f_in = [0.05]
rsd_options = [1]
beta_values = [1,5,10,15,20,25,30]
omega_m=0.50
omega_l=0.50
w=-1.0

for i_mock in range(total_mocks):
    for rsd in rsd_options:
        for beta in beta_values:
            for i_mass, i_f_in in zip(base_mass, base_f_in):

                command_all="make -f Makefile %s MOCK_ID=%02d BETA=%d CUT_MASS=%.1E FRAC=%.4f RSD=%d OMEGA_M=%.2f OMEGA_L=%.2f W=%.2f"%("all", i_mock, beta, i_mass, i_f_in, rsd, omega_m, omega_l, w)

                retcode = call(command_all,shell=True)
