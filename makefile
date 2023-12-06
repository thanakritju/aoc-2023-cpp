current_dir = $(shell pwd)

# make day=00 run
run:
	BAZEL_CXXOPTS="-std=c++17" bazel run //day$(day):main $(current_dir)/day$(day)/input.txt

# make day=00 test
test:
	BAZEL_CXXOPTS="-std=c++17" bazel run //day$(day):main