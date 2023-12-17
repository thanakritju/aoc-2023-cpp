current_dir = $(shell pwd)

# make day=00 run
run:
	bazel run //day$(day):main $(current_dir)/day$(day)/input.txt

# make day=01 example
example:
	bazel run //day$(day):main $(current_dir)/day$(day)/example.txt

# make day=00 test
test:
	bazel run //day$(day):main

# make day=05 generate
generate:
	cp -r template day$(day)

install:
	brew install bazel