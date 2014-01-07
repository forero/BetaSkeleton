test_io.x: test_io.c io_mock.c io_mock.h
	cc test_io.c io_mock.c -o test_io.x

sub_sample.x: sub_sample.c io_mock.c io_mock.h
	cc sub_sample.c io_mock.c -o sub_sample.x

test: test_io.x
	./test_io.x ../data/mass_sdss3_17.dat
	./test_io.x ../data/x_sdss3_17.dat
	./test_io.x ../data/y_sdss3_17.dat
	./test_io.x ../data/x_sdss3_17.dat
	./test_io.x ../data/vx_sdss3_17.dat
	./test_io.x ../data/vy_sdss3_17.dat
	./test_io.x ../data/vz_sdss3_17.dat

subsample:  ../data/pos_sdss3_17_sub001.dat

../data/pos_sdss3_17_sub001.dat: sub_sample.x	
	./sub_sample.x ../data/x_sdss3_17.dat ../data/y_sdss3_17.dat ../data/z_sdss3_17.dat ../data/pos_sdss3_17_sub001.dat 0.01


clean: 
	rm -f *.x 
	rm -f *.o
	rm -f *~
	rm -f ../data/pos_sdss3_17_sub001.dat
