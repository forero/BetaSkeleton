# parameters to be fed in the command line
#MOCK_ID
#BETA
#CUT_MASS
#FRAC
#RSD

# Setup paths
PATH_POST=../data/processed/
PATH_RAW=../data/raw/
EXEC_PATH=/home/forero/software/ngl-beta/build/binsrc/
PATH_SKELETON=../data/skeleton/
PATH_STATS=../data/stats/
#MOCK_ID=17
MOCK_NAME=sdss3_$(MOCK_ID)

# Cuts before dumping into ascii NGL format (needed by the skeleton)
#CUT_MASS=5.0E13
#FRAC=0.02

# Skeleton parameters
METHOD=BSkeleton
#BETA=10

# Cosmological parameters used to distort the original mock 
TRUE_OMEGA_M=0.30
TRUE_OMEGA_L=0.70
TRUE_W=-1.0

# Are we using redshift distortions? 1=YES 0=NO
#RSD=0

# Cosmological parameters used to reconstruct after RSD distortion. These might be the wrong ones.
OMEGA_M=0.30
OMEGA_L=0.70
W=-1.0

# Now all the evolution of all the different files used here
FILE_RAW_X=$(PATH_RAW)/x_$(MOCK_NAME).dat
FILE_RAW_Y=$(PATH_RAW)/y_$(MOCK_NAME).dat
FILE_RAW_Z=$(PATH_RAW)/z_$(MOCK_NAME).dat
FILE_RAW_VX=$(PATH_RAW)/vx_$(MOCK_NAME).dat
FILE_RAW_VY=$(PATH_RAW)/vy_$(MOCK_NAME).dat
FILE_RAW_VZ=$(PATH_RAW)/vz_$(MOCK_NAME).dat
FILE_RAW_MASS=$(PATH_RAW)/mass_$(MOCK_NAME).dat

# Directly from raw to spherical + radial velocities
FILE_R_POS=$(PATH_POST)/r_$(MOCK_NAME).dat
FILE_PHI_POS=$(PATH_POST)/phi_$(MOCK_NAME).dat
FILE_THETA_POS=$(PATH_POST)/theta_$(MOCK_NAME).dat
FILE_VR=$(PATH_POST)/vr_$(MOCK_NAME).dat

# Redshift file from the previous radial distances
FILE_Z_SHIFT=$(PATH_POST)/z_shift_$(MOCK_NAME)_RSD_$(RSD).dat

# Radial distance reconstructed from the redshift.
FILE_R_POS_RECONSTRUCT=$(PATH_POST)/r_$(MOCK_NAME)_RSD_$(RSD)_OM_$(OMEGA_M)_OL_$(OMEGA_L).dat

# Cartesian coordinates from the reconstructed radial coordinates
FILE_X_POS_RECONSTRUCT=$(PATH_POST)/x_$(MOCK_NAME)_RSD_$(RSD)_OM_$(OMEGA_M)_OL_$(OMEGA_L).dat
FILE_Y_POS_RECONSTRUCT=$(PATH_POST)/y_$(MOCK_NAME)_RSD_$(RSD)_OM_$(OMEGA_M)_OL_$(OMEGA_L).dat
FILE_Z_POS_RECONSTRUCT=$(PATH_POST)/z_$(MOCK_NAME)_RSD_$(RSD)_OM_$(OMEGA_M)_OL_$(OMEGA_L).dat

# Files for the skeleton
STAMP=$(MOCK_NAME)_RSD_$(RSD)_OM_$(OMEGA_M)_OL_$(OMEGA_L)_MASS_$(CUT_MASS)_FRAC_$(FRAC)_BETA_$(BETA)
FILE_NGL=$(PATH_SKELETON)/NGL_$(STAMP).dat
FILE_NGL_BENCH=$(PATH_SKELETON)/NGL_bench_$(STAMP).dat
FILE_SKEL=$(PATH_SKELETON)/$(METHOD)_$(STAMP).dat
FILE_SKEL_CLEAN=$(PATH_SKELETON)/clean_$(METHOD)_$(STAMP).dat
FILE_SKEL_SHAPE_X=$(PATH_SKELETON)/edge_x_$(METHOD)_$(STAMP).dat
FILE_SKEL_SHAPE_Y=$(PATH_SKELETON)/edge_y_$(METHOD)_$(STAMP).dat
FILE_SKEL_SHAPE_Z=$(PATH_SKELETON)/edge_z_$(METHOD)_$(STAMP).dat
FILE_SKEL_SHAPE_ASCII=$(PATH_SKELETON)/edge_xyz_$(METHOD)_$(STAMP).dat

# Final KS stats
FILE_SKEL_SHAPE_ASCII_KS=$(PATH_STATS)/KS_$(METHOD)_$(STAMP).dat

#compute the spherical coordinates from cartesian
$(FILE_R_POS): c2s.x
	./c2s.x $(FILE_RAW_X) $(FILE_RAW_Y) $(FILE_RAW_Z) $(FILE_R_POS) $(FILE_PHI_POS) $(FILE_THETA_POS) 

#compute the radial velocities 
$(FILE_VR): rv.x
	./rv.x $(FILE_RAW_X) $(FILE_RAW_Y) $(FILE_RAW_Z) $(FILE_RAW_VX) $(FILE_RAW_VY) $(FILE_RAW_VZ) $(FILE_VR)

#get the redshifts from the radial measurements of distance and peculiar velocity for the true cosmology
$(FILE_Z_SHIFT): r2z.x $(FILE_R_POS) $(FILE_VR)
	./r2z.x $(FILE_R_POS) $(FILE_VR) $(TRUE_OMEGA_M) $(TRUE_OMEGA_L) $(TRUE_W) $(RSD) $(FILE_Z_SHIFT)

#get the radial distance from redshift measurements
$(FILE_R_POS_RECONSTRUCT): z2r.x $(FILE_Z_SHIFT) 
	./z2r.x $(FILE_Z_SHIFT) $(OMEGA_M) $(OMEGA_L) $(W) $(FILE_R_POS_RECONSTRUCT)

#Converts spherical-coordinates into cartesian coordinates:
$(FILE_X_POS_RECONSTRUCT): s2c.x $(FILE_R_POS_RECONSTRUCT) 
	./s2c.x $(FILE_R_POS_RECONSTRUCT) $(FILE_PHI_POS) $(FILE_THETA_POS) $(FILE_X_POS_RECONSTRUCT) $(FILE_Y_POS_RECONSTRUCT) $(FILE_Z_POS_RECONSTRUCT)

# Prepare the NGL file to find the skeleton. Makes a cut in mass and fraction of points.
$(FILE_NGL): cat2ngl.x $(FILE_X_POS_RECONSTRUCT) $(FILE_Y_POS_RECONSTRUCT) $(FILE_Z_POS_RECONSTRUCT)
	./cat2ngl.x $(FILE_X_POS_RECONSTRUCT) $(FILE_Y_POS_RECONSTRUCT) $(FILE_Z_POS_RECONSTRUCT) $(FILE_RAW_MASS) $(FILE_NGL) $(CUT_MASS) $(FRAC)
	./cat2ngl.x $(FILE_RAW_X) $(FILE_RAW_Y) $(FILE_RAW_Z) $(FILE_RAW_MASS) $(FILE_NGL_BENCH) $(CUT_MASS) $(FRAC)

# Run the Skeleton
$(FILE_SKEL): $(FILE_NGL)
	$(EXEC_PATH)./getNeighborGraph -i $(FILE_NGL) -d 3 -b $(BETA) -m $(METHOD) > $(FILE_SKEL)

# Clean the duplicated pairs in the skeletonas
$(FILE_SKEL_CLEAN): $(FILE_SKEL) clean_skel.x
	./clean_skel.x $(FILE_SKEL) $(FILE_SKEL_CLEAN)

# Get the vectorial length of every edge in the skeleton and dump it as an ascii file
$(FILE_SKEL_SHAPE_ASCII): $(FILE_SKEL_CLEAN) $(FILE_NGL) skel_shape.x sub_sample.x
	./skel_shape.x $(FILE_NGL) $(FILE_SKEL_CLEAN) $(FILE_SKEL_SHAPE_X) $(FILE_SKEL_SHAPE_Y) $(FILE_SKEL_SHAPE_Z)
	./sub_sample.x $(FILE_SKEL_SHAPE_X) $(FILE_SKEL_SHAPE_Y) $(FILE_SKEL_SHAPE_Z) $(FILE_SKEL_SHAPE_ASCII) 1.0

# Final stage where I get the KS test for the skeleton
$(FILE_SKEL_SHAPE_ASCII_KS):$(FILE_SKEL_SHAPE_ASCII)
	python isotropy_KS_test.py $(FILE_SKEL_SHAPE_ASCII) >  $(FILE_SKEL_SHAPE_ASCII_KS)

all: $(FILE_SKEL_SHAPE_ASCII_KS)

# how to compile all the small scripts
test_io.x: test_io.c io_mock.c io_mock.h
	cc test_io.c io_mock.c -o test_io.x

sub_sample.x: sub_sample.c io_mock.c io_mock.h
	cc sub_sample.c io_mock.c -o sub_sample.x

rv.x: radial_velocities.c io_mock.c io_mock.h
	cc radial_velocities.c io_mock.c -lm -o rv.x

c2s.x:cartesian2spherical.c io_mock.c io_mock.h
	cc cartesian2spherical.c io_mock.c -lm -o c2s.x

s2c.x:spherical2cartesian.c io_mock.c io_mock.h
	cc spherical2cartesian.c io_mock.c -lm -o s2c.x

r2z.x: radial2redshift.c io_mock.c cosmo_fun.c io_mock.h cosmo_fun.h
	cc radial2redshift.c io_mock.c cosmo_fun.c -lm -o r2z.x

z2r.x: redshift2radial.c io_mock.c cosmo_fun.c io_mock.h cosmo_fun.h
	cc redshift2radial.c io_mock.c cosmo_fun.c -lm -o z2r.x

cat2ngl.x: catalog2ngl.c io_mock.c io_mock.h
	cc catalog2ngl.c io_mock.c -lm -o cat2ngl.x

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

clean: 
	rm -f *.x 
	rm -f *.o
	rm -f *~
	rm -f $(FILE_SKEL_SHAPE_ASCII_KS)
	rm -f $(FILE_Z_SHIFT)
