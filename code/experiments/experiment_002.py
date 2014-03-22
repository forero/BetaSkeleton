from subprocess import call

total_mocks = 27
base_mass = [1.0E13, 5.0E13, 1.0E14]
base_f_in = [0.004 , 0.02  , 0.10]
rsd_options = [0,1]
beta_values = [1,5,10,15,20,25,30]

for i_mock in range(total_mocks):
    for rsd in rsd_options:
        for beta in beta_values:
            for i_mass, i_f_in in zip(base_mass, base_f_in):

                command_all="make -f Makefile %s MOCK_ID=%02d BETA=%d CUT_MASS=%.1E FRAC=%.4f RSD=%d"%("all", i_mock, beta, i_mass, i_f_in, rsd)
                command_clean="make -f Makefile %s MOCK_ID=%02d BETA=%d CUT_MASS=%.1E FRAC=%.4f RSD=%d"%("clean", i_mock, beta, i_mass, i_f_in, rsd)

                retcode = call(command_clean,shell=True)
                retcode = call(command_all,shell=True)
