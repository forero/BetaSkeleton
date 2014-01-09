test_io.x: test_io.c io_mock.c io_mock.h
	cc test_io.c io_mock.c -o test_io.x

sub_sample.x: sub_sample.c io_mock.c io_mock.h
	cc sub_sample.c io_mock.c -o sub_sample.x

rv.x: radial_velocities.c io_mock.c io_mock.h
	cc -lm radial_velocities.c io_mock.c -o rv.x

c2s.x:cartesian2spherical.c io_mock.c io_mock.h
	cc -lm cartesian2spherical.c io_mock.c -o c2s.x

cat2ngl.x: catalog2ngl.c io_mock.c io_mock.h
	cc -lm catalog2ngl.c io_mock.c -o cat2ngl.x

test: test_io.x
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
CUT_MASS=5.0E13
FRAC=0.5
FILE_NGL=$(PATH_PROCESSED)/ngl_sdss3_17_MASS_$(CUT_MASS)_F_$(FRAC).dat

cat2ngl: $(FILE_NGL)

$(FILE_NGL): cat2ngl.x
	./cat2ngl.x $(PATH_RAW)/x_sdss3_17.dat $(PATH_RAW)/y_sdss3_17.dat $(PATH_RAW)/z_sdss3_17.dat $(PATH_RAW)/mass_sdss3_17.dat $(FILE_NGL) $(CUT_MASS) $(FRAC)


# run the skeleton
#FILE_SKEL=$(PATH_SKELETON)$METHOD\_b1.5_$POS_FILE
#skeleton: $

# get cartesian data into spherical data
spherical:  ../data/raw/r_sdss3_17.dat 

../data/raw/r_sdss3_17.dat: c2s.x 
	./c2s.x ../data/raw/x_sdss3_17.dat ../data/raw/y_sdss3_17.dat ../data/raw/z_sdss3_17.dat ../data/processed/r_sdss3_17.dat ../data/processed/phi_sdss3_17.dat ../data/processed/theta_sdss3_17.dat  
	./sub_sample.x ../data/processed/r_sdss3_17.dat ../data/processed/phi_sdss3_17.dat ../data/processed/theta_sdss3_17.dat ../data/processed/sample_spherical.dat 0.1

# selecting subsamples to dump into an ascii file
subsample:  ../data/processed/pos_sdss3_17_sub001.dat

../data/raw/pos_sdss3_17_sub001.dat: sub_sample.x	
	./sub_sample.x ../data/raw/x_sdss3_17.dat ../data/raw/y_sdss3_17.dat ../data/raw/z_sdss3_17.dat ../data/processed/pos_sdss3_17_sub001.dat 0.01

# computing the radial velocity component
radial:	../data/processed/vr_sdss3_17.dat

../data/raw/vr_sdss3_17.dat: rv.x
	./rv.x ../data/raw/x_sdss3_17.dat ../data/raw/y_sdss3_17.dat ../data/raw/z_sdss3_17.dat ../data/raw/vx_sdss3_17.dat ../data/raw/vy_sdss3_17.dat ../data/raw/vz_sdss3_17.dat ../data/processed/vr_sdss3_17.dat 

clean: 
	rm -f *.x 
	rm -f *.o
	rm -f *~
	rm -f ../data/processed/pos_sdss3_17_sub001.dat
