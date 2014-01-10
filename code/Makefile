test_io.x: test_io.c io_mock.c io_mock.h
	cc test_io.c io_mock.c -o test_io.x

sub_sample.x: sub_sample.c io_mock.c io_mock.h
	cc sub_sample.c io_mock.c -o sub_sample.x

rv.x: radial_velocities.c io_mock.c io_mock.h
	cc -lm radial_velocities.c io_mock.c -o rv.x

c2s.x:cartesian2spherical.c io_mock.c io_mock.h
	cc -lm cartesian2spherical.c io_mock.c -o c2s.x

r2z.x: radial2redshift.c io_mock.c cosmo_fun.c io_mock.h cosmo_fun.h
	cc -lm radial2redshift.c io_mock.c cosmo_fun.c -o r2z.x

z2r.x: redshift2radial.c io_mock.c cosmo_fun.c io_mock.h cosmo_fun.h
	cc -lm redshift2radial.c io_mock.c cosmo_fun.c -o z2r.x

cat2ngl.x: catalog2ngl.c io_mock.c io_mock.h
	cc -lm catalog2ngl.c io_mock.c -o cat2ngl.x

clean_skel.x: clean_pairs.c io_mock.c io_mock.h
	cc -lm clean_pairs.c io_mock.c -o clean_skel.x

skel_shape.x: get_skeleton_shape.c io_mock.c io_mock.h
	cc -lm get_skeleton_shape.c io_mock.c -o skel_shape.x

test_cosmo.x: test_cosmo.c cosmo_fun.c cosmo_fun.h
	cc -lm test_cosmo.c cosmo_fun.c -o test_cosmo.x


test_cosmo: test_cosmo.x
	./test_cosmo.x

test_io: test_io.x
	./test_io.x ../data/raw/mass_sdss3_17.dat
	./test_io.x ../data/raw/x_sdss3_17.dat
	./test_io.x ../data/raw/y_sdss3_17.dat
	./test_io.x ../data/raw/x_sdss3_17.dat
	./test_io.x ../data/raw/vx_sdss3_17.dat
	./test_io.x ../data/raw/vy_sdss3_17.dat
	./test_io.x ../data/raw/vz_sdss3_17.dat



# get info from a cartesian catalog to put it into the ngl format
PATH_PROCESSED=../data/processed/
PATH_RAW=../data/raw/
CUT_MASS=1.0E14
FRAC=0.03
NAME_NGL=ngl_sdss3_17_MASS_$(CUT_MASS)_F_$(FRAC).dat
FILE_NGL=$(PATH_PROCESSED)/$(NAME_NGL)

cat2ngl: $(FILE_NGL)

$(FILE_NGL): cat2ngl.x
	./cat2ngl.x $(PATH_RAW)/x_sdss3_17.dat $(PATH_RAW)/y_sdss3_17.dat $(PATH_RAW)/z_sdss3_17.dat $(PATH_RAW)/mass_sdss3_17.dat $(FILE_NGL) $(CUT_MASS) $(FRAC)



# run the skeleton

EXEC_PATH=/Users/forero/Dropbox/SparseFilaments/code/ngl-beta/binsrc/
PATH_SKELETON=../data/skeleton/
METHOD=BSkeleton
BETA=10
FILE_SKEL=$(PATH_SKELETON)$(METHOD)_$(BETA)_$(NAME_NGL)

skeleton: $(FILE_SKEL)

$(FILE_SKEL): $(FILE_NGL)
	$(EXEC_PATH)./getNeighborGraph -i $(FILE_NGL) -d 3 -b $(BETA) -m $(METHOD) > $(FILE_SKEL)

# clean the pairs in the skeleton

FILE_SKEL_CLEAN=$(PATH_SKELETON)/clean_$(METHOD)_$(BETA)_$(NAME_NGL)

clean_skeleton: $(FILE_SKEL_CLEAN)

$(FILE_SKEL_CLEAN): $(FILE_SKEL) clean_skel.x
	./clean_skel.x $(FILE_SKEL) $(FILE_SKEL_CLEAN)

# dump lenghts of each edge in the skeleton
FILE_SKEL_SHAPE_X=$(PATH_SKELETON)/edge_x_$(METHOD)_$(BETA)_$(NAME_NGL)
FILE_SKEL_SHAPE_Y=$(PATH_SKELETON)/edge_y_$(METHOD)_$(BETA)_$(NAME_NGL)
FILE_SKEL_SHAPE_Z=$(PATH_SKELETON)/edge_z_$(METHOD)_$(BETA)_$(NAME_NGL)
FILE_SKEL_SHAPE_ASCII=$(PATH_SKELETON)/edge_xyz_$(METHOD)_$(BETA)_$(NAME_NGL)

shape_skeleton: $(FILE_SKEL_SHAPE_ASCII) 

$(FILE_SKEL_SHAPE_ASCII): $(FILE_SKEL_CLEAN) $(FILE_NGL) skel_shape.x sub_sample.x
	./skel_shape.x $(FILE_NGL) $(FILE_SKEL_CLEAN) $(FILE_SKEL_SHAPE_X) $(FILE_SKEL_SHAPE_Y) $(FILE_SKEL_SHAPE_Z)
	./sub_sample.x $(FILE_SKEL_SHAPE_X) $(FILE_SKEL_SHAPE_Y) $(FILE_SKEL_SHAPE_Z) $(FILE_SKEL_SHAPE_ASCII) 1.0

# get radial data into redshift space
TRUE_OMEGA_M=0.30
TRUE_OMEGA_L=0.70
TRUE_W=-1.0
FILE_Z_SHIFT_NORSD=$(PATH_PROCESSED)/z_shift_norsd_$(TRUE_OMEGA_M)_$(TRUE_OMEGA_L)_$(TRUE_W)_sdss3_17.dat
FILE_Z_SHIFT_RSD=$(PATH_PROCESSED)/z_shift_rsd_$(TRUE_OMEGA_M)_$(TRUE_OMEGA_L)_$(TRUE_W)_sdss3_17.dat
FILE_R_FROM_MOCK=$(PATH_PROCESSED)/r_sdss3_17.dat
FILE_VR_FROM_MOCK=$(PATH_PROCESSED)/vr_sdss3_17.dat


r2z: $(FILE_Z_SHIFT_NORSD) $(FILE_Z_SHIFT_RSD)


$(FILE_Z_SHIFT_NORSD): r2z.x $(FILE_R_FROM_MOCK) $(FILE_VR_FROM_MOCK)
	./r2z.x $(FILE_R_FROM_MOCK) $(FILE_VR_FROM_MOCK) $(TRUE_OMEGA_M) $(TRUE_OMEGA_L) $(TRUE_W) 0 $(FILE_Z_SHIFT_NORSD)

$(FILE_Z_SHIFT_RSD): r2z.x $(FILE_R_FROM_MOCK) $(FILE_VR_FROM_MOCK)
	./r2z.x $(FILE_R_FROM_MOCK) $(FILE_VR_FROM_MOCK) $(TRUE_OMEGA_M) $(TRUE_OMEGA_L) $(TRUE_W) 1 $(FILE_Z_SHIFT_RSD)


OMEGA_M=0.30
OMEGA_L=0.70
W=-1.0
FILE_R_FROM_Z_SHIFT_NORSD=$(PATH_PROCESSED)/r_built_norsd_$(OMEGA_M)_$(OMEGA_L)_$(W)_sdss3_17.dat
FILE_R_FROM_Z_SHIFT_RSD=$(PATH_PROCESSED)/r_built_rsd_$(OMEGA_M)_$(OMEGA_L)_$(W)_sdss3_17.dat

z2r: $(FILE_R_FROM_Z_SHIFT_NORSD) $(FILE_R_FROM_Z_SHIFT_RSD)

$(FILE_R_FROM_Z_SHIFT_NORSD): z2r.x $(FILE_Z_SHIFT_NORSD)
	./z2r.x $(FILE_Z_SHIFT_NORSD) $(OMEGA_M) $(OMEGA_L) $(W) $(FILE_R_FROM_Z_SHIFT_NORSD)

$(FILE_R_FROM_Z_SHIFT_RSD): z2r.x $(FILE_Z_SHIFT_RSD)
	./z2r.x $(FILE_Z_SHIFT_RSD) $(OMEGA_M) $(OMEGA_L) $(W) $(FILE_R_FROM_Z_SHIFT_RSD)



#get the radial velocity
FILE_X_RAW=$(PATH_RAW)/x_sdss3_17.dat
FILE_Y_RAW=$(PATH_RAW)/y_sdss3_17.dat
FILE_Z_RAW=$(PATH_RAW)/z_sdss3_17.dat
FILE_VX_RAW=$(PATH_RAW)/vx_sdss3_17.dat
FILE_VY_RAW=$(PATH_RAW)/vy_sdss3_17.dat
FILE_VZ_RAW=$(PATH_RAW)/vz_sdss3_17.dat
$(FILE_VR_FROM_MOCK): rv.x
	./rv.x $(FILE_X_RAW) $(FILE_Y_RAW) $(FILE_Z_RAW) $(FILE_VX_RAW) $(FILE_VY_RAW) $(FILE_VZ_RAW) $(FILE_VR_FROM_MOCK)

# get cartesian data into spherical data
spherical:  ../data/raw/r_sdss3_17.dat 

../data/raw/r_sdss3_17.dat: c2s.x 
	./c2s.x ../data/raw/x_sdss3_17.dat ../data/raw/y_sdss3_17.dat ../data/raw/z_sdss3_17.dat ../data/processed/r_sdss3_17.dat ../data/processed/phi_sdss3_17.dat ../data/processed/theta_sdss3_17.dat  
	./sub_sample.x ../data/processed/r_sdss3_17.dat ../data/processed/phi_sdss3_17.dat ../data/processed/theta_sdss3_17.dat ../data/processed/sample_spherical.dat 0.1

# selecting subsamples to dump into an ascii file
subsample:  ../data/processed/pos_sdss3_17_sub001.dat

../data/raw/pos_sdss3_17_sub001.dat: sub_sample.x	
	./sub_sample.x ../data/raw/x_sdss3_17.dat ../data/raw/y_sdss3_17.dat ../data/raw/z_sdss3_17.dat ../data/processed/pos_sdss3_17_sub001.dat 0.01

clean: 
	rm -f *.x 
	rm -f *.o
	rm -f *~
	rm -f ../data/processed/pos_sdss3_17_sub001.dat
	rm -f $(FILE_NGL)
	rm -f $(FILE_SKEL)